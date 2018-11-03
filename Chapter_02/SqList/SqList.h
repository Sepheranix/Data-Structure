#ifndef _SQLIST_H_
#define _SQLIST_H_

//定义顺序表结构及相关函数声明

#define OK 1
#define OVERFLOW -1
#define LIST_INIT_SIZE 100	//线性表存储空间初始容量
#define LISTINCREMENT 10	//线性表存储空间分配增量
#define TRUE 1
#define FALSE 0
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType *elem;	//存储空间基地址
	int length;		//当前长度
	int listsize;	//当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;

//基本操作
Status InitList_Sq(SqList &L);
Status DestroyList_Sq(SqList &L);

//辅助函数
Status compare_equal_Sq(ElemType e1, ElemType e2);
Status visit_display_Sq(ElemType e);

//引用型操作
Status ListEmpty_Sq(SqList L);
int ListLength_Sq(SqList L);
Status PriorElem_Sq(SqList L, ElemType cur_e, ElemType &pre_e);
Status NextElem_Sq(SqList L, ElemType cur_e, ElemType &next_e);
Status GetElem_Sq(SqList L, int i, ElemType &e);
Status LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status ListTraverse_Sq(SqList L, Status(*visit)(ElemType));

//加工型操作
void ClearList_Sq(SqList &L);
Status ListInsert_Sq(SqList &L, int i, ElemType e);
Status ListDelete_Sq(SqList &L, int i, ElemType &e);

//应用函数
void UnionList_Sq(SqList &La, SqList Lb);
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc);


#endif // !_SQLIST_H_
