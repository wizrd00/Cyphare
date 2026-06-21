#include "launcher.h"

static void *thread_push_file(void *arg)
{
	params_t *param = (params_t *) arg;
	param->push._stat = push_file(param->push.config, param->push.path);
	param->push.finish = true;
	return NULL;
}

static void *thread_pull_file(void *arg)
{
	params_t *param = (params_t *) arg;
	param->pull._stat = pull_file(param->pull.config, param->pull.remote_name);
	param->pull.finish = true;
	return NULL;
}

static void *thread_scan_pair(void *arg)
{
	params_t *param = (params_t *) arg;
	param->scan._stat = scanpair(param->scan.config, param->scan.info, param->scan.len);
	param->scan.finish = true;
	return NULL;
}

int launch_push_file(InitConfig *config, const char *path, const char *logpath)
{
	int _stat = 0;
	params_t param;
	pthread_t hdl;
	struct timespec sleeptime = {.tv_sec = 0, .tv_nsec = LAUNCH_PUSH_FILE_INTERVAL};
	param.push.config = config;
	param.push.path = path;
	param.push.finish = false;
	if (initiate(logpath, (size_t) DEFAULT_LOG_COUNT) != 0)
		return -1;
	cli_push_path(path);
	cli_push_info(config->addrs.remote_ip, config->addrs.remote_port);
	cli_create_bar();
	if (pthread_create(&hdl, NULL, thread_push_file, (void *) &param) != 0)
		return -1;
	while (!param.push.finish) {
		if (config->seq != 0)
			cli_update_bar(config->seq - 1, config->chcount);
		nanosleep(&sleeptime, NULL);
	}
	cli_update_bar(config->seq - 1, config->chcount);
	if (deinitiate() != 0)
		return -1;
	return _stat = cli_push_result(param.push._stat);
}

int launch_pull_file(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	params_t param;
	pthread_t hdl;
	char remote_name[MAXNAMESIZE] = {0};
	struct timespec sleeptime = {.tv_sec = 0, .tv_nsec = LAUNCH_PULL_FILE_INTERVAL};
	param.pull.config = config;
	param.pull.remote_name = remote_name;
	param.pull.finish = false;
	if (initiate(logpath, (size_t) DEFAULT_LOG_COUNT) != 0)
		return -1;
	cli_pull_info(config->addrs.local_ip, config->addrs.local_port);
	cli_create_bar();
	if (pthread_create(&hdl, NULL, thread_pull_file, (void *) &param) != 0)
		return -1;
	while (!param.pull.finish) {
		if (config->seq != 0)
			cli_update_bar(config->seq - 1, config->chcount);
		nanosleep(&sleeptime, NULL);
	}
	cli_update_bar(config->seq - 1, config->chcount);
	if (deinitiate() != 0)
		return -1;
	return _stat = cli_pull_result(param.pull._stat);
}

int launch_scanpair(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	params_t param;
	PairInfo *info;
	size_t len = 0;
	pthread_t hdl;
	struct timespec sleeptime = {.tv_sec = LAUNCH_SCAN_PAIR_INTERVAL, .tv_nsec = 0};
	param.scan.config = config;
	param.scan.info = &info;
	param.scan.len = &len;
	param.scan.finish = false;
	if (initiate(logpath, (size_t) DEFAULT_LOG_COUNT) != 0)
		return -1;
	if (pthread_create(&hdl, NULL, thread_scan_pair, (void *) &param) != 0)
		return -1;
	while (!param.scan.finish) {
		cli_scan_info(len);
		nanosleep(&sleeptime, NULL);
	}
	if (deinitiate() != 0) {
		free(info);
		return -1;
	}
	_stat = cli_scan_result(param.scan._stat, info, len);
	free(info);
	return _stat;
}
