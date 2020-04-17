#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

constexpr auto SPACE = ' ';

struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode() : data(0), left(nullptr), right(nullptr), parent(nullptr) {}
	TreeNode(int d) : data(d), left(nullptr), right(nullptr), parent(nullptr) {}
	TreeNode(int d, TreeNode* p) : data(d), left(nullptr), right(nullptr), parent(p) {}
	TreeNode(int d, TreeNode* l, TreeNode* r, TreeNode* p) : data(d), left(l), right(r), parent(p) {}
};

/*
* 二叉搜索树(binary search tree)
* 重点：找后继/前驱、删除、迭代遍历、迭代搜索。
* BST所有操作的时间复杂都都为O(h),其中h为树的高度。
*/
class BST
{
public:
	BST();
	~BST();

	//递归-先序遍历
	void recursive_preorder_traverse(TreeNode* tree);
	//递归-中序遍历
	void recursive_inorder_traverse(TreeNode* tree);
	//递归-后序遍历
	void recursive_postorder_traverse(TreeNode* tree);
	//迭代-先序遍历
	void iterative_preorder_traverse(TreeNode* tree);
	//迭代-中序遍历
	void iterative_inorder_traverse(TreeNode* tree);
	//迭代-后序遍历
	void iterative_postorder_traverse(TreeNode* tree);
	//层次遍历
	void level_traverse(TreeNode* tree);
	//递归搜索
	TreeNode* recursive_search(TreeNode* tree, int value);
	//迭代搜索
	TreeNode* iterative_search(int value);
	//最小值
	TreeNode* minimum(TreeNode* tree);
	//最大值
	TreeNode* maximum(TreeNode* tree);
	//找后继
	TreeNode* successor(TreeNode* tree);
	//找前驱
	TreeNode* predecessor(TreeNode* tree);
	//插入
	void insert(int value);
	//删除
	void remove(TreeNode* tree, TreeNode* node);
	//移植
	void transplant(TreeNode* old_tree, TreeNode* new_tree, bool is_destory = true);
	//摧毁
	void destory(TreeNode* tree);
private:
	//根节点
	TreeNode* root;
};

BST::BST(): root(nullptr){}

BST::~BST()
{
	destory(root);
}

void BST::recursive_preorder_traverse(TreeNode* tree)
{
	if (tree != nullptr)
	{
		std::cout << tree->data << SPACE;
		recursive_preorder_traverse(tree->left);
		recursive_preorder_traverse(tree->right);
	}
}

void BST::recursive_inorder_traverse(TreeNode* tree)
{
	if (tree)
	{
		recursive_inorder_traverse(tree->left);
		std::cout << tree->data << SPACE;
		recursive_inorder_traverse(tree->right);
	}
}

void BST::recursive_postorder_traverse(TreeNode* tree)
{
	if (tree)
	{
		recursive_postorder_traverse(tree->left);
		recursive_postorder_traverse(tree->right);
		std::cout << tree->data << SPACE;
	}
}

void BST::iterative_preorder_traverse(TreeNode * tree)
{
	if (tree == nullptr)
	{
		return;
	}
	TreeNode* top;
	stack<TreeNode*> ts;
	ts.push(tree);
	while (!ts.empty())
	{
		top = ts.top();
		cout << top->data << SPACE;
		ts.pop();
		if (top->right != nullptr)
		{
			ts.push(top->right);
		}
		if (top->left != nullptr)
		{
			ts.push(top->left);
		}
	}
}

void BST::iterative_inorder_traverse(TreeNode * tree)
{
	if (tree == nullptr)
	{
		return;
	}
	TreeNode* top;
	stack<TreeNode*> ts;
	while (!ts.empty() || tree != nullptr)
	{
		if (tree != nullptr)
		{
			ts.push(tree);
			tree = tree->left;
		}
		else
		{
			top = ts.top();
			cout << top->data << SPACE;
			ts.pop();
			tree = tree->right;
		}
	}
}

void BST::iterative_postorder_traverse(TreeNode * tree)
{
	if (tree == nullptr)
	{
		return;
	}
	//p用来记录上一次访问过的结点
	TreeNode* top, *p;
	stack<TreeNode*> ts;
	ts.push(tree);
	while (!ts.empty())
	{
		if (tree != nullptr)
		{
			ts.push(tree);
			tree = tree->left;
		}
		else
		{
			top = ts.top();
			if (top->right != nullptr && top->right != p)
			{
				tree = top->right;
			}
			else
			{
				cout << top->data << SPACE;
				ts.pop();
				p = tree;
				tree = nullptr;
			}
		}
	}
}

void BST::level_traverse(TreeNode* tree)
{
	if (tree == nullptr)
	{
		return;
	}
	queue<TreeNode*> tq;
	TreeNode* cur = tree, *temp;
	tq.push(cur);
	while (!tq.empty())
	{
		temp = tq.front();
		cout << temp->data << SPACE;
		tq.pop();
		if (temp->left != nullptr)
		{
			tq.push(temp->left);
		}
		if (temp->right != nullptr)
		{
			tq.push(temp->right);
		}
	}
}

TreeNode* BST::recursive_search(TreeNode* tree, int value)
{
	if (tree == nullptr || tree->data == value)
		return tree;
	return tree->data > value
		? recursive_search(tree->left, value)
		: recursive_search(tree->right, value);
}

TreeNode* BST::iterative_search(int value)
{
	TreeNode *cur = root;
	while (cur != nullptr)
	{
		if (cur->data > value)
		{
			cur = cur->left;
		}
		else if (cur->data < value)
		{
			cur = cur->right;
		}
		else
		{
			return cur;
		}
	}
	return nullptr;
}

TreeNode* BST::minimum(TreeNode* tree)
{
	if (!tree)
	{
		return tree;
	}
	while (tree->left)
	{
		tree = tree->left;
	}
	return tree;
}

TreeNode* BST::maximum(TreeNode* tree)
{
	if (!tree)
	{
		return tree;
	}
	while (tree->right)
	{
		tree = tree->right;
	}
	return tree;
}

TreeNode* BST::successor(TreeNode* tree)
{
	if (!tree)
		return nullptr;
	//1.tree的右子树非空
	if (tree->right)
	{
		return minimum(tree->right);
	}
	//2.tree的右子树为空，则沿着tree向上找parent，直到找到该parent有左孩子。
	TreeNode* p = tree->parent;
	while (p && (tree == p->right))
	{
		tree = p;
		p = p->parent;
	}
	return p;
}

TreeNode* BST::predecessor(TreeNode* tree)
{
	if (!tree)
		return nullptr;
	//1.tree的左子树非空
	if (tree->left)
	{
		return maximum(tree->left);
	}
	//2.tree的左子树为空，则沿着tree向上找parent，直到找到该parent有右孩子。
	TreeNode* p = tree->parent;
	while (p && (tree == p->left))
	{
		tree = p;
		p = p->parent;
	}
	return p;
}

void BST::insert(int value)
{
	TreeNode* cur = root, *par;
	if (cur == nullptr)
	{
		root = new TreeNode(value, nullptr, nullptr, nullptr);
		return;
	}
	while (cur != nullptr)
	{
		par = cur;
		cur = cur->data > value ? cur->left : cur->right;
	}
	cur = new TreeNode(value, nullptr, nullptr, par);
	if (par->data > value)
	{
		par->left = cur;
	}
	else
	{
		par->right = cur;
	}
}

void BST::remove(TreeNode* tree, TreeNode* node)
{
	/*
	1.待删除结点是叶子结点->直接删除。
	2.待删除结点不是叶子节点
		1.待删除结点有一个孩子->将待删除结点的孩子结点提升到待删除结点上。
		2.待删除结点有两个孩子->找到待删除结点的后继。
			1.后继为待删除结点的右孩子-> 将该的孩子结点提升到待删除结点上。
			2.后继为待删除结点的右子树中的一个结点,且该结点没有左子树->将后继移出然后拼接。
	*/
	if (node->left == nullptr && node->right == nullptr)
	{
		transplant(node, nullptr);
	}
	else if(node->left == nullptr || node->right == nullptr)
	{
		TreeNode* child = node->left == nullptr ? node->right : node->left;
		transplant(node, child);
	}
	else
	{
		TreeNode* s = successor(node);
		if (s->parent != node)
		{
			//s不可能有左孩子。
			transplant(s, s->right, false);
			//拼接(拼接一定要双向绑定)
			s->right = node->right;
			s->right->parent = s;
		}
		transplant(node, s, false);
		s->left = node->left;
		s->left->parent = s;
		delete node;
	}
}

void BST::transplant(TreeNode* old_tree, TreeNode* new_tree, bool is_destory)
{
	if (old_tree->parent == nullptr)
	{
		root = new_tree;
	}
	else
	{
		TreeNode* par = old_tree->parent;
		if (par->left == old_tree)
		{
			par->left = new_tree;
		}
		else
		{
			par->right = new_tree;
		}
		if (new_tree != nullptr)
		{
			new_tree->parent = par;
		}
	}
	if (is_destory)
	{
		destory(old_tree);
	}
}

void BST::destory(TreeNode* tree)
{
	//后序遍历摧毁
	if (tree == nullptr)
	{
		return;
	}
	if (tree->left != nullptr)
	{
		destory(tree->left);
	}
	if (tree->right != nullptr)
	{
		destory(tree->right);
	}
	delete tree;
	tree = nullptr;
}