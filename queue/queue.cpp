#include<iostream>
using namespace std;

/*
单向队列
	1.先进先出。
	2.插入在队尾进行，删除在队头进行。
*/
class queue
{
public:
	queue(int capacity);
	~queue();
	bool enqueue(int element);
	bool dequeue( int& element);
	void traverse();
	void clear();
	bool is_empty() const;
	bool is_full() const;
	int get_size() const;
	
private:
	int* seq;
	int head;
	int tail;
	int size;
	int capacity;
};


queue::queue(int cap = 10)
{
	capacity = cap;
	seq = new int[cap] {0};
	head = 0;
	tail = 0;
	size = 0;
}

queue::~queue()
{
	delete[] seq;
	seq = nullptr;
}

bool queue::enqueue(int element)
{
	if (is_full())
	{
		return false;
	}
	seq[tail] = element;
	tail = tail == capacity - 1 ? 0 : tail + 1;
	size++;
	return true;
}

bool queue::dequeue(int& element)
{
	if (is_empty())
	{
		return false;
	}
	element = seq[head];
	head = head == capacity - 1 ? 0 : head + 1;
	size--;
	return true;
}

void queue::traverse()
{
	int p_head = head;
	for (int i = 0; i < size; i++)
	{
		cout << seq[p_head] << endl;
		p_head = p_head == capacity - 1 ? 0 : p_head + 1;
	}
}

void queue::clear()
{
	size = 0;
	head = 0;
	tail = 0;
}

bool queue::is_empty() const
{
	return size == 0;
}

bool queue::is_full() const
{
	return size == capacity;
}

int queue::get_size() const
{
	return size;
}
