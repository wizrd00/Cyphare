#ifndef CYPHARE_H
#define CYPHARE_H

#include "types.h"
#include "utils/checkargs.h"
#include "librufshare/rufshare.h"
#include <stdlib.h>
#include <string.h>

#define VERSION "0.0.1"
#define SCANSTR "scan"
#define PUSHSTR "push"
#define PULLSTR "pull"
#define SCANOPTSTR ":s:"
#define PUSHOPTSTR ":c:f:n:s:d:"
#define PULLOPTSTR ":n:s:"

#define GLOBAL_ERROR "getopt() failed, something went wrong!\n\n"
#define MISSED_ERROR "missed argument for option -%c\n\n"
#define UNKNOWN_ERROR "unknown option -%c\n\n"
#define INV_SRCADDR_ERROR "invalid source address format\n\n"
#define INV_DSTADDR_ERROR "invalid destination address format\n\n"
#define INV_CHSIZE_ERROR "invalid chunk size, maximum size is 65535 bytes\n\n"
#define INV_FILE_ERROR "invalid file path %s\n\n"
#define INV_NAME_ERROR "invalid name %s\n\n"

#define CHECK_ARGC(val)\
	do {if (val < 2) {fprintf(stderr, help); return 1;}} while (0)

#define CHECK_SRCADDR(val, ip, port)\
	do {if (!check_address_format(val, ip, port)) {fprintf(stderr, INV_SRCADDR_ERROR); fprintf(stderr, help); return 1;}} while (0)

#define CHECK_DSTADDR(val, ip, port)\
	do {if (!check_address_format(val, ip, port)) {fprintf(stderr, INV_DSTADDR_ERROR); fprintf(stderr, help); return 1;}} while (0)

#define CHECK_CHUNKSIZE(val, chsize)\
	do {if (!check_chunk_size(val, chsize)) {fprintf(stderr, INV_CHSIZE_ERROR); fprintf(stderr, help); return 1;}} while (0)

#define CHECK_FILE(val, check_size)\
	do {if (!check_file_path(val, check_size)) {fprintf(stderr, INV_FILE_ERROR, val); fprintf(stderr, help); return 1;}} while (0)

#define CHECK_NAME(val)\
	do {if (!check_name_length(val)) {fprintf(stderr, INV_NAME_ERROR, val); fprintf(stderr, help); return 1;}} while (0)

int main(int argc, char *argv[]);

typedef union {
	struct {
		char ip[MAXIPV4SIZE];
		bool ip_spec;
		unsigned short port;
		bool port_spec;
	} scan;
	struct {
		RUFShareChunkSize chsize;
		bool chsize_spec;
		char *path;
		bool chsize_spec;
		char name[MAXNAMESIZE];
		bool name_spec;
		char src_ip[MAXIPV4SIZE];
		bool src_ip_spec;
		char dst_ip[MAXIPV4SIZE];
		bool dst_ip_spec;
		unsigned short src_port;
		bool src_port_spec;
		unsigned short dst_port;
		bool dst_port_spec;
	} push;
	struct {
		char name[MAXNAMESIZE];
		bool name_spec;
		char ip[MAXIPV4SIZE];
		bool ip_spec;
		unsigned short port;
		bool port_spec;
	} pull;
} args_t;

#endif
