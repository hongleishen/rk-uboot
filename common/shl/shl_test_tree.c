#include <stdio.h>
#include <tree.h>
#include <common.h>
#include <command.h>
#include <tree.h>
// tree_node *root;
// tree_node current_node;

void a1(void);

// ---------------func b------------------------------
// 叶子函数定义
void b1(void) 
{
    f_start_hook(21);
    a1();
    f_end_hook();
}

void b2(void)
{
    f_start_hook(27);
    f_end_hook();
}

void b_3(void)
{
    f_start_hook(33);
    f_end_hook();
}


// --------func a--------------------------------
// 分支函数定义
void a1(void)
{
    f_start_hook(42);

    b1();
    b2();

    f_end_hook();
}


void a2(void)
{
    f_start_hook(53);

    b_3();

    f_end_hook();
}

// -------------------func root-------------------------
// 根函数定义      必须跟函数初始化root后，后面的树形结构才会运行，在此之前，函数都直接跳过
void root_function(void)
{
    f_start_hook(64);
    printf("%s\n", __func__);

    root = create_node("root");
    current_node = root;
    
    a1();
    a2();

    free_tree(&root);
    if (root == NULL) {
        my_dbg("root is null after free\n");
    } else {
        my_dbg("root is not null after free\n");
    }

    f_end_hook();
}

/*
               root
        a1              a2
    b1     b2            b_3
*/


static int _test_tree(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    my_dbg("test tree in uboot\n");
    root_function();
    return 0;
}

U_BOOT_CMD(
    shl_test_tree, 1, 1, _test_tree,
    "shl test tree, in common",
    "<u32 number>"
);
