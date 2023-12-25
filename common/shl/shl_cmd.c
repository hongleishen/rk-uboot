#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>
#include "../../cmd/ver_shl.h"


static int do_shl_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    printf("hello shl 1225 =====\n");
	// KBUILD_CFLAGS   += $(call cc-option)	# shl   Makefile 619行去掉 -Werror=date-time
	printf("compile time is: %s  %s\n", __DATE__, __TIME__);
	printf("ver_shl.h time is: %s %s\n", BUILD_DATE, BUILD_TIME);
	debug("this is debug ....\n");
	n_my_dbg("this n_my_dbg\n");
	my_dbg("this is my_dbg\n");
    return 0;
}

U_BOOT_CMD(
	shl_cmd,	1,		1,	do_shl_cmd,
	"It's just shl test, in common",
	""
);