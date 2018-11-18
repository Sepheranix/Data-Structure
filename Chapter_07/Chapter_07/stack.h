#pragma once

/* ����˳��ջ */

typedef int SElemType;
typedef int Status;

typedef struct {
	SElemType *base; //��ָ��
	SElemType *top;  //ָ��ջ����ָ��
	int stacksize;   //��ǰջ���������
}SqStack;

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S, SElemType &e);
int GetTop(SqStack S);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &S, SElemType &e);
Status StackTraverse(SqStack S, Status(*visit)(SElemType));