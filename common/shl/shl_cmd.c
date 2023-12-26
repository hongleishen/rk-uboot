#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>
#include "../../cmd/ver_shl.h"

unsigned int g_cmd_open_my_dbg;
unsigned int g_cmd_open_dwc3_writel;

static int do_shl_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    printf("hello shl 1225 =====\n");
	// KBUILD_CFLAGS   += $(call cc-option)	# shl   Makefile 619行去掉 -Werror=date-time
	printf("compile time is: %s  %s\n", __DATE__, __TIME__);
	printf("ver_shl.h time is: %s %s\n", BUILD_DATE, BUILD_TIME);
	debug("this is debug ....\n");
	n_my_dbg("this n_my_dbg\n");
	my_dbg("this is my_dbg\n");

    printf("g_cmd_open_my_dbg = %d\n", g_cmd_open_my_dbg);
    printf("g_cmd_open_dwc3_writel = %d\n", g_cmd_open_dwc3_writel);

    return 0;
}

U_BOOT_CMD(
	shl_cmd,	1,		1,	do_shl_cmd,
	"It's just shl test, in common",
	""
);


static int shl_arg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc != 3) {
        printf("Usage: shl_cmd <u32 number> <string>\n");
        return CMD_RET_USAGE;
    }

    unsigned long num;
    if (strict_strtoul(argv[1], 10, &num) < 0) {
        printf("Invalid number: %s\n", argv[1]);
        return CMD_RET_USAGE;
    }

    printf("hello shl 1225 =====\n");
    printf("Number: %lu\n", num);
    printf("String: %s\n", argv[2]);

    // Your existing code here

    return 0;
}

U_BOOT_CMD(
    shl_arg, 3, 1, shl_arg,
    "arg test, in common",
    "<u32 number> <string>"
);


static int _shl_open_my_dbg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc != 2) {
        printf("Usage: shl_open_my_dbg <u32 number>\n");
        return CMD_RET_USAGE;
    }

    unsigned long num;
    if (strict_strtoul(argv[1], 10, &num) < 0) {
        printf("Invalid number: %s\n", argv[1]);
        return CMD_RET_USAGE;
    }

    g_cmd_open_my_dbg = (unsigned int)num;
	printf("g_cmd_open_my_dbg = %d\n", g_cmd_open_my_dbg);
	my_dbg("test dbg\n");

    return 0;
}

U_BOOT_CMD(
    shl_open_my_dbg, 2, 1, _shl_open_my_dbg,
    "shl open my dbg, in common",
    "<u32 number>"
);


static int _shl_open_dwc3_writel(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc != 2) {
        printf("Usage: shl_open_dwc3_writel <u32 number>\n");
        return CMD_RET_USAGE;
    }

    unsigned long num;
    if (strict_strtoul(argv[1], 10, &num) < 0) {
        printf("Invalid number: %s\n", argv[1]);
        return CMD_RET_USAGE;
    }

    g_cmd_open_dwc3_writel = (unsigned int)num;
	printf("g_cmd_open_dwc3_writel = %d\n", g_cmd_open_dwc3_writel);

    return 0;
}

U_BOOT_CMD(
    shl_open_dwc3_writel, 2, 1, _shl_open_dwc3_writel,
    "shl open my dbg, in common",
    "<u32 number>"
);
