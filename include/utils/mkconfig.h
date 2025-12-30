#ifndef CYPHARE_MKCONFIG_H
#define CYPHARE_MKCONFIG_H

#include "types.h"
#include "librufshare/utils/sstr.h"
#include <string.h>

static inline void mkconfig_scan(InitConfig *config, args_t *args)
{
	sstrncpy(config->addrs.local_ip, args->scan.ip, MAXIPV4SIZE);	
	config->addrs.local_port = args->scan.port;
	config->spt_cast = DEFAULT_SPT_CAST;
	config->sp_interval = DEFAULT_SP_INTERVAL;
	config->sp_trycount = DEFAULT_SP_TRYCOUNT;
	return;
}

static inline void mkconfig_push(InitConfig *config, args_t *args)
{
	config->chsize = args->push.chsize;
	config->pchsize = 0;
	config->chcount = 0;
	config->seq = 0;
	extract_file_name(config->addrs.filename, args->push.path, MAXFILENAMESIZE);
	sstrncpy(config->addrs.name, args->push.name, MAXNAMESIZE);
	sstrncpy(config->addrs.local_ip, args->push.src_ip, MAXIPV4SIZE);
	sstrncpy(config->addrs.remote_ip, args->push.dst_ip, MAXIPV4SIZE);
	config->addrs.local_port = args->push.src_port;
	config->addrs.remote_port = args->push.dst_port;
	config->hst_send = DEFAULT_HST_SEND;
	config->hst_recv = DEFAULT_HST_RECV;
	config->tft_flow = DEFAULT_TFT_FLOW;
	config->tft_recv = DEFAULT_TFT_RECV;
	config->tft_data = DEFAULT_TFT_DATA;
	config->vft_send = DEFAULT_VFT_SEND;
	config->vft_recv = DEFAULT_VFT_RECV;
	config->tf_trycount = DEFAULT_TF_TRYCOUNT;
	return;
}

static inline void mkconfig_pull(InitConfig *config, args_t *args)
{
	config->chsize = 0;
	config->pchsize = 0;
	config->chcount = 0;
	config->seq = 0;
	sstrncpy(config->addrs.name, args->pull.name, MAXNAMESIZE);
	sstrncpy(config->addrs.local_ip, args->pull.ip, MAXIPV4SIZE);
	sstrncpy(config->addrs.remote_ip, DEFAULT_DST_IP, MAXIPV4SIZE);
	config->addrs.local_port = args->pull.port;
	config->addrs.remote_port = DEFAULT_DST_PORT;
	config->hst_send = DEFAULT_HST_SEND;
	config->hst_recv = DEFAULT_HST_RECV;
	config->tft_flow = DEFAULT_TFT_FLOW;
	config->tft_recv = DEFAULT_TFT_RECV;
	config->tft_data = DEFAULT_TFT_DATA;
	config->vft_send = DEFAULT_VFT_SEND;
	config->vft_recv = DEFAULT_VFT_RECV;
	config->bct_cast = DEFAULT_BCT_CAST;
	config->bc_interval = DEFAULT_BC_INTERVAL;
	config->tf_trycount = DEFAULT_TF_TRYCOUNT;
	config->bc_trycount = DEFAULT_BC_TRYCOUNT;
	return;
}

#endif
