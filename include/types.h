#ifndef CYPHARE_TYPES_H
#define CYPHARE_TYPES_H

#include "librufshare/rufshare.h"
#include <stddef.h>
#include <stdbool.h>

#define VERSION "0.0.1"
#define SCANSTR "scan"
#define PUSHSTR "push"
#define PULLSTR "pull"

#define GLOBAL_ERROR "getopt() failed, something went wrong!\n\n"
#define TASK_ERROR "invalid task %s\n\n"
#define MISSED_ERROR "missed argument for option -%c\n\n"
#define UNKNOWN_ERROR "unknown option -%c\n\n"
#define INV_SRCADDR_ERROR "invalid source address format\n\n"
#define INV_DSTADDR_ERROR "invalid destination address format\n\n"
#define INV_CHSIZE_ERROR "invalid chunk size, maximum size is 65535 bytes\n\n"
#define INV_FILE_ERROR "invalid file path %s\n\n"
#define INV_NAME_ERROR "invalid name %s\n\n"

#define DEFAULT_SRC_IP "0.0.0.0"
#define DEFAULT_SRC_PORT 1308
#define DEFAULT_DST_IP "255.255.255.255"
#define DEFAULT_DST_PORT 1308
#define DEFAULT_CHUNK_SIZE 0xffff
#define DEFAULT_HST_SEND 8
#define DEFAULT_HST_RECV 8
#define DEFAULT_TFT_FLOW 8
#define DEFAULT_TFT_RECV 8
#define DEFAULT_TFT_DATA 8
#define DEFAULT_VFT_SEND 8
#define DEFAULT_VFT_RECV 8
#define DEFAULT_BCT_CAST 8
#define DEFAULT_SPT_CAST 8
#define DEFAULT_BC_INTERVAL 2
#define DEFAULT_SP_INTERVAL 8
#define DEFAULT_TF_TRYCOUNT 4
#define DEFAULT_SP_TRYCOUNT 4
#define DEFAULT_BC_TRYCOUNT 4

#undef CHECK_EQUAL
#define CHECK_EQUAL(val0, val1, err)\
	do {if (val0 != val1) {fprintf(stderr, err); return -1;}} while (0)

#undef CHECK_NOTEQUAL
#define CHECK_NOTEQUAL(val0, val1, err)\
	do {if (val0 == val1) {fprintf(stderr, err); return -1;}} while (0)

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
		bool path_spec;
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

extern const char help[];

#endif
