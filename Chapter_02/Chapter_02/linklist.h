#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

void InitList_L(LinkList &L);
void DestroyList_L(LinkList &L);
void ClearList_L(LinkList &L);
Status ListEmpty_L(LinkList L);
int ListLength_L(LinkList L);
Status GetElem_L(LinkList L, int i, ElemType &e);
int LocateElem_L(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status PriorElem_L(LinkList L, ElemType cur_e, ElemType &pre_e);
Status NextElem_L(LinkList L, ElemType cur_e, ElemType &next_e);
Status ListInsert_L(LinkList L, int i, ElemType e);
Status ListDelete_L(LinkList L, int i, ElemType &e);
Status ListTraverse_L(LinkList L, Status(*visit)(LinkList));
Status visit_display_L(LinkList L);

void CreateList_L(LinkList &L, int n);
void MergeList_L(LinkList La, LinkList Lb, LinkList &Lc);

#endif // !_LINK_LIST_


