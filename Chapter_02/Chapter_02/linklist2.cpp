//链表的构造及算法
#include "headers.h"

using namespace std;

Status MakeNode(Link &p, ElemType e)
{
	//分配由p指向的值为e的结点，并返回OK；若分配失败，则返回ERROR
	p = (Link)malloc(sizeof(LNode2));
	if (!p)		//分配失败
		return ERROR;
	p->data = e;
	return OK;
}

void FreeNode(Link &p)
{
	//释放p所指向的结点
	free(p);
	p = NULL;
}

Status InitList(LinkList2 &L)
{
	//构造一个空链表L
	Link p;
	p = (Link)malloc(sizeof(LNode2)); //生成结点
	if (!p)
		return ERROR;
	p->next = NULL;		//头结点的下一个元素置空
	L.head = L.tail = p;
	L.len = 0;	//初始为0
	return OK;
}

Status ClearList(LinkList2 &L)
{
	//将L置为空表，并释放原链表的结点空间
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

Status DestroyList(LinkList2 &L)
{
	//销毁线性链表L，L不再存在
	ClearList(L);	//释放除头尾结点的所有结点
	free(L.head);	//释放头尾结点（同一个结点）
	L.head = L.tail = NULL;
	L.len = 0;
	return OK;
}

Status InsFirst(Link h, Link s)
{
	//h指向链表头结点，将s所指结点插入第一个结点之前
	s->next = h->next;
	h->next = s;
	return OK;
}

Status DelFirst(Link h, Link &q)
{
	//已知h指向链表头结点，删除第一个结点并以q返回，链表为空返回ERROR
	if (!h)
		return ERROR;
	q = h->next;
	h->next = q->next;
	q->next = NULL;
	return OK;
}

Status Append(LinkList2 &L, Link s)
{
	//将指针s所指的一串结点连接在L的最后一个结点之后，并修改尾指针
	int i = 1;	//计数，记录s链接的的结点数
	L.tail->next = s;	//连接
	while (s->next != NULL) {	//寻找尾指针
		s = s->next;
		i++;
	}
	L.tail = s;		//修改尾指针
	L.len += i;
	return OK;
}

Status Remove(LinkList2 &L, Link &q)
{
	//删除L尾结点，并以q返回
	Link p = L.head;
	if (L.head == L.tail)
		return ERROR;
	while (p->next != L.tail)
		p = p->next;	//寻找尾指针前一个结点
	p->next = NULL;		//删除尾指针
	q = L.tail;
	L.tail = p;
	L.len--;
	return OK;
}

Status InsBefore(LinkList2 &L, Link &p, Link s)
{
	//已知p指向线性链表L中的一个结点，将s所指向结点插入在p所指结点之前
	//并修改指针p指向新的结点
	Link h = L.head;
	while (p != h->next) {    //搜索指向p所指结点
		h = h->next;
	}
	h->next = s;
	s->next = p;
	p = s;
	L.len++;
	return OK;
}

Status InsAfter(LinkList2 &L, Link &p, Link s)
{
	//已知p指向线性链表L中的一个结点，将s所指的结点插入在p所指结点之后
	//并修改指针p所指新插入的结点
	s->next = p->next;
	p->next = s;
	if (p == L.tail)
		L.tail = s;		//修改尾指针
	p = s;
	L.len++;
	return OK;
}

Status SetCurElem(Link &p, ElemType e)
{
	// 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值  
	p->data = e;
	return OK;
}

ElemType GetCurElem(Link p)
{
	//已知p指向表中一个结点，返回p所指结点中数据元素的值
	return p->data;
}

Status ListEmpty(LinkList2 L)
{
	//L为空表返回TRUE，否则FALSE
	if (L.head == L.tail)
		return TRUE;
	else
		return FALSE;
}

int ListLength(LinkList2 L)
{
	//返回L中元素个数
	return L.len;
}
Position GetHead(LinkList2 L)
{
	//返回L中头结点位置
	return L.head;
}

Position GetLast(LinkList2 L)
{
	//返回L中尾结点位置
	return L.tail;
}

Position PriorPos(LinkList2 L, Link p)
{
	// 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置   
	// 若无前驱，则返回NULL
	Link pos = L.head;
	while (pos->next != p)
		pos = pos->next;
	if (pos == L.head)	//没有直接前驱
		return NULL;
	else
		return pos;
}

Position NextPos(LinkList2 L, Link p)
{
	//返回后继位置，无则返回NULL
	if (p == L.tail)
		return NULL;
	else
		return p->next;
}

Status LocatePos(LinkList2 L, int i, Link &p)
{
	// 返回p指示线性链表L中第i个结点的位置，并返回1，i值不合法时返回0   
	// i=0为头结点
	if (i<0 || i>L.len)
		return 0;
	p = L.head;
	while (i != 0) {
		i--;
		p = p->next;
	}
	return 0;
}

Position LocateElem(LinkList2 L, ElemType e, int(*compare)(ElemType, ElemType))
{
	// 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置，   
	// 若不存在这样的元素，则返回NULL
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

Status ListTraverse(LinkList2 L, void(*visit)(Link))
{
	// 依次对L的每个数据元素调用函数visit() 
	Link p = L.head->next;
	while (p != NULL) {
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
 * 算法2.20，在带头结点的单链线性表L的第i个元素之前插入元素e
 */
Status ListInsert(LinkList2 &L, int i, ElemType e)
{
	/*Link p = L.head;
	Link s;
	MakeNode(s, e);
	if (i < 1 || i > L.len)
		return ERROR;
	while (i > 0) {
		p = p->next;
		i--;
	}
	InsBefore(L, p, s);*/


	Link h, s;
	if (!LocatePos(L, i - 1, h))
		return ERROR;
	if (!MakeNode(s, e))
		return ERROR;
	if (h == L.tail)
		L.tail = s;   // 修改尾指针
	InsFirst(h, s);       //对于从第不个结点开始的链表，第i-1个结点是它的头结点
	L.len++;
	return OK;
}

Status MergeList(LinkList2 &La, LinkList2 &Lb, LinkList2 &Lc, int(*compare)(ElemType, ElemType))
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