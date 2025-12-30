#ifndef CYPHARE_TRYEXEC_H
#define CYPHARE_TRYEXEC_H

#include <stdlib.h>
#include <stdio.h>

static inline void tryexec(int status)
{
	if (status == 0)
		return;
	fputs("ERROR\n", stderr);
	exit(EXIT_FAILURE);
	return;
}

#endif
