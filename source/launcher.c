#include "launcher.h"

int launch_scanpair(InitConfig *config)
{
	int _stat = 0;
	PairInfo *info;
	size_t len;
	int scan_stat;
	pid_t scan_pid = fork();
	if (scan_pid == 0)
		return scanpair(config, info, &len);
	while (waitpid(scan_pid, &scan_stat, WNOHANG) == 0) {
		cli_scan_len(len);
		sleep(1);
	}
	if (scan_stat == SUCCESS)
		cli_scan_info(info, len);
	else
		_stat = -1;
	free(info);
	return _stat;
}

int launch_push_file(InitConfig *config, const char *path)
{
	int _stat = 0;
	struct timespec interval = {.tv_sec = 0, .tv_nsec = LAUNCH_PUSH_FILE_INTERVAL};
	int push_stat;
	pid_t push_pid = fork();
	if (push_pid == 0)
		return push_file(config, path);
	cli_push_path(path);
	cli_push_info(conf->addrs.filename, conf->addrs.remote_ip, conf->addrs.remote_port);
	cli_create_bar();
	while (waitpid(push_pid, &push_stat, WNOHANG) == 0) {
		cli_update_bar((size_t) conf->seq);
		nanosleep(&interval, NULL);
	}
	return _stat = cli_push_result(push_stat);
}

int launch_pull_file(InitConfig *config)
{
	int _stat = 0;
	struct timespec interval = {.tv_sec = 0, .tv_nsec = LAUNCH_PULL_FILE_INTERVAL};
	int pull_stat;
	pid_t pull_pid = fork();
	char remote_name[MAXNAMESIZE];
	if (pull_pid == 0) {
		return pull_file(config, remote_name);
	}
	cli_create_bar();
	while (waitpid(pull_pid, &pull_stat, WNOHANG) == 0) {
		cli_update_bar((size_t ) conf->seq);
		nanosleep(&interval, NULL);
	}
	return _stat = cli_pull_result(pull_stat);
}
