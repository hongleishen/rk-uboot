#ifndef TREE_H
#define TREE_H


#define DEBUG_SHL
#ifdef DEBUG_SHL
#define my_dbg(format, ...)     printf("[dbg: %s, %d ]" format, __func__, __LINE__, ##__VA_ARGS__)
#define n_my_dbg(format, ...) printf("\n[dbg: %s, %d ]" format, __func__, __LINE__, ##__VA_ARGS__)
//#define n_my_dbg(format, ...) printf("\n[dbg: %s, %d ]" format, __func__, __LINE__, ##__VA_ARGS__)


#else
#define my_dbg(format, ...)
#define n_my_dbg(format, ...)
#endif


// 定义树节点结构体
typedef struct tree_node {
    char *data;

    struct tree_node **children; // 子节点数组
    int child_count;            // 子节点数量

    struct tree_node *parent;           // 父节点
    int depth;                          // 节点深度
} tree_node;

extern tree_node *root;
extern tree_node *current;

tree_node *create_node(const char *data);
//void add_child(tree_node *parent, tree_node *child);
void add_child(tree_node *child);

void preorder_traversal(tree_node *node);
void postorder_traversal(tree_node *node);
tree_node *search(tree_node *node, const char *data);

void free_tree(tree_node **pp_node);
void remove_child(tree_node *parent, tree_node *child);

#endif