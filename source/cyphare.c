#include "cyphare.h"

static const char help[] =
	"Cyphare version" " " VERSION " " "help message :\n"
	"source code in https://github.com/wizrd00/Cyphare.git\n"
	"./cyphare TASK [OPTIONS]\n"
	"TASKs :\n"
	"\n\tscan" "    " "scans hosts in the network that are ready to receive file\n"
	"\t\tOPTIONS :\n"
	"\t\t\t[-s <source-ip:source-port>=0.0.0.0:1308]\n"
	"\n\tpush" "    " "pushes desired file to the host\n"
	"\t\tOPTIONS :\n"
	"\t\t\t[-c <chunk-size>=65535]  [-f <file>]  [-n <username>=random]\n"
	"\t\t\t[-s <source-ip:source-port>=0.0.0.0:1308]  [-d <destination-ip:destination-port>]\n"
	"\n\tpull" "    " "broadcasts in the network that it's ready to receive file\n"
	"\t\tOPTIONS :\n"
	"\t\t\t[-n <name>=random]  [-s <source-ip:source-port>=0.0.0.0:1307]\n"
	"\n";

int main(int argc, char *argv[])
{
	args_t args;
	InitConfig config;
	pthread_t handle;
	CHECK_ARGC(argc);
	if (strcmp(argv[1], SCANSTR) == 0) {
		if (scan_argparse(argc, argv, &args) != 0)
			return 1;
		mkconfig_scan(&config, &args);
		tryexec(launch_scanpair(&config, DEFAULT_LOG_PATH));
	}
	else if (strcmp(argv[1], PUSHSTR) == 0) {
		if (push_argparse(argc, argv, &args) != 0)
			return 1;
		mkconfig_push(&config, &args);
		tryexec(launch_push_file(&config, args.push.path, DEFAULT_LOG_PATH));
	}
	else if (strcmp(argv[1], PULLSTR) == 0) {
		if (pull_argparse(argc, argv, &args) != 0)
			return 1;
		mkconfig_pull(&config, &args);
		tryexec(launch_pull_file(&config, DEFAULT_LOG_PATH));
	}
	else {
		fprintf(stderr, TASK_ERROR, argv[1]);
		fprintf(stderr, help);
		return 1;
	}
	return 0;
}
