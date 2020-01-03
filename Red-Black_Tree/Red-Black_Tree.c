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
	int color;
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

/*传入数据，插入数据到当前树中*/
void add(int data);

/*旋转*/
void rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3);

void LOG(Tree *root);

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
}	

void 
add(int data)
{
	//根为空，直接插入
	if (root == NULL) {
		root = (Tree *)malloc(sizeof(Tree));
		root->parent = NULL;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		root->color = 0;
		return ;
	}

	//已经有了，直接返回
	if (NULL != search(data)) {
		return ;
	}

	//查找插入点
	Tree *parent = where_insert(data);

	//创建节点
	Tree *node = (Tree *)malloc(sizeof(Tree));
	node->color = 1;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->data = data;

	//父节点是黑色，直接插入
	if (parent->color == 0) {
		if (parent->data > data)
			parent->right = node;
		else 
			parent->left = node;
		return ;
	}

	//找到叔叔节点，和爷爷节点
	Tree *grandpa = parent->parent;
	Tree *uncle = (parent == grandpa->left ? grandpa->right : grandpa->left);

	//如果叔叔节点不为空，可以确定必叔叔为红色，因为父节点黑色的情况已经处理过了，叔叔节点与父节点同色。向上变色直到平衡
	if (uncle != NULL) {
		if (node->data > parent->data)
			parent->right = node;
		else
			parent->left = node;
		do {
			//变色
			grandpa->color = 1;
			parent->color = 0;
			uncle->color = 0;

			//判断爷爷和爷爷的父节点是否为根，做特殊处理
			//由于根节点必须是黑色，所以如果爷爷节点是根
			//节点，则置为黑色
			if (grandpa == root) {
				grandpa->color = 0;
				break;
			}
			if (grandpa->parent == root) {
				break;
			}

			//将当前插入节点指向爷爷节点，继续向上做变色操作
			node = grandpa;
			parent = node->parent;
			grandpa = parent->parent;
		} while (node->parent->color == 1);
	}

	//如果叔叔节点不存在，需要进行旋转
	if (uncle == NULL) {
		if (node->data > parent->data) {

		} else {

		}
	}
}

int
tree_delete()
{

	return 0;
}

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
		goto RETURN;
	}
	printf("How many nodes do you want to delete?");
	scanf("%d", &del_num);
	if (del_num > n) {
		printf("Not so many nodes");
		goto RETURN;
	}
	for (int i = 0; i < del_num; i++) {
		int data = 0;
		scanf("%d", &data);
		tree_delete(data);
	}

RETURN:	LOG(root);

	return 0;
}

void 
LOG(Tree *ptr_root)
{
	if (ptr_root != NULL) {
		LOG(ptr_root->left);
		printf("%d   ", ptr_root->data);
		LOG(ptr_root->right);
	}
}
