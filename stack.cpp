/*
栈
	1.先进后出。
	2.插入和删除只在栈顶进行。
	3.STL默认选择deque双向队列实现，并且使用alloc内存分配，缓冲区大小为512B。
*/
class stack 
{
public:
	stack(int cap);
	~stack();

	bool push(int element) const;
	bool pop(int &element) const;
	//返回栈顶元素
	int peek() const;
	bool is_empty() const;
	bool is_full() const;
	//栈中元素个数
	int get_size() const;
private:
	int* seq;
	//栈顶
	int top;
	int capcaity;
	int size;
};