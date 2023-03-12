/*
 *  Pocris Sabin - 312CB
 */

#include "SystemConfiguration.h"

void readSystemConfiguration(SysConfig *sysConfig, IO *io) {
  fscanf(io->fileInput, "%d", &(sysConfig->quantum));
  fscanf(io->fileInput, "%d", &(sysConfig->numberOfCores));
  sysConfig->numberOfThreads = sysConfig->numberOfCores * 2;
}