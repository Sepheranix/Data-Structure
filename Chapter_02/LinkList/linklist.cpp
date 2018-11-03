#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "linklist.h"

using namespace std;

void InitList_L(LinkList &L)
{
	//����һ���յ���������L
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
}

void DestroyList_L(LinkList &L)
{
	//���ٱ�L
	free(L);
	L = NULL;
}

void ClearList_L(LinkList &L)
{
	//����L����Ϊ�ձ�
	L->next = NULL;
}

Status ListEmpty_L(LinkList L)
{
	//�ж��Ƿ�Ϊ�ձ��Ƿ���true, ���򷵻�false
	if (L->next == NULL)
		return TRUE;
	else
		return FALSE;
}

int ListLength_L(LinkList L)
{
	int len = 0;
	LinkList p = L->next;	//pָ���һ�����
	while (p != NULL) {
		len++;
		p = p->next;
	}
	return len;
}

Status GetElem_L(LinkList L, int i, ElemType &e)
{
	//LΪ��ͷ���ĵ�����ͷָ��
	//����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
	LinkList p = L->next;	//pָ��ָ���һ�����
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
	//���Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����
	//����L�е�һ����e�����ϵ��compare()������Ԫ�ص�λ��������������Ԫ�ز����ڣ�����0	
	int pos = 0;	//λ��
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
	//Ҫ�����Ա�L����
	//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
	//�������ʧ�ܣ�pre_e�޶���
	LinkList p = L->next;	//pָ���һ�����
	int i = 0;	//���ǵ�һ��
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
	//Ҫ�����Ա�L����
	//��cur_e��L������Ԫ�أ��Ҳ������һ����
	//����next_e�������ĺ������������ʧ�ܣ�next_e�޶���
	LinkList p = L->next;	//pָ���һ�����
	int i = 0;	//���ǵ�һ��
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
	//Ҫ�����Ա���ڣ�1<=i<=ListLength_Sq(L)+1
	//�ڵ�i��λ��֮ǰ��������Ԫ��e
	LinkList p = L;
	int i = 0;
	while (p && i < pos-1) {
		i++;
		p = p->next;
	}
	if (!p || i > pos - 1)	
		return ERROR;	//posС��1����ڱ�
	LNode* newNode = (LinkList)malloc(sizeof(LNode));
	newNode->next = p->next;
	newNode->data = e;
	p->next = newNode;
	return OK;
}

Status ListDelete_L(LinkList L, int pos, ElemType &e)
{
	//���Ա�����ҷǿգ�1<=i<=ListLength_Sq(L)
	//ɾ��L�ĵ�i��Ԫ�أ�����e������ֵ
	LinkList p = L;
	int i = 0;
	while (p && i < pos - 1) {
		i++;
		p = p->next;
	}
	if (!(p->next) || i > pos - 1)
		return ERROR;	//posС��1����ڱ�
	LinkList temp = p->next;
	p->next = temp->next;
	e = temp->data;
	free(temp);
	temp = NULL;
	return OK;
}

Status ListTraverse_L(LinkList L, Status(*visit)(LinkList))
{
	//���ζ�L��ÿ��Ԫ�ص��ú���visit(), 
	//һ��visit()ʧ�ܣ������ʧ�ܣ�����FALSE,���򷵻�TRUE
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

//�㷨
//�㷨2.11
void CreateList_L(LinkList &L, int n)
{
	//��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ�����
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = 0; i < n; i++) {
		p = (LinkList)malloc(sizeof(LNode));	//�����½��
		//scanf_s("%d", p->data);
		cout << "�����룺";
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}

//�㷨2.12
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