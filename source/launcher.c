#include "launcher.h"

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;

static void *thread_push_file(void *arg)
{
	params_t *param = (params_t *) arg;
	param->push._stat = push_file(param->push.config, param->push.path);
	pthread_cond_signal(&cond);
	return NULL;
}

static void *thread_pull_file(void *arg)
{
	params_t *param = (params_t *) arg;
	param->pull._stat = pull_file(param->pull.config, param->pull.remote_name);
	pthread_cond_signal(&cond);
	return NULL;
}

static void *thread_scan_pair(void *arg)
{
	params_t *param = (params_t *) arg;
	param->scan._stat = scanpair(param->scan.config, param->scan.info, param->scan.len);
	pthread_cond_signal(&cond);
	return NULL;
}

static int launch_initiate(const char *logpath)
{
	return (initiate(logpath) == 0) ? 0 : -1;
}

int launch_push_file(InitConfig *config, const char *path, const char *logpath)
{
	int _stat = 0;
	params_t param;
	pthread_t hdl;
	struct timespec abstime = {.tv_sec = 0, .tv_nsec = 0};
	param.push.config = config;
	param.push.path = path;
	if (launch_initiate(logpath) == -1)
		return -1;
	cli_push_path(path);
	cli_push_info(config->addrs.remote_ip, config->addrs.remote_port);
	cli_create_bar();
	if (pthread_create(&hdl, NULL, thread_push_file, (void *) &param) != 0)
		return -1;
	while (pthread_cond_timedwait(&cond, &mutx, &abstime) == ETIMEDOUT) {
		if ((!config->chcount) && (!config->seq))
			cli_update_bar(config->seq, config->chcount);
		if (clock_gettime(CLOCK_REALTIME, &abstime) != 0)
			return -1;
		abstime.tv_sec += LAUNCH_PUSH_FILE_INTERVAL;
	}
	return _stat = cli_push_result(param.push._stat);
}

int launch_pull_file(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	params_t param;
	pthread_t hdl;
	char remote_name[MAXNAMESIZE] = {0};
	struct timespec abstime = {.tv_sec = 0, .tv_nsec = 0};
	param.pull.config = config;
	param.pull.remote_name = remote_name;
	if (launch_initiate(logpath) == -1)
		return -1;
	cli_pull_info(config->addrs.local_ip, config->addrs.local_port);
	if (pthread_create(&hdl, NULL, thread_pull_file, (void *) &param) != 0)
		return -1;
	while (pthread_cond_timedwait(&cond, &mutx, &abstime) == ETIMEDOUT) {
		if ((!config->chcount) && (!config->seq))
			cli_update_bar(config->seq, config->chcount);
		if (clock_gettime(CLOCK_REALTIME, &abstime) != 0)
			return -1;
		abstime.tv_sec += LAUNCH_PULL_FILE_INTERVAL;
	}
	return _stat = cli_pull_result(param.pull._stat);
}

int launch_scanpair(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	params_t param;
	PairInfo *info;
	size_t len = 0;
	pthread_t hdl;
	struct timespec abstime = {.tv_sec = 0, .tv_nsec = 0};
	param.scan.config = config;
	param.scan.info = &info;
	param.scan.len = &len;
	if (launch_initiate(logpath) == -1)
		return -1;
	pthread_mutex_lock(&mutx);
	if (pthread_create(&hdl, NULL, thread_scan_pair, (void *) &param) != 0)
		return -1;
	while (pthread_cond_timedwait(&cond, &mutx, &abstime) == ETIMEDOUT) {
		cli_scan_info(len);
		if (clock_gettime(CLOCK_REALTIME, &abstime) != 0)
			return -1;
		abstime.tv_sec += LAUNCH_SCAN_PAIR_INTERVAL;
	}
	_stat = cli_scan_result(param.scan._stat, info, len);
	free(info);
	return _stat;
}
