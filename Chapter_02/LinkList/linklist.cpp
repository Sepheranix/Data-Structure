#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "linklist.h"

using namespace std;

void InitList_L(LinkList &L)
{
	//构造一个空的线性链表L
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
}

void DestroyList_L(LinkList &L)
{
	//销毁表L
	free(L);
	L = NULL;
}

void ClearList_L(LinkList &L)
{
	//将表L重置为空表
	L->next = NULL;
}

Status ListEmpty_L(LinkList L)
{
	//判断是否为空表，是返回true, 否则返回false
	if (L->next == NULL)
		return TRUE;
	else
		return FALSE;
}

int ListLength_L(LinkList L)
{
	int len = 0;
	LinkList p = L->next;	//p指向第一个结点
	while (p != NULL) {
		len++;
		p = p->next;
	}
	return len;
}

Status GetElem_L(LinkList L, int i, ElemType &e)
{
	//L为带头结点的单链表头指针
	//当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
	LinkList p = L->next;	//p指针指向第一个结点
	int j = 1;
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	if (p == NULL || j > i)
		return ERROR;
	e = p->data;
	return OK;
}

int LocateElem_L(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	//线性表L已存在，compare()是数据元素判定函数
	//返回L中第一个与e满足关系的compare()的数据元素的位序。若这样的数据元素不存在，返回0	
	int pos = 0;	//位序
	LinkList p = L->next;

	while (p) {
		pos++;
		if (compare(e, p->data))
			return pos;
		p = p->next;
	}
	return 0;
}

Status PriorElem_L(LinkList L, ElemType cur_e, ElemType &pre_e)
{
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱
	//否则操作失败，pre_e无定义
	LinkList p = L->next;	//p指向第一个结点
	int i = 0;	//不是第一个
	while (p) {
		i++;
		if (p->next->data == cur_e) {
			pre_e = p->data;
			break;
		}
		p = p->next;
	}
	if (!p || i==1)
		return ERROR;
	else
		return OK;
}

Status NextElem_L(LinkList L, ElemType cur_e, ElemType &next_e)
{
	//要求线性表L存在
	//若cur_e是L的数据元素，且不是最后一个，
	//则用next_e返回它的后驱，否则操作失败，next_e无定义
	LinkList p = L->next;	//p指向第一个结点
	int i = 0;	//不是第一个
	while (p) {
		if (p->data == cur_e && p->next) {
			next_e = p->next->data;
			break;
		}
		p = p->next;
	}
	if (!p)
		return ERROR;
	else
		return OK;
}

Status ListInsert_L(LinkList L, int pos, ElemType e)
{
	//要求线性表存在，1<=i<=ListLength_Sq(L)+1
	//在第i个位置之前插入数据元素e
	LinkList p = L;
	int i = 0;
	while (p && i < pos-1) {
		i++;
		p = p->next;
	}
	if (!p || i > pos - 1)	
		return ERROR;	//pos小于1或大于表长
	LNode* newNode = (LinkList)malloc(sizeof(LNode));
	newNode->next = p->next;
	newNode->data = e;
	p->next = newNode;
	return OK;
}

Status ListDelete_L(LinkList L, int pos, ElemType &e)
{
	//线性表存在且非空，1<=i<=ListLength_Sq(L)
	//删除L的第i个元素，并用e返回其值
	LinkList p = L;
	int i = 0;
	while (p && i < pos - 1) {
		i++;
		p = p->next;
	}
	if (!(p->next) || i > pos - 1)
		return ERROR;	//pos小于1或大于表长
	LinkList temp = p->next;
	p->next = temp->next;
	e = temp->data;
	free(temp);
	temp = NULL;
	return OK;
}

Status ListTraverse_L(LinkList L, Status(*visit)(LinkList))
{
	//依次对L的每个元素调用函数visit(), 
	//一旦visit()失败，则操作失败，返回FALSE,否则返回TRUE
	LinkList p;
	p = L->next;
	while (p != NULL) {
		if (visit(p)==ERROR)
			return ERROR;
		p = p->next;
	}
	return OK;
}

Status visit_display_L(LinkList L)
{
	//printf_s("%d ", L->data);
	cout << L->data << " ";
	return OK;
}

//算法
//算法2.11
void CreateList_L(LinkList &L, int n)
{
	//逆位序输入n个元素的值，建立带表头结点的单链表
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = 0; i < n; i++) {
		p = (LinkList)malloc(sizeof(LNode));	//生成新结点
		//scanf_s("%d", p->data);
		cout << "请输入：";
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}

//算法2.12
void MergeList_L(LinkList La, LinkList Lb, LinkList &Lc)
{
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = Lc = La;

	while (pa != NULL && pb != NULL) {
		if (pa->data > pb->data) {
			pc->next = pa;
			pc = pc->next;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pc->next;
			pb = pb->next;
		}
	}
	if (pa == NULL)
		pc->next = pb;
	else
		pc->next = pa;
		pc->next = pa;
}