#ifndef _ARRAY_H_
#define _ARRAY_H_

#define MAX_ARRAY_DIM 8		//�����������ά��Ϊ8

typedef int ElemType;
typedef int Status;

typedef struct {
	ElemType *base;	//�������ַ����InitArray����
	int dim;		//����ά��
	int *bounds;	//����ά���ַ����InitArray����
	int *constants;	//����ӳ����������ַ����InitArray����
}Array;

Status InitArray(Array &A, int dim, ...);
Status DestroyArray(Array &A);
Status Locate(Array A, va_list ap, int &off);
Status Value(Array A, ElemType &e, ...);
Status Assign(Array &A, ElemType e, ...);

#endif // !_ARRAY_H_
