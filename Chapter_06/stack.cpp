/*ʵ��˳��ջ�Ļ�������*/

#include "headers.h"

/*����һ����ջ*/
Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SqStack));
	if (!S.base)
		return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


/*����ջS,S���ٴ���*/
Status DestroyStack(SqStack &S)
{
	free(S.base);
	S.base = NULL;
	return 0;
}

/*��S��Ϊ��ջ*/
Status ClearStack(SqStack &S)
{
	S.top = S.base;
	return 0;
}

/*��ջSΪ�գ�����TRUE�� ���򷵻�FALSE*/
Status StackEmpty(SqStack S)
{
	return (S.base == S.top) ? TRUE : FALSE;
}

/*����S��Ԫ�ظ�������ջ�ĳ���*/
int StackLength(SqStack S)
{
	return (S.top - S.base);
}

/*��ջ���գ�����e����S��ջ��Ԫ�أ�������OK������ERROR*/
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

/*����Ԫ��eΪ�µ�ջ��Ԫ��*/
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

/*��ջ���գ�ɾ��Sջ��Ԫ�أ���e������ֵ*/
Status Pop(SqStack &S, SElemType &e)
{
	if (StackEmpty(S))
		return ERROR;
	e = *(S.top - 1);
	S.top--;
	return OK;
}

/*��ջ�׵�ջ��ÿ��Ԫ�����ε���visit(), һ��visitʧ�ܣ������ʧ��*/
Status StackTraverse(SqStack S, Status(*visit)(SElemType))
{
	SElemType *p = S.base;
	while (p != S.top) {
		visit(*p);
		p++;
	}
	return OK;
}

///*��ӡԪ��*/
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