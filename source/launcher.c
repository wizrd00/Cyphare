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
	struct timespec nanotime = {.tv_sec = 0, .tv_nsec = LAUNCH_PUSH_FILE_INTERVAL};
	if (launch_initiate(logpath) == -1)
		return -1;
	param.push.config = config;
	param.push.path = path;
	cli_push_path(path);
	cli_push_info(config->addrs.remote_ip, config->addrs.remote_port);
	cli_create_bar();
	if (pthread_create(&hdl, NULL, thread_push_file, (void *) &param) != 0)
		return -1;
	while (pthread_cond_timedwait(&cond, &mutx, &nanotime) == ETIMEDOUT) {
		if ((!config->chcount) && (!config->seq))
			cli_update_bar(config->seq, config->chcount);
	}
	return _stat = cli_push_result(param.push._stat);
}

int launch_pull_file(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	params_t param;
	pthread_t hdl;
	char remote_name[MAXNAMESIZE] = {0};
	struct timespec nanotime = {.tv_sec = 0, .tv_nsec = LAUNCH_PULL_FILE_INTERVAL};
	param.pull.config = config;
	param.pull.remote_name = remote_name;
	cli_pull_info(config->addrs.local_ip, config->addrs.local_port);
	if (pthread_create(&hdl, NULL, thread_pull_file, (void *) &param) != 0)
		return -1;
	while (pthread_cond_timedwait(&cond, &mutx, &nanotime) != ETIMEDOUT) {
		if ((!config->chcount) && (!config->seq))
			cli_update_bar(config->seq, config->chcount);
	}
	return _stat = cli_pull_result(param.pull._stat);
}

int launch_scanpair(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	return _stat;
}
