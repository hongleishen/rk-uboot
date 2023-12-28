#include <stdio.h>
#include <stdlib.h>
#include <tree.h>
#include <common.h>
#include <malloc.h>

#include <linux/string.h>

/*
// 定义树节点结构体
typedef struct tree_node {
    char *data;

    struct tree_node **children;	// 子节点数组
    int child_count;            	// 子节点数量

    struct tree_node *parent;		// 父节点
    int depth;              		// 节点深度
} tree_node;
 */

tree_node *root = NULL;
tree_node *current_node = NULL;      // current_node 代表当前运行的node，对于新创建的node，它就是parent node

void *my_realloc(void *ptr, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    if (!ptr) {
        return malloc(new_size);
    }

    void *new_ptr = malloc(new_size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, new_size); // 复制旧内存内容到新内存
        free(ptr);
    }
    return new_ptr;
}

// 创建新节点
tree_node *create_node(const char *data) 
{
    tree_node *parent = current_node;
	tree_node *node = (tree_node*)malloc(sizeof(tree_node));
    memset(node, 0, sizeof(*node));
	node->data = strdup(data); // 复制字符串
	node->children = NULL;
	node->child_count = 0;

    node->parent = parent;
	node->depth = node->parent ? node->parent->depth + 1 : 0; // 设置深度
    //current_node = node;

	return node;
}

// 添加子节点
void add_child(tree_node *child) 
{
    tree_node *parent = current_node;
	parent->child_count++;
	parent->children = (tree_node**)my_realloc(parent->children, sizeof(tree_node*)*parent->child_count);
	parent->children[parent->child_count - 1] = child;

    child->parent = parent;
    //child->depth = parent->depth + 1; // 更新子节点的深度,  create_node已经设置，可以不更新
	current_node = child;
}

// 前序遍历
void preorder_traversal(tree_node *node)
{
	if (node == NULL) return;
	printf("%s,%d;    ", node->data, node->depth);
	for (int i = 0; i < node->child_count; i++) {
		preorder_traversal(node->children[i]);
	}
}

// 后序遍历
void postorder_traversal(tree_node *node)
{
	if (node == NULL) return;
	for (int i = 0; i < node->child_count; i++) {
		postorder_traversal(node->children[i]);
	}
	printf("%s ", node->data);
}

// 搜索节点
tree_node *search(tree_node *node, const char *data)
{
	if (node == NULL) return NULL;
	if (strcmp(node->data, data) == 0) return node;
	for (int i = 0; i < node->child_count; i++) {
		tree_node *result = search(node->children[i], data);
		if (result != NULL) return result;
	}
	return NULL;
}


// 移除子节点
void remove_child(tree_node *parent, tree_node *child)
{
	if (parent == NULL || child == NULL) return;

	if (strcmp(parent->data, "root") == 0)
		return;

	// 创建一个新的子节点数组
	int new_count = 0;
	tree_node* *new_children = malloc(sizeof(tree_node*)  *parent->child_count);

	// 复制除了要移除的子节点外的所有子节点
	for (int i = 0; i < parent->child_count; i++) {
		if (parent->children[i] != child) {
			new_children[new_count++] = parent->children[i];
		}
	}

	// 释放原来的子节点数组
	free(parent->children);

	// 更新父节点的子节点数组和计数
	parent->children = new_children;
	parent->child_count = new_count;
}


// 释放树内存
void free_tree(tree_node **pp_node)
{
	tree_node *node = *pp_node;
	my_dbg("node->data = %s\n", node->data);
	if (node == NULL) return;
	for (int i = 0; i < node->child_count; i++) {
		free_tree(&node->children[i]);
	}
	free(node->data);
	free(node->children);
	
	*pp_node = NULL;
}


/*
*    祖宗用完了，如果它自己不除名，后面子代永远不能用
*/
#define N_FUNC   10
char freq_func[N_FUNC][32] = {};  // 存储高频出现的函数名
void save_func(const char *func)
{
	int i = 0;
	// 更新存储的字符串
	for (i = N_FUNC - 1; i > 0; i--) {
		strcpy(freq_func[i], freq_func[i - 1]);
	}
	strcpy(freq_func[0], func);
	return;
}

void rm_func(const char *func)
{

}


#define SIZE 5
#define occurred_frequently_n  2

int func_count = 0;
char recent_strings[SIZE][32] = {};  // 存储最近5次输入的字符串
int occurred_frequently(const char *func)
{
    int i, j, found;

	// 检查字符串是否重复

	found = 0;
	for (i = 0; i < SIZE; i++) {
		// printf("recent_strings[%d] = %s\n", i, recent_strings[i]);
		if (strcmp(recent_strings[i], func) == 0) {
			if (func_count++ >= occurred_frequently_n) {
				d_printf("func %s occurred_frequently!!!!!!!\n", func);
				save_func(func);
				found = 1;
				func_count = 0;
				break;
			}
		}
	}

	// 更新存储的字符串
	for (j = SIZE - 1; j > 0; j--) {
		strcpy(recent_strings[j], recent_strings[j - 1]);
	}
	strcpy(recent_strings[0], func);

	return found;
}


void _f_start_hook(const char *file, const char *func, int line, int n_line)
{
	int i = 0;

    if (root == NULL) {
        my_dbg(" root == NULL, return\n");
        return;
    }

	for (i = 0; i < N_FUNC; i++) {
		if (strcmp(freq_func[i], func) == 0) {
			// printf("---- %s has freq ocur return in start_hook!\n", func);
			return;
		}
	}

	if (occurred_frequently(func)) {
        my_dbg(" %s occurred_frequently return\n", func);
        return;		
	}

    tree_node *func_node = create_node(func);
    add_child(func_node);

    d_printf("%s        [%s, %d] %d\n", func, file, line, n_line);

    return;
}

void _f_end_hook(const char *func)
{
	int i = 0;

    if (root == NULL) {
        my_dbg(" root == NULL, return\n");
        return;
    }

	for (i = 0; i < N_FUNC; i++) {
		// printf("===== freq_func[%d] = %s\n", i, freq_func[i]);
		if (strcmp(freq_func[i], func) == 0) {
			// printf("===== %s has freq ocur return it in end_hook!\n", func);
			return;
		}
	}

    tree_node *tmp = current_node;

	#if 0
    d_printf("--");
    preorder_traversal(root);
    printf("\n");
	#endif

    remove_child(current_node->parent, current_node);
    // d_printf("rm current_node->data:%s, current_node->depth = %d;  set current_node to %s\n\n", tmp->data, tmp->depth, tmp->parent->data);
    current_node = tmp->parent;
    return;
}