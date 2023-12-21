/*
 * Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>
#ifdef CONFIG_SYS_COREBOOT
#include <asm/arch/sysinfo.h>
#endif
#include "ver_shl.h"
#include <stdio.h>

const char __weak version_string[] = U_BOOT_VERSION_STRING;

static int do_version(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char buf[DISPLAY_OPTIONS_BANNER_LENGTH];

	printf(display_options_get_banner(false, buf, sizeof(buf)));
#ifdef CC_VERSION_STRING
	puts(CC_VERSION_STRING "\n");
#endif
#ifdef LD_VERSION_STRING
	puts(LD_VERSION_STRING "\n");
#endif
#ifdef CONFIG_SYS_COREBOOT
	printf("coreboot-%s (%s)\n", lib_sysinfo.version, lib_sysinfo.build);
#endif
	return 0;
}

U_BOOT_CMD(
	version,	1,		1,	do_version,
	"print monitor, compiler and linker version",
	""
);

// 定义一个函数，用于等待用户输入字符，如果输入字符是 'g'，则继续执行
void wait_input(void)
{
    char input;
    printf("请输入字符 'g' 以继续程序：\n");
    while (1) {
        // scanf(" %c", &input); // 注意这里的空格，用于吸收可能的空白字符
		input = getc();
        if (input == 'g') {
            break; // 如果输入是 'g'，则退出循环
        }
    }
}


static int do_shl_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    printf("hello shl 1104=====\n");
	// KBUILD_CFLAGS   += $(call cc-option)	# shl   Makefile 619行去掉 -Werror=date-time
	printf("compile time is: %s  %s\n", __DATE__, __TIME__);
	printf("ver_shl.h time is: %s %s\n", BUILD_DATE, BUILD_TIME);
	debug("this is debug ....\n");
	my_dbg("this is my_dbg\n");

	my_dbg("will wait input...\n");
	wait_input();
	my_dbg("out of wait_input!\n");

    return 0;
}

U_BOOT_CMD(
	shl_test,	1,		1,	do_shl_test,
	"It's just shl test",
	""
);