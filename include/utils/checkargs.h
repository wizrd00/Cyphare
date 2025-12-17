#ifndef CYPHARE_CHECKARGS_H
#define CYPHARE_CHECKARGS_H

#include <librufshare/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXTIMEOUT 16
#define MAXIPV4SIZE 16

static inline bool check_address_format(char *addr, char *src_ip, unsigned short *src_port)
{
	char *ip = addr;
	char *port = addr;
	uint32_t ipnetorder;
	char *endptr;
	long tmp_port;
	while (*(port++)) {if (*port == ':') {*port = '\0'; port++; break;}}
	if (inet_pton(AF_INET, ip, &ipnetorder) != 1)
		return false;
	tmp_port = strtol(port, &endptr, 10);
	if ((*endptr != '\0') || (tmp_port <= 0) || (tmp_port > 65535))
		return false;
	strncpy(src_ip, ip, MAXIPV4SIZE);
	*src_port = (unsigned short) tmp_port;
	return true;
}

static inline bool check_chunk_size(char *chsize0, RUFShareChunkSize *chsize1)
{
	long tmp_chsize;
	char *endptr;
	tmp_chsize = strtol(chsize0, &endptr, 10);
	if ((*endptr != '\0') || (tmp_chsize <= 0) || (tmp_chsize > 65535))
		return false;
	*chsize1 = (RUFShareChunkSize) tmp_chsize;
	return true;
}

static inline bool check_file_path(char *file, bool check_size)
{
	struct stat statbuf;
	if (stat(file, &statbuf) == -1)
		return false;
	if (check_size)
		if (statbuf.st_size == 0)
			return false;
	return true;
}

static inline bool check_name_length(char *name)
{
	size_t len = strlen(name);
	if ((len == 0) || (len > MAXNAMESIZE))
		return false;
	return true;
}

#endif
