#ifndef CYPHARE_MKCONFIG_H
#define CYPHARE_MKCONFIG_H

#include "types.h"
#include <string.h>

static inline void mkconfig_scan(InitConfig *conf, args_t *args)
{
	conf->spt_cast = DEFAULT_SP_CAST;
	conf->sp_interval = DEFAULT_SP_INTERVAL;
	conf->sp_trycount = DEFAULT_SP_TRYCOUNT;
	strncpy(conf->addrs.local_ip, args->scan.ip, MAXIPV4SIZE);	
	conf->addrs.local_port = args->port;
	return;
}

static inline void mkconfig_push(InitConfig *conf, args_t *args)
{
	conf->chsize = args->push.chsize;
	conf->pchsize = 0;
	conf->chcount = 0;
	conf->seq = 0;
	//TODO
	return;
}

#endif
