//����Ĺ��켰�㷨

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "linklist.h"

using namespace std;

Status MakeNode(Link &p, ElemType e)
{
	//������pָ���ֵΪe�Ľ�㣬������OK��������ʧ�ܣ��򷵻�ERROR
	p = (Link)malloc(sizeof(LNode));
	if (!p)		//����ʧ��
		return ERROR;
	p->data = e;
	return OK;
}

void FreeNode(Link &p)
{
	//�ͷ�p��ָ��Ľ��
	free(p);
	p = NULL;
}

Status InitList(LinkList &L)
{
	//����һ��������L
	Link p;
	p = (Link)malloc(sizeof(LNode)); //���ɽ��
	if (!p)
		return ERROR;
	p->next = NULL;		//ͷ������һ��Ԫ���ÿ�
	L.head = L.tail = p;
	L.len = 0;	//��ʼΪ0
	return OK;
}

Status ClearList(LinkList &L)
{
	//��L��Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
	Link p, q;
	p = L.head->next;;
	L.head->next = NULL;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	L.tail = L.head;
	L.len = 0;
	return OK;
}

Status DestroyList(LinkList &L)
{
	//������������L��L���ٴ���
	ClearList(L);	//�ͷų�ͷβ�������н��
	free(L.head);	//�ͷ�ͷβ��㣨ͬһ����㣩
	L.head = L.tail = NULL;
	L.len = 0;
	return OK;
}

Status InsFirst(Link h, Link s)
{
	//hָ������ͷ��㣬��s��ָ�������һ�����֮ǰ
	s->next = h->next;
	h->next = s;
	return OK;
}

Status DelFirst(Link h, Link &q)
{
	//��֪hָ������ͷ��㣬ɾ����һ����㲢��q���أ�����Ϊ�շ���ERROR
	if (!h)
		return ERROR;
	q = h->next;
	h->next = q->next;
	q->next = NULL;
	return OK;
}

Status Append(LinkList &L, Link s)
{
	//��ָ��s��ָ��һ�����������L�����һ�����֮�󣬲��޸�βָ��
	int i = 1;	//��������¼s���ӵĵĽ����
	L.tail->next = s;	//����
	while (s->next != NULL) {	//Ѱ��βָ��
		s = s->next;
		i++;
	}
	L.tail = s;		//�޸�βָ��
	L.len += i;
	return OK;
}

Status Remove(LinkList &L, Link &q)
{
	//ɾ��Lβ��㣬����q����
	Link p = L.head;
	if (L.head == L.tail)
		return ERROR;
	while (p->next != L.tail)
		p = p->next;	//Ѱ��βָ��ǰһ�����
	p->next = NULL;		//ɾ��βָ��
	q = L.tail;		
	L.tail = p;
	L.len--;
	return OK;
}

Status InsBefore(LinkList &L, Link &p, Link s)
{
	//��֪pָ����������L�е�һ����㣬��s��ָ���������p��ָ���֮ǰ
	//���޸�ָ��pָ���µĽ��
	if (L.head = L.tail)
	{
		return ERROR;
	}
	Link pos = L.head;
	while (pos->next != p)
	{
		pos = pos->next;
	}
	s->next = p;
	pos->next = s;
	p = s;
	L.len++;
	return OK;
}

Status InsAfter(LinkList &L, Link &p, Link s)
{
	//��֪pָ����������L�е�һ����㣬��s��ָ�Ľ�������p��ָ���֮��
	//���޸�ָ��p��ָ�²���Ľ��
	s->next = p->next;
	p->next = s;
	if (p == L.tail)
		L.tail = s;		//�޸�βָ��
	p = s;
	L.len++;
	return OK;
}

Status SetCurElem(Link &p, ElemType e)
{
	// ��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ  
	p->data = e;
	return OK;
}

ElemType GetCurElem(Link p)
{
	//��֪pָ�����һ����㣬����p��ָ���������Ԫ�ص�ֵ
	return p->data;
}

Status ListEmpty(LinkList L)
{
	//LΪ�ձ���TRUE������FALSE
	if (L.head == L.tail)
		return TRUE;
	else
		return FALSE;
}

int ListLength(LinkList L)
{
	//����L��Ԫ�ظ���
	return L.len;
}
Position GetHead(LinkList L)
{
	//����L��ͷ���λ��
	return L.head;
}

Position GetLast(LinkList L)
{
	//����L��β���λ��
	return L.tail;
}

Position PriorPos(LinkList L, Link p)
{
	// ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ����λ��   
	// ����ǰ�����򷵻�NULL
	Link pos = L.head;
	while (pos->next != p)
		pos = pos->next;
	if (pos == L.head)	//û��ֱ��ǰ��
		return NULL;
	else
		return pos;
}

Position NextPos(LinkList L, Link p)
{
	//���غ��λ�ã����򷵻�NULL
	if (p == L.tail)
		return NULL;
	else
		return p->next;
}

Status LocatePos(LinkList L, int i, Link &p)
{
	// ����pָʾ��������L�е�i������λ�ã�������1��iֵ���Ϸ�ʱ����0   
	// i=0Ϊͷ���
	if (i<0 || i>L.len)
		return 0;
	p = L.head;
	while (i > 0) {
		i--;
		p = p->next;
	}
	return 0;
}

Position LocateElem(LinkList L, ElemType e, int(*compare)(ElemType, ElemType))
{
	// ������������L�е�1����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã�   
	// ��������������Ԫ�أ��򷵻�NULL
	Link p = L.head->next;
	int i = 0;
	while (p) {
		i++;
		if ((*compare)(p->data, e) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

Status ListTraverse(LinkList L, void(*visit)(Link))
{
	// ���ζ�L��ÿ������Ԫ�ص��ú���visit() 
	Link p = L.head->next;
	while (p) {
		visit(p);
		p = p->next;
	}
	return OK;
}

void visit_display(Link p)
{
	printf_s("%d ", p->data);
}

int compare(ElemType e1, ElemType e2)
{
	if (e1 > e2)
		return 1;
	else if (e1 < e2)
		return -1;
	else
		return 0;
}

/**
 * �㷨2.20���ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
 */
Status ListInsert(LinkList &L, int i, ElemType e)
{
	Link p = L.head;
	Link s;
	MakeNode(s, e);
	if (i < 1 || i > L.len)
		return ERROR;
	while (i > 0) {
		p = p->next;
		i--;
	}
	InsBefore(L, p, s);
}

Status MergeList(LinkList &La, LinkList &Lb, LinkList &Lc, int(*compare)(ElemType, ElemType))
{
	Link ha, hb, pa, pb, q;
	ElemType a, b;
	if (!InitList(Lc))
		return ERROR;
	ha = GetHead(La);
	hb = GetHead(Lb);
	pa = NextPos(La, ha);
	pb = NextPos(Lb, hb);
	while (pa && pb) {
		a = GetCurElem(pa);
		b = GetCurElem(pb);
		if (compare(a, b) <= 0) {   // a<=b
			DelFirst(ha, q);
			Append(Lc, q);
			pa = NextPos(La, ha);
		}
		else {    // a>b
			DelFirst(hb, q);
			Append(Lc, q);
			pb = NextPos(Lb, hb);
		}
	} // while
	if (pa)
		Append(Lc, pa);
	else
		Append(Lc, pb);
	FreeNode(ha);
	FreeNode(hb);
	return OK;
}