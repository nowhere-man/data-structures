/*
ջ
	1.�Ƚ������
	2.�����ɾ��ֻ��ջ�����С�
	3.STLĬ��ѡ��deque˫�����ʵ�֣�����ʹ��alloc�ڴ���䣬��������СΪ512B��
*/
class stack 
{
public:
	stack(int cap);
	~stack();

	bool push(int element) const;
	bool pop(int &element) const;
	//����ջ��Ԫ��
	int peek() const;
	bool is_empty() const;
	bool is_full() const;
	//ջ��Ԫ�ظ���
	int get_size() const;
private:
	int* seq;
	//ջ��
	int top;
	int capcaity;
	int size;
};