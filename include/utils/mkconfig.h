#ifndef CYPHARE_MKCONFIG_H
#define CYPHARE_MKCONFIG_H

#include "types.h"
#include <string.h>

static inline void mkconfig_scan(InitConfig *conf, args_t *args)
{
	strncpy(conf->addrs.local_ip, args->scan.ip, MAXIPV4SIZE);	
	conf->addrs.local_port = args->scan.port;
	conf->spt_cast = DEFAULT_SP_CAST;
	conf->sp_interval = DEFAULT_SP_INTERVAL;
	conf->sp_trycount = DEFAULT_SP_TRYCOUNT;
	return;
}

static inline void mkconfig_push(InitConfig *conf, args_t *args)
{
	conf->chsize = args->push.chsize;
	conf->pchsize = 0;
	conf->chcount = 0;
	conf->seq = 0;
	extract_file_name(conf->addrs.filename, args->push.path, MAXFILENAMESIZE);
	strncpy(conf->addrs.name, args->push.name, MAXNAMESIZE);
	strncpy(conf->addrs.local_ip, args->push.src_ip, MAXIPV4SIZE);
	strncpy(conf->addrs.remote_ip, args->push.dst_ip, MAXIPV4SIZE);
	conf->addrs.local_port = args->push.src_port;
	conf->addrs.remote_port = args->push.dst_port;
	conf->hst_send = DEFAULT_HST_SEND;
	conf->hst_recv = DEFAULT_HST_RECV;
	conf->tft_flow = DEFAULT_TFT_FLOW;
	conf->tft_recv = DEFAULT_TFT_RECV;
	conf->tft_data = DEFAULT_TFT_DATA;
	conf->vft_send = DEFAULT_VFT_SEND;
	conf->vft_recv = DEFAULT_VFT_RECV;
	conf->tf_trycount = DEFAULT_TF_TRYCOUNT;
	return;
}

static inline void mkconfig_pull(InitConfig *conf, args_t *args)
{
	conf->chsize = 0;
	conf->pchsize = 0;
	conf->chcount = 0;
	conf->seq = 0;
	strncpy(conf->addrs.name, args->pull.name, MAXNAMESIZE);
	strncpy(conf->addrs.local_ip, args->pull.ip, MAXIPV4SIZE);
	conf->addrs.local_port = args->pull.port;
	conf->hst_send = DEFAULT_HST_SEND;
	conf->hst_recv = DEFAULT_HST_RECV;
	conf->tft_flow = DEFAULT_TFT_FLOW;
	conf->tft_recv = DEFAULT_TFT_RECV;
	conf->tft_data = DEFAULT_TFT_DATA;
	conf->vft_send = DEFAULT_VFT_SEND;
	conf->vft_recv = DEFAULT_VFT_RECV;
	conf->bc_interval = DEFAULT_BC_INTERVAL;
	conf->tf_trycount = DEFAULT_TF_TRYCOUNT;
	conf->bc_trycount = DEFAULT_BC_TRYCOUNT;
	return;
}

#endif
