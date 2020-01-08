#include <stdio.h>
#include <malloc.h>

#define INPUT_DATA

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

int search(int data, Tree *node);


/*传入数据，插入数据到当前树中*/
void add(int data);

/*旋转*/
void rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3);

int tree_delete(int data);

void LOG(Tree *root);

void add_rebalance(Tree *node, Tree *parent, Tree *grandpa, Tree *uncle);

void del_rebalance(Tree *node, int type);

int
search(int data, Tree *node)
{
	Tree *pointer = root, *parent = NULL;
	while (pointer != NULL) {
		parent = pointer;
		if (data > pointer->data) {
			pointer = pointer->right;
		} else if (pointer->data > data) {
			pointer = pointer->left;
		} else {
			node = pointer;
			return 0;
		}
	}
	node = parent;
	return 1;
}

void 
rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3)
{
	b->color = 0;
	a->color = 1;
	c->color = 1;
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
	Tree *search_temp = NULL;
	Tree *parent;
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

	//查找插入点
	if (0 == search(data, parent)) {
		return ;
	}

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
			parent->left = node;
		else 
			parent->right = node;
		return ;
	}

	//找到叔叔节点，和爷爷节点
	Tree *grandpa = parent->parent;
	Tree *uncle = (parent == grandpa->left ? grandpa->right : grandpa->left);

	//将节点加入树中
	if (node->data > parent->data)
		parent->right = node;
	else
		parent->left = node;

	//平衡性检查和修正
	add_rebalance(node, parent, grandpa, uncle);

	return ;
}

void 
add_rebalance(Tree *node, Tree *parent, Tree *grandpa, Tree *uncle)
{
	do {
		int yesorno = 0;
		if (uncle != NULL) {
			if (uncle->color == 1)
				yesorno = 1;
		}
		if (yesorno) {     //情景一：如果叔叔节点存在且为红色，则进行变色
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
			node = grandpa;
	
		} else {          //情景二：如果叔叔节点不存在或为黑色，则需要进行旋转
			if (grandpa->left == parent && node->data > parent->data) { //LL
				parent->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = parent;
					else
						grandpa->parent->right = parent;
				} else {
					root = parent;
				}
				rotate34(node, parent, grandpa, node->left, node->right, parent->right, grandpa->right);
				node = parent;
			} else if (grandpa->left == parent && node->data < parent->data) { //LR
				node->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = node;
					else
						grandpa->parent->right = node;
				} else {
					root = node;
				}
				rotate34(parent, node, grandpa, parent->left, node->left, node->right, grandpa->right);
			} else if (grandpa->right == parent && node->data < parent->data) { //RL 
				node->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = node;
					else
						grandpa->parent->right = node;
				} else {
					root = node;
				}
				rotate34(grandpa, node, parent, grandpa->left, node->left, node->right, parent->right);
			} else if (grandpa->right == parent && node->data > parent->data) { //RR
				parent->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = parent;
					else
						grandpa->parent->right = parent;
				} else {
					root = parent;
				}
				rotate34(grandpa, parent, node, grandpa->left, parent->left, node->left, node->right);
				node = parent;
			}
		}
		parent = node->parent;
		if (parent == NULL || parent == root)
			break;
		grandpa = parent->parent;
		uncle = (parent == grandpa->left ? grandpa->right : grandpa->left);
	} while (node->parent->color == 1 && node->color == 1);
}

//删除函数尚未写完，是不完整的
int
tree_delete(int data)
{
	Tree *node = NULL;
	Tree *child = NULL;
	Tree *parent = NULL;

	if (1 == search(data, node)) {
		return 0;
	}
	parent = node->parent;

	//如果删除的节点有左右孩子，寻找前驱节点，并置换位置
	if (node->left != NULL && node->right != NULL) { 
		Tree *pointer = node->left;
		while(pointer->right != NULL) {
			pointer = pointer->right;
		}
		node->data = pointer->data;
		node = pointer;
		parent = node->parent;
	}

	if (node->left != node->right) { 
		//被删除的节点有一个子节点，则将子节点代替删除节点，
		//并将替换后的节点置为黑色。注意：因为只有一个子节点，
		//所以该节点只能是黑色，其子节点只能是红色，否则会破
		//坏黑色完美平衡
		if (node->left != NULL)
			child = node->left;
		else
			child = node->right;

		if (parent != NULL) {
			if (node == parent->left)
				parent->left = child;
			else
				parent->right = child;
		} else {
			root = child;
		}
		child->color = 0;
		child->parent = parent;

		free(node);
		return 0;
	}
	//叶节点，删除，如果节点是红色，直接返回，否则进行再平衡
	if (node->left == node->right) { 
		if (parent == NULL) {
			root = NULL;
			free(node);
			return 0;
		}
		if (node->color == 1) {
			if (parent->left == node)
				parent->left = NULL;
			else
				parent->right = NULL;
			free(node);
			return 0;
		} else {



		}
	}
	return 0;
}

int
main()
{
#ifdef INPUT_DATA
	int n = 0, is_del = 0, del_num = 0;
	printf("Please input size of tree: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int data = 0;
		scanf("%d", &data);
		add(data);
	}
	getchar();
#else
	int test_data[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int n = 16, is_del = 0, del_num = 0;
	for (int i = 0; i < n; i++) {
		add(test_data[i]);
	}
#endif
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
