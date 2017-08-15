#include "sysmanager.h"
#include "../logger/logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "../../fpga/fpga.h"

char* sysmanager::getApplicationName()
{
	static char dest[PATH_MAX];
	memset(dest, 0, sizeof(dest));

	char path[64];
	sprintf(path, "/proc/%d/exe", getpid());
	readlink(path, dest, PATH_MAX);

	return dest;
}

void sysmanager::restartApplication()
{
	// Flush all pending changes to disk(s)
	sync();

	fpga::instance().core_reset(true);

	char *appname = getApplicationName();
	printf("Restarting the %s...\n", appname);

	// Spawn new copy of main executable
	char *argv[] = { appname, NULL };
	execve(appname, argv, NULL);

	// Control won't reach this point in normal conditions
	LOGERROR("Spawning via execve failed. Rebooting the device ...\n");
	fpga::instance().fpga::reboot(false);
}

const char* sysmanager::getDataRootDir()
{
	return "/media/fat";
}