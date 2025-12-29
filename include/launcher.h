#ifndef CYPHARE_LAUNCHER_H
#define CYPHARE_LAUNCHER_H

#include "types.h"
#include "utils/launchcli.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define LAUNCH_PUSH_FILE_INTERVAL 100000000
#define LAUNCH_PULL_FILE_INTERVAL 200000000

int launch_scanpair(InitConfig *config);

int launch_push_file(InitConfig *config, const char *path);

int launch_pull_file(InitConfig *config);

#endif
