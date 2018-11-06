#include "headers.h"

/**
 * ����һ����ջS
 */
Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		return ERROR;  /* �洢����ʧ�� */
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
} // InitStack

/**
 * ����ջS��S���ٴ���
 */
Status DestroyStack(SqStack &S)
{
	free(S.base);
	S.base = NULL;
	return 0;
}

/**
 * ��S��Ϊ��ջ
 */
Status ClearStack(SqStack &S)
{
	S.top = S.base;
	return 0;
}

/**
 * ��ջSΪ�գ�����TRUE�� ���򷵻�FALSE
 */
Status StackEmpty(SqStack S)
{
	return (S.base == S.top) ? TRUE : FALSE;
}

/**
 * ����S��Ԫ�ظ�������ջ�ĳ���
 */
int StackLength(SqStack S)
{
	return (S.top - S.base);
}

/**
 * ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK������ERROR
 */
Status GetTop(SqStack S, SElemType &e)
{
	if (S.base == S.top)  //ջΪ��
		return ERROR;
	e = *(S.top - 1);  //ջ��Ԫ�ظ���e
	return OK;
}

/**
 * ����Ԫ��eΪ�µ�ջ��Ԫ��
 */
Status Push(SqStack &S, SElemType e)
{
	if (S.stacksize == StackLength(S)) {   //ջ�ﵽ������������Զ���������
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
			return ERROR;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return OK;
}

/**
 * ��ջ���գ�ɾ��Sջ��Ԫ�أ���e������ֵ
 */
Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base)  // ջΪ��
		return ERROR;
	e = *(S.top - 1);
	S.top--;
	return OK;
}

/**
 * ��ջ�׵�ջ��ÿ��Ԫ�����ε���visit(), һ��visitʧ�ܣ������ʧ��
 */
Status StackTraverse(SqStack S, Status(*visit)(SElemType))
{
	SElemType *p;
	p = S.base;   //pָ��ջ��
	while (p != S.top) {  //����ջ��Ԫ��
		visit(*p);
		p++;
	}
	return OK;
}

/**
 * ��ӡԪ��
 */
Status visit_display(SElemType e)
{
	//	printf("%d ", e);
	return OK;
}

Status print_path(SElemType e)
{
	printf_s("(%d, %d)\n", e.seat.row, e.seat.col);
	return OK;
}