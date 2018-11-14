#ifndef _LinkList2_H_
#define _LinkList2_H_

typedef struct LNode2 {	//�������
	ElemType data;
	struct LNode2 *next;
}*Link, *Position;

typedef struct {	//��������
	Link head, tail;	//�ֱ�ָ�����������е�ͷ�������һ�����
	int len;	//ָ�����Ա������ݵĸ���
	//Link current;	//ָ��ǰ���ʵĽ���ָ�룬��ʼλ��ָ��ͷ���
}LinkList2;

Status MakeNode(Link &p, ElemType e);
void FreeNode(Link &p);
Status InitList(LinkList2 &L);
Status ClearList(LinkList2 &L);
Status DestroyList(LinkList2 &L);
Status InsFirst(Link h, Link s);
Status DelFirst(Link h, Link &q);
Status Append(LinkList2 &L, Link s);
Status Remove(LinkList2 &L, Link &p);
Status InsBefore(LinkList2 &L, Link &p, Link s);
Status InsAfter(LinkList2 &L, Link &p, Link s);
Status SetCurElem(Link &p, ElemType e);
Status ListEmpty(LinkList2 L);
int ListLength(LinkList2 L);
Position GetHead(LinkList2 L);
Position GetLast(LinkList2 L);
Position PriorPos(LinkList2 L, Link p);
Position NextPos(LinkList2 L, Link p);
Status LocatePos(LinkList2 L, int i, Link &p);
Position LocateElem(LinkList2 L, ElemType e, int(*compare)(ElemType, ElemType));
Status ListTraverse(LinkList2 L, void(*visit)(Link));
void visit_display(Link p);
Status ListInsert(LinkList2 &L, int i, ElemType e);
Status MergeList(LinkList2 &La, LinkList2 &Lb, LinkList2 &Lc, int(*compare)(ElemType, ElemType));
int compare(ElemType e1, ElemType e2);

#endif // !_LINK_LIST_H_