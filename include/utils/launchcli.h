#ifndef CYPHARE_LAUNCHCLI_H
#define CYPHARE_LAUNCHCLI_H

#include "types.h"
#include <stdio.h>

#define CLI_SCAN_LEN_TEXT "[\x1b[36mSCAN\x1b[0m] -> %d host found"
#define CLI_SCAN_INFO_TEXT "\n[\x1b[32m%d\x1b[0m] -> %.*s at %.*s:%.5hu\n"
#define CLI_PUSH_PATH_TEXT "[\x1b[36mPUSH\x1b[0m] -> the path '%s' specified\n"
#define CLI_PUSH_INFO_TEXT "[\x1b[36mPUSH\x1b[0m] -> push the file %.*s to remote host with address %.*s:%.5hu\n"

static inline void cli_scan_len(size_t len)
{
	printf(CLI_SCAN_LEN_TEXT, len);
	putchar('\r');
	return;
}

static inline void cli_scan_info(PairInfo *info, size_t len)
{
	for (int i = 0; i < len; i++)
		printf(CLI_SCAN_INFO_TEXT, MAXNAMESIZE, info[i].name, MAXIPV4SIZE, info[i].addr.ip, info[i].addr.port);	
	return;
}

static inline void cli_push_path(const char *path)
{
	printf(CLI_PUSH_PATH_TEXT, path);
	return;
}

static inline void cli_push_info(const char *filename, const char *remote_ip, const unsigned short remote_port)
{
	printf(CLI_PUSH_INFO_TEXT, MAXFILENAMESIZE, filename, MAXIPV4SIZE, remote_ip, remote_port);
	return;
}

static inline int cli_push_result(int status);

static inline void cli_create_bar(void);

static inline void cli_update_bar(size_t seq);

#endif
