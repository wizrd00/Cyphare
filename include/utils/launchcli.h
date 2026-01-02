#ifndef CYPHARE_LAUNCHCLI_H
#define CYPHARE_LAUNCHCLI_H

#include "types.h"
#include <stdio.h>

#define CLI_PUSH_PATH_TEXT "[\x1b[36mPUSH\x1b[0m] -> the path '%s' specified\n"
#define CLI_PUSH_INFO_TEXT "[\x1b[36mPUSH\x1b[0m] -> push the file to remote host with address %.*s:%.5hu\n"
#define CLI_PUSH_DONE_TEXT "[\x1b[36mPUSH\x1b[0m] -> push was successful%d\n"
#define CLI_PUSH_ERROR_TEXT "[\x1b[31mPUSH\x1b[0m] -> push failed with status code %d\n"
#define CLI_PULL_INFO_TEXT "[\x1b[36mPULL\x1b[0m] -> pull the file with local host address %.*s:%-5hu\n"
#define CLI_PULL_DONE_TEXT "[\x1b[36mPULL\x1b[0m] -> pull was successful%d\n"
#define CLI_PULL_ERROR_TEXT "[\x1b[31mPULL\x1b[0m] -> pull failed with status code %d\n"
#define CLI_SCAN_INFO_TEXT "[\x1b[36mSCAN\x1b[0m] -> %d host found\n"
#define CLI_SCAN_DONE_TEXT "[\x1b[32m%d\x1b[0m] -> %.*s at %.*s:%-5hu\n"
#define CLI_SCAN_ERROR_TEXT "[\x1b[31mSCAN\x1b[0m] -> scan pairs failed with status code %d\n"
#define CLI_BAR_CONTEXT_TEXT "progress -> [%lu/%lu]"

#define CLI_BAR_SYMBOL_COUNT 32

static inline void cli_push_path(const char *path)
{
	printf(CLI_PUSH_PATH_TEXT, path);
	return;
}

static inline void cli_push_info(const char *remote_ip, const unsigned short remote_port)
{
	printf(CLI_PUSH_INFO_TEXT, MAXIPV4SIZE, remote_ip, remote_port);
	return;
}

static inline int cli_push_result(status_t status)
{
	if (status != SUCCESS) {
		fprintf(stderr, CLI_PUSH_ERROR_TEXT, (int) status);
		return -1;
	}
	printf(CLI_PUSH_DONE_TEXT, (int) status);
	return 0;
}

static inline int cli_pull_info(const char *local_ip, const unsigned short local_port)
{
	printf(CLI_PULL_INFO_TEXT, MAXIPV4SIZE, local_ip, local_port);
	return 0;
}

static inline int cli_pull_result(status_t status)
{
	if (status != SUCCESS) {
		fprintf(stderr, CLI_PULL_ERROR_TEXT, (int) status);
		return -1;
	}
	printf(CLI_PULL_DONE_TEXT, (int) status);
	return 0;
}

static inline void cli_scan_info(size_t len)
{
	printf(CLI_SCAN_INFO_TEXT, len);
	putchar('\r');
	return;
}

static inline int cli_scan_result(status_t status, PairInfo *info, size_t len)
{
	if (status != SUCCESS) {
		fprintf(stderr, CLI_SCAN_ERROR_TEXT, (int) status);
		return -1;
	}
	for (int i = 0; i < len; i++)
		printf(CLI_SCAN_INFO_TEXT, MAXNAMESIZE, info[i].name, MAXIPV4SIZE, info[i].addr.ip, info[i].addr.port);	
	return 0;
}

static inline void cli_create_bar(void)
{
	printf(CLI_BAR_CONTEXT_TEXT, 0);
	putchar('\r');
	return;
}

static inline void cli_update_bar(size_t x, size_t y)
{
	printf(CLI_BAR_CONTEXT_TEXT, x, y);	
	putchar('\r');
}

#endif
