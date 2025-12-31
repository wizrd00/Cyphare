#include "launcher.h"

static int launch_initiate(const char *logpath)
{
	return (initiate(logpath) == 0) ? 0 : -1;
}

int launch_scanpair(InitConfig *config, const char *logpath)
{
	int _stat = 0;
	return _stat;
}

int launch_push_file(InitConfig *config, const char *path)
{
	int _stat = 0;
	return _stat = cli_push_result(push_stat);
}

int launch_pull_file(InitConfig *config)
{
	int _stat = 0;
	return _stat = cli_pull_result(pull_stat);
}
