#include <stdio.h>
#include <malloc.h>

#ifdef __GNUC__
#define max(x, y) ({ \
	typeof(x) _max1 = (x); \
	typeof(y) _max2 = (y); \
	(void)(&_max1 == &_max2); \
	_max1 > _max2 ? _max1 :_max2; \
})
#else
#define max(x, y) ({ \
	x > y ? x : y; \
})
#endif

typedef struct Tree{
	int data;
	struct Tree *left;
	struct Tree *right;
	struct Tree *parent;
	int height;
}Tree;

Tree *root = NULL;

/* 传入数据，查找数据是否存在
 * 如果不存在返回NULL，否则返回
 * 相应的节点指针 */
Tree *search(int data);

/* 传入数据，查找插入位置，禁
 * 止传入已存在的数据，请在调
 * 用前使用search进行搜索 */
Tree *where_insert(int data);

/* 传入数据，将数据格式化为节
 * 点，并插入到二叉树中，随后
 * 使二叉树平衡 */
void add(int data);

/* 传入一个整形数据，查找并删
 * 除相应的节点，随后对二叉树
 * 重新计算平衡，如果没有找到
 * 数据，则返回-1，否则返回0 */
int tree_delete(int data);

/* 向父节点查找不平衡节点，直
 * 到到达祖父节点，找到则返回
 * 该节点的地址，否则返回NULL。
 * 注意：本函数只允许传入新加
 * 入到树中的叶节点*/
Tree *imbalanced_node(Tree *node);

/* 判断失衡类型，有四种，返回
 * 0-3，分别对应LL，LR，RR，RL
 * 传入的node必须是叶节点*/
int imbalance_type(Tree *node);

/* 旋转树，使树平衡，传入不平
 * 衡节点 */
void rotate(Tree *node);

/* 传入一个叶节点，更新所有节
 * 点的高度值 */
void update_height(Tree *node);

int
main()
{
	int n = 0;
	printf("Please input size of tree: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int data = 0;
		scanf("%d", &data);
		add(data);
	}
	return 0;
}

Tree *
search(int data)
{
	Tree *pointer = root;
	while (pointer != NULL) {
		if (data > pointer->data) {
			pointer = pointer->right;
		} else if (data < pointer->data) {
			pointer = pointer->left;
		} else {
			return pointer;
		}
	}
	return NULL;
}

Tree *
where_insert(int data)
{
	Tree *pointer = root, *parent = NULL;
	while (pointer != NULL) {
		parent = pointer;
		if (data > pointer->data) {
			pointer = pointer->right;
		} else if (pointer->data > data) {
			pointer = pointer->left;
		}
	}
	return parent;
}

void
add(int data)
{
	if (root == NULL) {
		Tree *node = (Tree *)malloc(sizeof(Tree));
		node->height = 0; 
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->data = data;
		root = node;
		return ;
	}
	Tree *node = search(data);
	if (node != NULL)
		return ;
	Tree* new_node = (Tree *)malloc(sizeof(Tree));

	new_node->height = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	new_node->data = data;
	
	Tree *parent = where_insert(data);
	if (data > parent->data) {
		parent->right = new_node;
	} else {
		parent->left = new_node;
	}
	new_node->parent = parent;
	update_height(new_node);
	
	imbalanced_node(new_node);

}

int tree_delete(int data)
{
}

Tree *
imbalanced_node(Tree *node)
{
	
	
}

int 
imbalance_type(Tree *node)
{
}

void
rotate(Tree *node)
{

}

void 
update_height(Tree *node)
{
	while(node->parent != NULL) {
		node = node->parent;
		int left_height = -1;
		int right_height = -1;
		if (node->left == NULL)
			left_height = -1;
		else
			left_height = node->left->height;
		if (node->right == NULL)
			right_height = -1;
		else 
			right_height = node->right->height;
		node->height = max(left_height, right_height) + 1;
	}
}
/*
void 
LOG()
{
	Tree *pointer = root;
	while (pointer != NULL) {



	}
}
*/
