#include <stdio.h>
#include <tree.h>

// tree_node *root;
// tree_node *current;

#define d_printf(format, ...)    do {    \
    for (int i = 0; i < 4*current->depth; i++) {    \
        printf(" ");    \
    }   \
    if (format[0] != '\0') \
        printf(format, ##__VA_ARGS__); \
} while(0);


static void _f_start_hook(const char *func)
{
    if (root == NULL) {
        my_dbg(" root == NULL, return\n");
        return;
    }

    tree_node *func_node = create_node(func);
    add_child(func_node);

    d_printf("%s\n", func);

    return;
}
#define f_start_hook()   _f_start_hook((const char *)__func__);

// 删除当前节点，current上移变parent
static void _f_end_hook(const char *func)
{
    if (root == NULL) {
        my_dbg(" root == NULL, return\n");
        return;
    }

    tree_node *tmp = current;

    d_printf("--");
    preorder_traversal(root);
    printf("\n");

    remove_child(current->parent, current);
    d_printf("current->data:%s, current->depth = %d;  set current to %s\n\n", tmp->data, tmp->depth, tmp->parent->data);
    current = tmp->parent;
    return;
}
#define f_end_hook() _f_end_hook((const char *)__func__);


// ---------------func b------------------------------
// 叶子函数定义
void b1() {
    f_start_hook();
    f_end_hook();
}

void b2() {
    f_start_hook();
    f_end_hook();
}

void b_3() {
    f_start_hook();
    f_end_hook();
}


// --------func a--------------------------------
// 分支函数定义
void a1() {
    f_start_hook();

    b1();
    b2();

    f_end_hook();
}


void a2() {
    f_start_hook();

    b_3();

    f_end_hook();
}

// -------------------func root-------------------------
// 根函数定义      必须跟函数初始化root后，后面的树形结构才会运行，在此之前，函数都直接跳过
void root_function() {
    f_start_hook();
    printf("%s\n", __func__);

    root = create_node("root");
    current = root;
    
    a1();
    a2();

    free_tree(&root);
    if (root == NULL) 
        my_dbg("root is null after free\n");
    else
        my_dbg("root is not null after free\n");


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
