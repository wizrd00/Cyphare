#include "cyphare.h"

static char help[] =
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
	"\t\t\t[-n <name>=random]  [-s <source-ip:source-port>=0.0.0.0:1308]\n"
	"\n";

int main(int argc, char *argv[])
{
	args_t args;
	int opt;
	CHECK_ARGC(argc);
	optind = 2;
	if (strcmp(argv[1], SCANSTR) == 0) {
		args.scan.ip_spec = false;
		args.scan.port_spec = false;
		while ((opt = getopt(argc, argv, SCANOPTSTR)) != -1)
			switch (opt) {
				case 's' :
					CHECK_SRCADDR(optarg, args.scan.ip, &(args.scan.port));
					args.scan.ip_spec = true;
					args.scan_port_spec = true;
					break;
				case ':' :
					fprintf(stderr, MISSED_ERROR, optopt);
					fprintf(stderr, help);
					return 1;
				case '?' :
					fprintf(stderr, UNKNOWN_ERROR, optopt);
					fprintf(stderr, help);
					return 1;
				default :
					fprintf(stderr, GLOBAL_ERROR);
					fprintf(stderr, help);
					return 1;
			}
	}
	else if (strcmp(argv[1], PUSHSTR) == 0) {
		args.push.chsize_spec = false;
		args.push.path_spec = false;
		args.push.name_spec = false;
		args.src_ip_spec = false;
		args.dst_ip_sped = false;
		args.src_port_spec = false;
		args.dst_port_spec = false;
		while ((opt = getopt(argc, argv, PUSHOPTSTR)) != -1)
			switch (opt) {
				case 'c' :
					CHECK_CHUNKSIZE(optarg, &(args.push.chsize));
					break;
				case 'f' :
					CHECK_FILE(optarg, true);
					args.push.path = optarg;
					break;
				case 'n' :
					CHECK_NAME(optarg);
					strncpy(args.push.name, optarg, MAXNAMESIZE);
					break;
				case 's' :
					CHECK_SRCADDR(optarg, args.push.src_ip, &(args.push.src_port));
					break;
				case 'd' :
					CHECK_DSTADDR(optarg, args.push.dst_ip, &(args.push.dst_port));
					break;
				case ':' :
					fprintf(stderr, MISSED_ERROR, optopt);
					fprintf(stderr, help);
					return 1;
				case '?' :
					fprintf(stderr, UNKNOWN_ERROR, optopt);
					fprintf(stderr, help);
					return 1;
				default :
					fprintf(stderr, GLOBAL_ERROR);
					fprintf(stderr, help);
					return 1;
			}
	}
	else if (strcmp(argv[1], PULLSTR) == 0) {
		args.pull.name_spec = false;
		args.pull.ip_spec = false;
		args.pull.port_spec = false;
		while ((opt = getopt(argc, argv, PULLOPTSTR)) != -1)
			switch (opt) {
				case 'n' :
					CHECK_NAME(optarg);
					strncpy(args.pull.name, optarg, MAXNAMESIZE);
					break;
				case 's' :
					CHECK_SRCADDR(optarg, args.pull.ip, &(args.pull.port));
					break;
				case ':' :
					fprintf(stderr, MISSED_ERROR, optopt);
					fprintf(stderr, help);
					return 1;
				case '?' :
					fprintf(stderr, UNKNOWN_ERROR, optopt);
					fprintf(stderr, help);
					return 1;
				default :
					fprintf(stderr, GLOBAL_ERROR);
					fprintf(stderr, help);
					return 1;
			}
	}
	return 0;
}
