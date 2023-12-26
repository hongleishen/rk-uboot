#ifndef TREE_H
#define TREE_H

// 定义树节点结构体
typedef struct tree_node {
    char *data;

    struct tree_node **children; // 子节点数组
    int child_count;            // 子节点数量

    struct tree_node *parent;           // 父节点
    int depth;                          // 节点深度
} tree_node;


extern tree_node *root;
extern tree_node *current_node;

// depth printf
#define d_printf(format, ...)    do {    \
    for (int i = 0; i < 4*current_node->depth; i++) {    \
        printf(" ");    \
    }   \
    if (format[0] != '\0') \
        printf(format, ##__VA_ARGS__); \
} while(0);

extern void _f_start_hook(const char *file, const char *func, int line, int n_line);
extern void _f_end_hook(const char *func);

#define f_start_hook(n_line)  _f_start_hook(__FILE__, __func__, __LINE__, n_line);
#define f_end_hook() _f_end_hook((const char *)__func__);


tree_node *create_node(const char *data);
//void add_child(tree_node *parent, tree_node *child);
void add_child(tree_node *child);

void preorder_traversal(tree_node *node);
void postorder_traversal(tree_node *node);
tree_node *search(tree_node *node, const char *data);

void free_tree(tree_node **pp_node);
void remove_child(tree_node *parent, tree_node *child);

#endif