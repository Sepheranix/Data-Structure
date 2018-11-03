#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#define OK 1
#define OVERFLOW (-1)
#define TRUE 1
#define FALSE 0
#define NOTEXIT 0
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct LNode {	//结点类型
	ElemType data;
	struct LNode *next;
}*Link, *Position;

typedef struct {	//链表类型
	Link head, tail;	//分别指向线性链表中的头结点和最后一个结点
	int len;	//指向线性表中数据的个数
	//Link current;	//指向当前访问的结点的指针，初始位置指向头结点
}LinkList;

Status MakeNode(Link &p, ElemType e);
void FreeNode(Link &p);
Status InitList(LinkList &L);
Status ClearList(LinkList &L);
Status DestroyList(LinkList &L);
Status InsFirst(Link h, Link s);
Status DelFirst(Link h, Link &q);
Status Append(LinkList &L, Link s);
Status Remove(LinkList &L, Link &p);
Status InsBefore(LinkList &L, Link &p, Link s);
Status InsAfter(LinkList &L, Link &p, Link s);
Status SetCurElem(Link p);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
Position GetHead(LinkList L);
Position GetLast(LinkList L);
Position PriorPos(LinkList L, Link p);
Position NextPos(LinkList L, Link p);
Status LocatePos(LinkList L, int i, Link &p);
Position LocateElem(LinkList &L, ElemType e, int(*compare)(ElemType, ElemType));
Status ListTraverse(LinkList L, void(*visit)(Link));
void visit_display(Link p);
Status ListInsert(LinkList &L, int i, ElemType e);
Status MergeList(LinkList &La, LinkList &Lb, LinkList &Lc, int(*compare)(ElemType, ElemType));
int compare(ElemType e1, ElemType e2);


#endif // !_LINK_LIST_H_