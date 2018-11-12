/*实现顺序栈的基本操作*/

#include "headers.h"

/*构造一个空栈*/
Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SqStack));
	if (!S.base)
		return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


/*销毁栈S,S不再存在*/
Status DestroyStack(SqStack &S)
{
	free(S.base);
	S.base = NULL;
	return 0;
}

/*把S置为空栈*/
Status ClearStack(SqStack &S)
{
	S.top = S.base;
	return 0;
}

/*若栈S为空，返回TRUE， 否则返回FALSE*/
Status StackEmpty(SqStack S)
{
	return (S.base == S.top) ? TRUE : FALSE;
}

/*返回S的元素个数，即栈的长度*/
int StackLength(SqStack S)
{
	return (S.top - S.base);
}

/*若栈不空，则用e返回S的栈顶元素，并返回OK，否则ERROR*/
Status GetTop(SqStack S, SElemType &e)
{
	if (S.base == S.top)
		return ERROR;
	e = *(S.top - 1);
	return OK;
}

SElemType GetTop(SqStack S)
{
	return *(S.top - 1);
}

/*插入元素e为新的栈顶元素*/
Status Push(SqStack &S, SElemType e)
{
	if (StackLength(S) >= S.stacksize)
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
	if (!S.base)
		return ERROR;
	*S.top = e;
	S.top++;
	return OK;
}

/*若栈不空，删除S栈顶元素，用e返回其值*/
Status Pop(SqStack &S, SElemType &e)
{
	if (StackEmpty(S))
		return ERROR;
	e = *(S.top - 1);
	S.top--;
	return OK;
}

/*从栈底到栈顶每个元素依次调用visit(), 一旦visit失败，则操作失败*/
Status StackTraverse(SqStack S, Status(*visit)(SElemType))
{
	SElemType *p = S.base;
	while (p != S.top) {
		visit(*p);
		p++;
	}
	return OK;
}

///*打印元素*/
//Status visit_display(SElemType e)
//{
//	printf_s("%d ", e);
//	return OK;
//}
//
//Status display_char(SElemType e)
//{
//	printf_s("%c", e);
//	return OK;
//}