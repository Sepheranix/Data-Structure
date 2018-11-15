#pragma once

#include <iostream>
#include <cstring>

template <typename T>
class Stack
{
private:
	T *buff;
	int cap;
	int len;

	enum { SIZE = 10 };

public:
	Stack() :cap(SIZE), len(0)    //��������
	{
		if (cap == len) throw 1;

		buff = new T[cap];

	}

	~Stack()   //����
	{
		delete[]buff;
		len = 0;
		cap = 0;
	}

	void clean()   //���
	{
		len = 0;
	}

	int size(void)   //��ȡ����
	{
		return len;
	}

	T &operator[](int n)   //�����±�����
	{
		if (n < 0 || n >= len) throw 2;

		return buff[n];
	}

	void push(const T &data)  //��ջ
	{
		if (len == cap)
		{
			cap = 3 * cap;
			T *p = new T[cap];
			memcpy(p, buff, len * sizeof(T));
			delete buff;

			buff = p;
		}

		int i = 0;

		for (i = len; i > 0; --i)
		{
			buff[i] = buff[i - 1];
		}
		buff[0] = data;
		++len;

	}

	void pop(T &data)		//��ջ
	{
		int i = 0;
		data = buff[len];
		for (i = 0; i < len; ++i)
		{
			buff[i] = buff[i + 1];
		}

		--len;
	}

	bool empty()  //�п�
	{
		return !len;
	}

	bool top(T &e)   //��ȡջ��
	{
		if (buff != NULL) {
			e = buff[len];
			return true;
		}
		else
			return false;
			

	}
	/*	��ջ

	private:
			struct Node
			{
				T data;
				Node *next;
				int len;
				int cap;
			};

			Node *head;
	public:
			Stack(int cap):cap(cap), len(0)  //��������
			{
				Node *node = new Node;
				node -> next = NULL;
				this -> head = node;
			}

			Stack():cap(-1), len(0)   // ����������
			{
				Node *node = new Node;
				node -> next = NULL;
				this -> head = node;
			}
			~Stack()   //����
			{
				Node * p = NULL;
				while(head != NULL)
				{
					p = head -> next;
					delete head;
					head = p;
				}
			}
			void push(const T &data)    //��ջ
			{
				if(len == cap)  throw 1;  // �׳��쳣1
				Node *node = new Node;
				node -> data = data;
				node -> next = head -> next;
				head -> next = node;
				++len;
			}
			void pop(void)   //��ջ
			{
				if(head -> next == NULL)  throw 1;
				Node *p = NULL;
				p = head -> next -> next;
				delete head -> next;
				head -> next = p;
				--len;
			}
			bool empty(void)	//�п�
			{
				return !(head -> next);
			}
			T &top(void) const	//���ջ��
			{
				return head -> next;
			}
			int size()//��ó���
			{
				return len;
			}
	*/

	//˳��ջ
};

















//#define STACK_INIT_SIZE 100
//#define STACKINCREAMENT 10
//
//
//template<class T>
//class Stack
//{
//public:
//	Stack(){}
//	virtual ~Stack(){}
//
//	virtual void Push(const T& e) = 0;
//	virtual bool Pop(T& e) = 0;
//	virtual bool GetTop(T& e)const = 0;
//	virtual bool Empty()const = 0;
//	virtual int Length()const = 0;
//};
//
//template<class T>
//class SqStack :public Stack<T>
//{
//public:
//	SqStack()
//	{
//		base = (T*)malloc(STACK_INIT_SIZE * sizeof(SqStack));
//		top = base;
//		stacksize = STACK_INIT_SIZE;
//	}
//	~SqStack()
//	{
//		free(base);
//		base = NULL;
//	}
//	//SqStack(const SqStack<T>& rhs);
//	//SqStack<T>& operator=(const SqStack<T>& rhs);
//	
//
//	void Push(const T& e);
//	bool Pop(T& e);
//	bool GetTop(T& e)const;
//	bool Empty()const;	
//	int Length()const;
//	void Clear();
//	bool Traverse(bool(*visit)(T))const;
//
//	//friend ostream& operator << (ostream& out, const SqStack<T> &rhs);	
//	
//private:
//	T *base;	//��ָ��
//	T *top;		//ָ��ջ��ָ��
//	int stacksize;	//��ǰջ���������
//};
