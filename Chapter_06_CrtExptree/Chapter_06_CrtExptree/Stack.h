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
	Stack() :cap(SIZE), len(0)    //容量限制
	{
		if (cap == len) throw 1;

		buff = new T[cap];

	}

	~Stack()   //析构
	{
		delete[]buff;
		len = 0;
		cap = 0;
	}

	void clean()   //清空
	{
		len = 0;
	}

	int size(void)   //获取长度
	{
		return len;
	}

	T &operator[](int n)   //重载下标运算
	{
		if (n < 0 || n >= len) throw 2;

		return buff[n];
	}

	void push(const T &data)  //入栈
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

	void pop(T &data)		//出栈
	{
		int i = 0;
		data = buff[len];
		for (i = 0; i < len; ++i)
		{
			buff[i] = buff[i + 1];
		}

		--len;
	}

	bool empty()  //判空
	{
		return !len;
	}

	bool top(T &e)   //获取栈顶
	{
		if (buff != NULL) {
			e = buff[len];
			return true;
		}
		else
			return false;
			

	}
	/*	链栈

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
			Stack(int cap):cap(cap), len(0)  //容量限制
			{
				Node *node = new Node;
				node -> next = NULL;
				this -> head = node;
			}

			Stack():cap(-1), len(0)   // 无容量限制
			{
				Node *node = new Node;
				node -> next = NULL;
				this -> head = node;
			}
			~Stack()   //析构
			{
				Node * p = NULL;
				while(head != NULL)
				{
					p = head -> next;
					delete head;
					head = p;
				}
			}
			void push(const T &data)    //入栈
			{
				if(len == cap)  throw 1;  // 抛出异常1
				Node *node = new Node;
				node -> data = data;
				node -> next = head -> next;
				head -> next = node;
				++len;
			}
			void pop(void)   //出栈
			{
				if(head -> next == NULL)  throw 1;
				Node *p = NULL;
				p = head -> next -> next;
				delete head -> next;
				head -> next = p;
				--len;
			}
			bool empty(void)	//判空
			{
				return !(head -> next);
			}
			T &top(void) const	//获得栈顶
			{
				return head -> next;
			}
			int size()//获得长度
			{
				return len;
			}
	*/

	//顺序栈
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
//	T *base;	//基指针
//	T *top;		//指向栈顶指针
//	int stacksize;	//当前栈的最大容量
//};
