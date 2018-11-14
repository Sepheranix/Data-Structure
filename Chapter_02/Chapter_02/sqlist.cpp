#include "headers.h"

//��������

Status InitList_Sq(SqList &L)
{
	//����һ���յ����Ա�L
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) return OVERFLOW;	//�洢����ʧ��
	L.length = 0;					//�ձ���Ϊ0
	L.listsize = LIST_INIT_SIZE;	//��ʼ�洢����
	return OK;
}

Status DestroyList_Sq(SqList &L)
{
	//��������L
	//Ҫ������L����
	if (L.elem)
	{
		free(L.elem);
		L.elem = NULL;
		return OK;
	}
	else
	{
		return ERROR;
	}
}

//��������

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
	//�Ƚ��������ݴ�С��e1����e2����1��С�ڷ���-1�����ڷ���0
	if (e1 > e2)
		return 1;
	else if (e1 < e2)
		return -1;
	else
		return 0;
}

Status visit_display_Sq(ElemType e)
{
	printf_s("%d ", e);
	return TRUE;
}

//�����Ͳ���

Status ListEmpty_Sq(SqList L)
{
	//��LΪ�ձ�����TRUE�����򷵻�FALSE
	//Ҫ�����Ա�L����
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}

int ListLength_Sq(SqList L)
{
	//Ҫ�����Ա��Ѵ���
	//����L������Ԫ�ظ���
	return L.length;
}

Status LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	//���Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����
	//����L�е�һ����e�����ϵ��compare()������Ԫ�ص�λ��
	//������������Ԫ�ز����ڣ�����0
	int pos = 0;
	for (int i = 0; i < L.length; i++)
	{
		if (compare(L.elem[i], e) == 0)
		{
			pos = i + 1;
			break;
		}
	}
	return pos;
}

Status PriorElem_Sq(SqList L, ElemType cur_e, ElemType &pre_e)
{
	//Ҫ�����Ա�L����
	//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ����
	//�������ʧ�ܣ�pre_e�޶���
	int pos = LocateElem_Sq(L, cur_e, compare_equal_Sq);
	if (!pos || pos == 1)
		return ERROR;
	else {
		pre_e = L.elem[pos - 2];
		return OK;
	}
}

Status NextElem_Sq(SqList L, ElemType e, ElemType &next_e)
{
	//Ҫ�����Ա�L����
	//��cur_e��L������Ԫ�أ��Ҳ������һ��
	//����next_e�������ĺ������������ʧ�ܣ�next_e�޶���
	int pos = LocateElem_Sq(L, e, compare_equal_Sq);
	if (!pos || pos == L.length)
		return ERROR;
	else {
		next_e = L.elem[pos];
		return OK;
	}
}

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
	//Ҫ�����Ա���ڣ�1<=i<=ListLength_Sq(L)
	//e����L�е�i������Ԫ�ص�ֵ
	if (i >= 1 && i <= L.length) {
		e = L.elem[i - 1];
		return OK;
	}
	else {
		return ERROR;
	}
}

Status ListTraverse_Sq(SqList L, Status(*visit)(ElemType))
{
	//Ҫ�����Ա����
	//���ζ�L��ÿ��Ԫ�ص��ú���visit(),
	//һ��visit()ʧ�ܣ������ʧ�ܣ�����FALSE,���򷵻�TRUE
	for (int i = 0; i < L.length; i++)
	{
		if (!visit_display_Sq(L.elem[i]))
			return FALSE;
	}
	return TRUE;
}

void ClearList_Sq(SqList &L)
{
	//��L����Ϊ�ձ�
	//Ҫ�����Ա�L����
	L.length = 0;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
	//Ҫ�����Ա���ڣ�1<=i<=ListLength_Sq(L)+1
	//�ڵ�i��λ��֮ǰ��������Ԫ��e, L�ĳ��ȼ�1
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length >= L.listsize)
	{
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			return OVERFLOW;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType* q = &(L.elem[i - 1]);
	for (ElemType* p = &(L.elem[L.length - 1]); p >= q; p--)
		*(p + 1) = *p;
	*q = e;
	L.length++;
	return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
	//���Ա�����ҷǿգ�1<=i<=ListLength_Sq(L)
	//ɾ��L�ĵ�i��Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
	if (i<1 || i>L.length)
		return ERROR;
	e = L.elem[i - 1];
	for (int j = i - 1; j < L.length; j++)
		L.elem[j] = L.elem[j + 1];
	L.length--;
	return OK;
}

//�㷨Ӧ��

//�㷨2.1
void UnionList_Sq(SqList &La, SqList Lb)
{
	//��Lb�д��ڵ�La�в����ڵ�Ԫ�ز��뵽La��
	int La_len = ListLength_Sq(La);
	int Lb_len = ListLength_Sq(Lb);
	ElemType e;
	for (int i = 0; i < Lb_len; i++)
	{
		e = Lb.elem[i];
		if (LocateElem_Sq(La, e, compare_equal_Sq) == 0)
		{
			ListInsert_Sq(La, ++La_len, e);
		}

	}
}

//�㷨2.2
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
	//��֪���Ա�La��Lb������Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µ����Ա�Lc,Lc������Ԫ��Ҳ��ֵ�ǵݼ�����
	int i, j, k, ai, bj;
	int La_len, Lb_len;
	La_len = La.length;
	Lb_len = Lb.length;
	InitList_Sq(Lc);
	i = j = k = 1;
	while (i <= La_len && j <= Lb_len)
	{
		GetElem_Sq(La, i, ai);
		GetElem_Sq(Lb, j, bj);
		if (ai >= bj)
		{
			ListInsert_Sq(Lc, k++, ai);
			i++;
		}
		else
		{
			ListInsert_Sq(Lc, k++, bj);
			j++;
		}
	}
	while (i <= La_len)
	{
		GetElem_Sq(La, i, ai);
		ListInsert_Sq(Lc, i++, ai);
	}
	while (j <= Lb_len)
	{
		GetElem_Sq(Lb, j, bj);
		ListInsert_Sq(Lc, j++, bj);
	}
}