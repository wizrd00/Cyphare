#ifndef CYPHARE_ARGPARSE_H
#define CYPHARE_ARGPARSE_H

#include "types.h"
#include "utils/randname.h"
#include <getopt.h>

extern char help[];

static inline int scan_argparse(int argc, char *argv[], args_t *args)
{
	int opt;
	optind = 2;
	args->scan.ip_spec = false;
	args->scan.port_spec = false;
	while ((opt = getopt(argc, argv, SCANOPTSTR)) != -1)
		switch (opt) {
			case 's' :
				CHECK_SRCADDR(optarg, args->scan.ip, &(args->scan.port));
				args->scan.ip_spec = true;
				args->scan.port_spec = true;
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
	if (!args->scan.ip_spec)
		strncpy(args->scan.ip, DEFAULT_SRC_IP, MAXIPV4SIZE);
	if (!args->scan.port_spec)
		args->scan.port = DEFAULT_SRC_PORT;
	return 0;
}

static inline int push_argparse(int argc, char *argv[], args_t *args)
{
	int opt;
	optind = 2;
	args->push.chsize_spec = false;
	args->push.path_spec = false;
	args->push.name_spec = false;
	args->push.src_ip_spec = false;
	args->push.dst_ip_spec = false;
	args->push.src_port_spec = false;
	args->push.dst_port_spec = false;
	while ((opt = getopt(argc, argv, PUSHOPTSTR)) != -1)
		switch (opt) {
			case 'c' :
				CHECK_CHUNKSIZE(optarg, &(args->push.chsize));
				break;
			case 'f' :
				CHECK_FILE(optarg, true);
				args->push.path = optarg;
				break;
			case 'n' :
				CHECK_NAME(optarg);
				strncpy(args->push.name, optarg, MAXNAMESIZE);
				break;
			case 's' :
				CHECK_SRCADDR(optarg, args->push.src_ip, &(args->push.src_port));
				break;
			case 'd' :
				CHECK_DSTADDR(optarg, args->push.dst_ip, &(args->push.dst_port));
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
	if (!args->push.chsize_spec)
		args->push.chsize = DEFAULT_CHUNK_SIZE;
	if (!args->push.name_spec)
		mkrandname(args->push.name);
	if (!args->push.src_ip_spec)
		strncpy(args->push.src_ip, DEFAULT_SRC_IP, MAXIPV4SIZE);
	if (!args->push.src_port_spec)
		args->push.src_port = DEFAULT_SRC_PORT;
	return 0;
}

static int pull_argparse(int argc, char *argv[], args_t *args)
{
	int opt;
	optind = 2;
	args->pull.name_spec = false;
	args->pull.ip_spec = false;
	args->pull.port_spec = false;
	while ((opt = getopt(argc, argv, PULLOPTSTR)) != -1)
		switch (opt) {
			case 'n' :
				CHECK_NAME(optarg);
				strncpy(args->pull.name, optarg, MAXNAMESIZE);
				break;
			case 's' :
				CHECK_SRCADDR(optarg, args->pull.ip, &(args->pull.port));
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
	if (!args->pull.name_spec)
		mkrandname(args->pull.name);
	if (!args->pull.ip_spec)
		strncpy(args->pull.ip, DEFAULT_SRC_IP, MAXIPV4SIZE);
	if (!args->pull.port_spec)
		args->pull.port = DEFAULT_SRC_PORT;
	return 0;
}

#endif
