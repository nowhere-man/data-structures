/*
˫��������
*/
#include<iostream>
#include <algorithm>
struct dnode
{
	int data;
	dnode* prev;
	dnode* next;

	dnode(int d) :data(d), prev(nullptr), next(nullptr) {}
	dnode(int d, dnode* p, dnode* n) :data(d), prev(p), next(n) {}
};

/*
˫������
*/
class dlinklist
{
public:
	dlinklist();
	~dlinklist();

	//��������
	void create();
	//��ӡ����
	void print();
	//�ݻ�����
	void destory();
	//�ж������Ƿ�Ϊ��
	bool empty(); 
	//��β����Ԫ��
	void push_back(int val); 
	//��ͷ����Ԫ��
	void push_front(int val); 
	//ָ��λ�ò���Ԫ��
	bool insert(int index, int val);
	//��βɾ��Ԫ��
	void pop_back();
	//��ͷɾ��Ԫ��
	void pop_front(); 
	//ָ��λ��ɾ��Ԫ��
	bool remove(int index);
	//���ر�ͷԪ��
	dnode* front(); 
	//���ر�βԪ��
	dnode* back(); 
	//���ر�Ԫ�ظ���
	int size(); 
	//���ص�һ��ֵΪk�Ľ��
	dnode* search(dnode* head, int value);
	//��ת����
	void invert();
private:
	dnode* head;
	dnode* tail;
};

dlinklist::dlinklist() :head(nullptr), tail(nullptr) {}

dlinklist::~dlinklist()
{
	destory();
}

void dlinklist::create()
{
	head = new dnode(0);
	std::cin >> head->data;
	dnode* cur = head, *prev = head;
	int val;
	while (std::cin >> val && val != -1)
	{
		cur = new dnode(val);
		cur->prev = prev;
		prev->next = cur;
		prev = cur;
	}
	tail = cur;
}

void dlinklist::print()
{
	dnode* cur = head;
	while (cur != nullptr)
	{
		std::cout << cur->data << ' ';
		cur = cur->next;
	}
	std::cout << std::endl;
}

void dlinklist::destory()
{
	dnode* cur = head, *next;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
	head = tail = nullptr;
}

bool dlinklist::empty()
{
	return head == nullptr;
}

void dlinklist::push_back(int val)
{
	if (tail == nullptr)
	{
		head = tail = new dnode(val);
	}
	else
	{
		tail->next = new dnode(val, tail, nullptr);
		tail = tail->next;
	}
	
}

void dlinklist::push_front(int val)
{
	if (head == nullptr)
	{
		head = tail = new dnode(val);
	}
	else
	{
		head->prev = new dnode(val, nullptr, head);
		head = head->prev;
	}
}

bool dlinklist::insert(int index, int val) 
{
	dnode* cur = head;
	int i = 0;

	//�����ͷ
	if (index == 0)
	{
		push_front(val);
		return true;
	}
	while (cur != nullptr && i < index)
	{
		cur = cur->next;
		i++;
	}
	//���뵽����
	if (cur != nullptr && i == index)
	{
		dnode* insert_node = new dnode(val, cur->prev, cur);
		cur->prev->next = insert_node;
		cur->prev = insert_node;
		return true;
	}
	//�嵽��β
	else if (cur == nullptr && i == index)
	{
		push_back(val);
		return true;
	}
	else
	{
		return false;
	}
}

void dlinklist::pop_back()
{
	if (!empty())
	{
		if (tail->prev == nullptr)
		{
			delete tail;
			head = tail = nullptr;
		}
		else
		{
			dnode* temp = tail->prev;
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
	}
}

void dlinklist::pop_front()
{
	if (!empty())
	{
		if (head->next == nullptr)
		{
			delete tail;
			head = tail = nullptr;
		}
		else
		{
			dnode* temp = head->next;
			delete head;
			head = temp;
			head->prev = nullptr;
		}
	}
}

bool dlinklist::remove(int index)
{
	dnode* cur = head;
	int i = 0;
	while (cur != nullptr && i < index)
	{
		cur = cur->next;
		i++;
	}
	if (cur != nullptr && i == index)
	{
		//ɾ��Ԫ���ڱ�ͷ
		if (cur->prev == nullptr)
		{
			pop_front();
		}
		//ɾ��Ԫ���ڱ�β
		else if (cur->next == nullptr)
		{
			pop_back();
		}
		//ɾ��Ԫ���ڱ���
		else
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			delete cur;
		}
		return true;
	}
	else
	{
		return false;
	}
}

dnode* dlinklist::front()
{
	return head;
}

dnode* dlinklist::back()
{
	return tail;
}

int dlinklist::size()
{
	dnode* cur = head;
	int size = 0;
	while (cur)
	{
		cur = cur->next;
		size++;
	}
	return size;
}

dnode* dlinklist::search(dnode* head, int value)
{
	dnode* cur = head;
	while (cur != nullptr && cur->data != value)
	{
		cur = cur->next;
	}
	return cur;
}

void dlinklist::invert()
{
	if (!empty())
	{
		dnode* cur = head, *temp;
		while (cur != nullptr)
		{
			temp = cur;
			cur = cur->next;
			std::swap(temp->prev, temp->next);
		}
		std::swap(head, tail);
	}
}

int main()
{
	dlinklist dll;
	dll.create();
	dll.print();
	dll.invert();
	dll.invert();
	dll.print();
	dll.insert(0, 0);
	dll.print();
	dll.remove(5);
	dll.print();
	system("pause");
}

