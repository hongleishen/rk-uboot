#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>

#include <linux/compat.h>
#include "../../cmd/ver_shl.h"

unsigned int g_cmd_open_my_dbg;
unsigned int g_cmd_open_dwc3_writel;
unsigned int g_cmd_open_debug;


// 定义一个函数，用于等待用户输入字符，如果输入字符是 'g'，则继续执行
void wait_input(void)
{
    char input;
    // printf("请输入字符 'g' 以继续程序：\n");
    while (1) {
        // scanf(" %c", &input); // 注意这里的空格，用于吸收可能的空白字符
        input = getc();
        if (input == 'g') {  // 如果输入是 'g'，则退出循环
            // printf("get 'g', return\n");
            break;
        }
        // while (getc() != '\n');  // 清理输入缓冲区
    }
}

static int do_shl_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    printf("hello shl 1225 =====\n");
	// KBUILD_CFLAGS   += $(call cc-option)	# shl   Makefile 619行去掉 -Werror=date-time
	printf("compile time is: %s  %s\n", __DATE__, __TIME__);
	printf("ver_shl.h time is: %s %s\n", BUILD_DATE, BUILD_TIME);


	my_dbg("this is my_dbg\n");
    n_my_dbg("\nthis n_my_dbg\n");

    my_dev_dbg(dwc->dev, "this is my_dev_dbg\n");

	debug("this is debug ....\n");
    printf("--------------------\n");
	dev_dbg(NULL, "this is dev_dbg\n");
    printf("--------------\n");

    printf("g_cmd_open_my_dbg = %d\n", g_cmd_open_my_dbg);
    printf("g_cmd_open_dwc3_writel = %d\n", g_cmd_open_dwc3_writel);
    printf("g_cmd_open_debug = %d\n", g_cmd_open_debug);

	printf("will wait input... ---------\n");
	wait_input();
	printf("out of wait_input! ========\n");

    _shl_test();
    dwc3_device_hs_test();
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
    n_my_dbg("\n\ntest n_my_dbg\n");
    printf("end ======\n");

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



static int _shl_open_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc != 2) {
        printf("Usage: shl_open_debug <u32 number>\n");
        return CMD_RET_USAGE;
    }

    unsigned long num;
    if (strict_strtoul(argv[1], 10, &num) < 0) {
        printf("Invalid number: %s\n", argv[1]);
        return CMD_RET_USAGE;
    }

    g_cmd_open_debug = (unsigned int)num;
    debug("this is debug\n");
	printf("g_cmd_open_debug = %d\n", g_cmd_open_debug);

    return 0;
}

U_BOOT_CMD(
    shl_open_debug, 2, 1, _shl_open_debug,
    "shl open my dbg, in common",
    "<u32 number>"
);


static int _shl_open_all(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    g_cmd_open_my_dbg = 1;
    g_cmd_open_dwc3_writel = 2;
    g_cmd_open_debug = 1;

    printf("g_cmd_open_my_dbg = %d\n", g_cmd_open_my_dbg);
    printf("g_cmd_open_debug = %d\n", g_cmd_open_debug);
    printf("g_cmd_open_dwc3_writel = %d\n", g_cmd_open_dwc3_writel);

    return 0;
}

U_BOOT_CMD(
    shl_open_all, 1, 1, _shl_open_all,
    "shl open my dbg, in common",
    "<u32 number>"
);