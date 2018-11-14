#include "headers.h"

//基本操作

Status InitList_Sq(SqList &L)
{
	//构造一个空的线性表L
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) return OVERFLOW;	//存储分配失败
	L.length = 0;					//空表长度为0
	L.listsize = LIST_INIT_SIZE;	//初始存储容量
	return OK;
}

Status DestroyList_Sq(SqList &L)
{
	//销毁链表L
	//要求链表L存在
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

//辅助函数

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
	//比较两个数据大小，e1大于e2返回1，小于返回-1，等于返回0
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

//引用型操作

Status ListEmpty_Sq(SqList L)
{
	//若L为空表，返回TRUE，否则返回FALSE
	//要求线性表L存在
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}

int ListLength_Sq(SqList L)
{
	//要求线性表已存在
	//返回L中数据元素个数
	return L.length;
}

Status LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	//线性表L已存在，compare()是数据元素判定函数
	//返回L中第一个与e满足关系的compare()的数据元素的位序。
	//若这样的数据元素不存在，返回0
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
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，
	//否则操作失败，pre_e无定义
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
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是最后一个
	//则用next_e返回它的后驱，否则操作失败，next_e无定义
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
	//要求线性表存在，1<=i<=ListLength_Sq(L)
	//e返回L中第i个数据元素的值
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
	//要求线性表存在
	//依次对L的每个元素调用函数visit(),
	//一旦visit()失败，则操作失败，返回FALSE,否则返回TRUE
	for (int i = 0; i < L.length; i++)
	{
		if (!visit_display_Sq(L.elem[i]))
			return FALSE;
	}
	return TRUE;
}

void ClearList_Sq(SqList &L)
{
	//将L重置为空表
	//要求线性表L存在
	L.length = 0;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
	//要求线性表存在，1<=i<=ListLength_Sq(L)+1
	//在第i个位置之前插入数据元素e, L的长度加1
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
	//线性表存在且非空，1<=i<=ListLength_Sq(L)
	//删除L的第i个元素，并用e返回其值，L的长度减1
	if (i<1 || i>L.length)
		return ERROR;
	e = L.elem[i - 1];
	for (int j = i - 1; j < L.length; j++)
		L.elem[j] = L.elem[j + 1];
	L.length--;
	return OK;
}

//算法应用

//算法2.1
void UnionList_Sq(SqList &La, SqList Lb)
{
	//将Lb中存在但La中不存在的元素插入到La中
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

//算法2.2
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
	//已知线性表La和Lb中数据元素按值非递减排列
	//归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列
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