/*
 *  Pocris Sabin - 312CB
 */

#ifndef _SYS_CONF_
#define _SYS_CONF_

#include <stdio.h>

#include "IO.h"

typedef struct SystemConfiguration {
  int quantum;
  int numberOfCores;
  int numberOfThreads;
} SysConfig;

void readSystemConfiguration(SysConfig *sysConfig, IO *io);

#endif