#include "headers.h"

/*若维数dim合法， 和各维长度合法，则构造相应数组A，并返回OK*/
Status InitArray(Array &A, int dim, ...)
{
	va_list ap;
	int elemtotal = 1;	//保存数组的元素个数
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;	
	A.dim = dim;
	A.bounds = (int *)malloc(dim * sizeof(int));
	if (!A.bounds)
		exit(OVERFLOW);	//若各维长度合法，则存入A.bounds，并求出A的元素总数elemtotal
	va_start(ap, dim);	//ap为va_list类型，是存放变长参数表信息的数组
	for (int i = 0; i < dim; i++) {
		A.bounds[i] = va_arg(ap, int);	//读入一个变长参数
		if (A.bounds[i] < 0)
			return UNDERFLOW;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if (!A.base)
		exit(OVERFLOW);
	//求映像函数的常数c，并存入A.constants[i - 1], i = 1, ..., dim
	A.constants = (int *)malloc(dim * sizeof(int));
	if (!A.constants)
		exit(OVERFLOW);
	A.constants[dim - 1] = 1;	//L = 1，指针的增减以元素的大小为单位
	for (int i = dim - 2; i > 0; --i)
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	return OK;
}

/*销毁数组A*/
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

/*若ap指示的各下标值合法，则求出该元素在A中对应的地址off*/
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

/*A是n维数组，e维元素变量，随后是n个下标值。
若各下标不超界，则e赋值为所指定的A的元素值，并返回OK*/
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

/*A是n维数组，e维元素变量，随后是n个下标值。
若各下标不超界，则将e的值赋给所指定的A的元素，并返回OK*/
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