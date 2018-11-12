#include "headers.h"

/*��ά��dim�Ϸ��� �͸�ά���ȺϷ���������Ӧ����A��������OK*/
Status InitArray(Array &A, int dim, ...)
{
	va_list ap;
	int elemtotal = 1;	//���������Ԫ�ظ���
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;	
	A.dim = dim;
	A.bounds = (int *)malloc(dim * sizeof(int));
	if (!A.bounds)
		exit(OVERFLOW);	//����ά���ȺϷ��������A.bounds�������A��Ԫ������elemtotal
	va_start(ap, dim);	//apΪva_list���ͣ��Ǵ�ű䳤��������Ϣ������
	for (int i = 0; i < dim; i++) {
		A.bounds[i] = va_arg(ap, int);	//����һ���䳤����
		if (A.bounds[i] < 0)
			return UNDERFLOW;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if (!A.base)
		exit(OVERFLOW);
	//��ӳ�����ĳ���c��������A.constants[i - 1], i = 1, ..., dim
	A.constants = (int *)malloc(dim * sizeof(int));
	if (!A.constants)
		exit(OVERFLOW);
	A.constants[dim - 1] = 1;	//L = 1��ָ���������Ԫ�صĴ�СΪ��λ
	for (int i = dim - 2; i > 0; --i)
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	return OK;
}

/*��������A*/
Status DestroyArray(Array &A)
{
	if (!A.base)	return ERROR;
	free(A.base);	A.base = NULL;
	if (!A.bounds)	return ERROR;
	free(A.bounds);	A.bounds = NULL;
	if (!A.constants)	return ERROR;
	free(A.constants);	A.constants = NULL;
	return OK;
}

/*��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�ж�Ӧ�ĵ�ַoff*/
Status Locate(Array A, va_list ap, int &off)
{
	off = 0;
	for (int i = 0; i < A.dim; i++)
	{
		int ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i])
			return OVERFLOW;
		off += A.constants[i] * ind;
	}
	return OK;
}

/*A��nά���飬eάԪ�ر����������n���±�ֵ��
�����±겻���磬��e��ֵΪ��ָ����A��Ԫ��ֵ��������OK*/
Status Value(Array A, ElemType &e, ...)
{
	int off;
	int result;
	va_list ap;
	va_start(ap, e);
	if (result = Locate(A, ap, off) <= 0)
		return result;
	e = *(A.base + off);
	return OK;
}

/*A��nά���飬eάԪ�ر����������n���±�ֵ��
�����±겻���磬��e��ֵ������ָ����A��Ԫ�أ�������OK*/
Status Assign(Array &A, ElemType e, ...)
{
	va_list ap;
	int result;
	int off;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0)
		return result;
	*(A.base + off) = e;
	return OK;
}