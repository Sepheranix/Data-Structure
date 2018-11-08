#ifndef _SQ_STACK_H_
#define _SQ_STACK_H_

/*定义顺序栈*/

typedef struct {
	SElemType *base;	//基指针
	SElemType *top;		//指向栈顶指针
	int stacksize;		//当前栈的最大容量
}SqStack;

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
int GetTop(SqStack S);
Status GetTop(SqStack S, SElemType &e);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &S, SElemType &e);
Status StackTraverse(SqStack S, Status (*visit)(SElemType));
Status visit_display(SElemType e);
Status display_char(SElemType e);

#endif
