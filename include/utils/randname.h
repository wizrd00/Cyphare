#ifndef CYPHARE_RANDNAME_H
#define CYPHARE_RANDNAME_H

#include "types.h"
#include <stdlib.h>
#include <time.h>

static inline void mkrandname(char *name)
{
	srand((unsigned int) time(NULL));
	snprintf(name, MAXNAMESIZE, "cyphare%d", rand());
	return;
}

#endif
