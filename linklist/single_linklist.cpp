#include<iostream>
using namespace std;

/*
单向链表结点
*/
struct linknode
{
	int value;
	linknode* next;

	linknode(int v = 0)
	{
		value = v;
		next = nullptr;
	}
};

/*
单向链表
*/
class linklist
{
public:
	linklist();
	~linklist();

	void create(int n);
	bool insert(int element, int index);
	bool remove(int element);
	void clear();
	bool reverse();
	bool is_empty() const;
	int get_size() const;
	void traverse() const;
private:
	linknode* head;	
	int size;
};
/*
linknode* reverse(linknode* head)
{
	linknode* p_cur = head;
	linknode* p_pre = nullptr;
	linknode* temp;
	while (p_cur != nullptr)
	{
		temp = p_pre;
		p_pre = p_cur;
		p_cur = p_cur->next;
		p_pre->next = temp;
	}
	return p_pre;
}
*/

linklist::linklist()
{
	head = nullptr;
	size = 0;
}

linklist::~linklist()
{
	clear();
}

void linklist::create(int n)
{
	head = new linknode();
	linknode* p = head;
	cin >> p->value;
	size++;
	int val;
	while (cin >> val)
	{
		linknode* node = new linknode(val);
		size++;
		p->next = node;
		p = p->next;
	}
}

bool linklist::insert(int element, int index)
{
	int i = 0;
	linknode* p = head;
	while (!p && i < index)
	{
		p = p->next;
	}
	if (p || i >= index)
	{
		return false;
	}
	linknode* node = new linknode(element);
	node->next = p->next;
	p->next = node;
	return true;
}

bool linklist::remove(int element)
{
	return false;
}

void linklist::clear()
{
	linknode* p = head, *temp;
	while (!p)
	{
		temp = p->next;
		delete p;
		p = temp;
	}
	size = 0;
}

bool linklist::reverse()
{
	return false;
}

bool linklist::is_empty() const
{
	return size == 0;
}

int linklist::get_size() const
{
	return size;
}

void linklist::traverse() const
{
	linknode* p = head;
	while (p)
	{
		cout << p->value << endl;
		p = p->next;
	}
}
