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
* ����������(binary search tree)
* �ص㣺�Һ��/ǰ����ɾ������������������������
* BST���в�����ʱ�临�Ӷ���ΪO(h),����hΪ���ĸ߶ȡ�
*/
class BST
{
public:
	BST();
	~BST();

	//�ݹ�-�������
	void recursive_preorder_traverse(TreeNode* tree);
	//�ݹ�-�������
	void recursive_inorder_traverse(TreeNode* tree);
	//�ݹ�-�������
	void recursive_postorder_traverse(TreeNode* tree);
	//����-�������
	void iterative_preorder_traverse(TreeNode* tree);
	//����-�������
	void iterative_inorder_traverse(TreeNode* tree);
	//����-�������
	void iterative_postorder_traverse(TreeNode* tree);
	//��α���
	void level_traverse(TreeNode* tree);
	//�ݹ�����
	TreeNode* recursive_search(TreeNode* tree, int value);
	//��������
	TreeNode* iterative_search(int value);
	//��Сֵ
	TreeNode* minimum(TreeNode* tree);
	//���ֵ
	TreeNode* maximum(TreeNode* tree);
	//�Һ��
	TreeNode* successor(TreeNode* tree);
	//��ǰ��
	TreeNode* predecessor(TreeNode* tree);
	//����
	void insert(int value);
	//ɾ��
	void remove(TreeNode* tree, TreeNode* node);
	//��ֲ
	void transplant(TreeNode* old_tree, TreeNode* new_tree, bool is_destory = true);
	//�ݻ�
	void destory(TreeNode* tree);
private:
	//���ڵ�
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
	//p������¼��һ�η��ʹ��Ľ��
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
	//1.tree���������ǿ�
	if (tree->right)
	{
		return minimum(tree->right);
	}
	//2.tree��������Ϊ�գ�������tree������parent��ֱ���ҵ���parent�����ӡ�
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
	//1.tree���������ǿ�
	if (tree->left)
	{
		return maximum(tree->left);
	}
	//2.tree��������Ϊ�գ�������tree������parent��ֱ���ҵ���parent���Һ��ӡ�
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
	1.��ɾ�������Ҷ�ӽ��->ֱ��ɾ����
	2.��ɾ����㲻��Ҷ�ӽڵ�
		1.��ɾ�������һ������->����ɾ�����ĺ��ӽ����������ɾ������ϡ�
		2.��ɾ���������������->�ҵ���ɾ�����ĺ�̡�
			1.���Ϊ��ɾ�������Һ���-> ���õĺ��ӽ����������ɾ������ϡ�
			2.���Ϊ��ɾ�������������е�һ�����,�Ҹý��û��������->������Ƴ�Ȼ��ƴ�ӡ�
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
			//s�����������ӡ�
			transplant(s, s->right, false);
			//ƴ��(ƴ��һ��Ҫ˫���)
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
	//��������ݻ�
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