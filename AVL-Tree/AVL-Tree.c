#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

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
 * 该节点的地址，否则返回NULL。*/
Tree *imbalanced_node(Tree *node);

/* 判断失衡类型，有四种，返回
 * 0-3，分别对应LL，LR，RR，RL
 * 传入的node必须是不平衡节点*/
int imbalance_type(Tree *imb_node);

/* 旋转树，使树平衡，传入不平
 * 衡节点和不平衡类型 */
void rotate(Tree *node, int type);
void rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3);

/* 传入一个节点，更新所有节
 * 点的高度值 */
void update_height(Tree *node);

int
main()
{
	int n = 0, is_del = 0, del_num = 0;
	printf("Please input size of tree: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int data = 0;
		scanf("%d", &data);
		add(data);
	}
	getchar();

	printf("Do you want delete nodes? (y/n)");
	is_del = getchar();
	if (0x59 != is_del && 0x79 != is_del) {
		return 0;
	}
	printf("How many nodes do you want to delete?");
	scanf("%d", &del_num);
	if (del_num > n) {
		printf("Not so many nodes");
	}
	for (int i = 0; i < del_num; i++) {
		int data = 0;
		scanf("%d", &data);
		tree_delete(data);
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

	Tree *imbalanced_tree = imbalanced_node(new_node);
	if (imbalanced_tree == NULL)
		return ;
	int type = imbalance_type(imbalanced_tree);

	rotate(imbalanced_tree, type);
}

int tree_delete(int data)
{
	/*
	Tree *node = search(data);
	if (node == NULL) {
		return -1;
	}
	Tree *parent = node->parent;
	if (node->left == node->right && node->left == NULL) {
		if (parent == NULL) {
			free(node);
			return 0;
		}
		if (parent->left == node) {
			parent->left = NULL;
		} else {
			parent->right = NULL;
		}
		free(node);
		update_height(parent);
		return 0;
	}
	*/
	reutrn 0;
}

Tree *
imbalanced_node(Tree *node)
{
	while(node->parent != NULL)
	{
		node = node->parent;
		int right_height = -1;
		int left_height = -1;

		if (node->right != NULL)
			right_height = node->right->height;

		if (node->left != NULL)
			left_height = node->left->height;

		if (abs(left_height - right_height) >= 2)
			return node;

	}
	return NULL;
}

int 
imbalance_type(Tree *node)
{
	Tree *child = NULL;
	int L1, L2, R1, R2;
	L1 = (node->left == NULL ? -1 : node->left->height);
	R1 = (node->right == NULL ? -1 : node->right->height);
	child = (L1 > R1 ? node->left : node->right);

	L2 = (child->left == NULL ? -1 : child->left->height);
	R2 = (child->right == NULL ? -1 : child->right->height);

	if (L1 > R1 && L2 > R2)
		return 0;
	else if (L1 > R1 && L2 < R2)
		return 1;
	else if (L1 < R1 && L2 > R2)
		return 2;
	else if (L1 < R1 && L2 < R2)
		return 3;
}

void
rotate(Tree *node, int type)
{
	if (type == 0) {
		Tree *leaf = node->left->left;
		Tree *parent = node->left;
		Tree *grandpa = node;
		parent->parent = grandpa->parent;
		if (grandpa->parent != NULL) {
			if (grandpa->parent->left == grandpa) {
				grandpa->parent->left = parent;
			} else {
				grandpa->parent->right = parent;
			}
		} else {
			root = parent;
		}
		rotate34(leaf, parent, grandpa, leaf->left, leaf->right, parent->right, grandpa->right);
	} else if (type == 1) {
		Tree *leaf = node->left->right;
		Tree *parent = node->left;
		Tree *grandpa = node;
		leaf->parent = grandpa->parent;
		if (grandpa->parent != NULL) {
			if (grandpa->parent->left == grandpa) {
				grandpa->parent->left = leaf;
			} else {
				grandpa->parent->right = leaf;
			}
		} else {
			root = leaf;
		}
		rotate34(parent, leaf, grandpa, parent->left, leaf->left, leaf->right, grandpa->right);
	} else if (type == 2) {
		Tree *leaf = node->right->left;
		Tree *parent = node->right;
		Tree *grandpa = node;
		leaf->parent = grandpa->parent;
		if (grandpa->parent != NULL) {
			if (grandpa->parent->left == grandpa) {
				grandpa->parent->left = leaf;
			} else {
				grandpa->parent->right = leaf;
			}
		} else {
			root = leaf;
		}
		rotate34(grandpa, leaf, parent, grandpa->left, leaf->left, leaf->right, parent->right);
	} else if (type == 3) {
		Tree *leaf = node->right->right;
		Tree *parent = node->right;
		Tree *grandpa = node;
		parent->parent = grandpa->parent;
		if (grandpa->parent != NULL) {
			if (grandpa->parent->left == grandpa) {
				grandpa->parent->left = parent;
			} else {
				grandpa->parent->right = parent;
			}
		} else {
			root = parent;
		}
		rotate34(grandpa, parent, leaf, grandpa->left, parent->left, leaf->left, leaf->right);
	}
}

void 
rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3)
{
	b->left = a;
	b->right = c;
	a->parent = b;
	a->left = t0;
	if (t0 != NULL) t0->parent = a;
	a->right = t1;
	if (t1 != NULL) t1->parent = a;
	c->parent = b;
	c->left = t2;
	if (t2 != NULL) t2->parent = c;
	c->right = t3;
	if (t3 != NULL) t3->parent = c;
	
	update_height(a);
	update_height(c);

	update_height(b);
}

void 
update_height(Tree *node)
{
	while(node->parent != NULL) {
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
		node = node->parent;
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
