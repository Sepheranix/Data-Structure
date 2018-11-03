#ifndef _SQLIST_H_
#define _SQLIST_H_

//����˳���ṹ����غ�������

#define OK 1
#define OVERFLOW -1
#define LIST_INIT_SIZE 100	//���Ա�洢�ռ��ʼ����
#define LISTINCREMENT 10	//���Ա�洢�ռ��������
#define TRUE 1
#define FALSE 0
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType *elem;	//�洢�ռ����ַ
	int length;		//��ǰ����
	int listsize;	//��ǰ����Ĵ洢��������sizeof(ElemType)Ϊ��λ��
}SqList;

//��������
Status InitList_Sq(SqList &L);
Status DestroyList_Sq(SqList &L);

//��������
Status compare_equal_Sq(ElemType e1, ElemType e2);
Status visit_display_Sq(ElemType e);

//�����Ͳ���
Status ListEmpty_Sq(SqList L);
int ListLength_Sq(SqList L);
Status PriorElem_Sq(SqList L, ElemType cur_e, ElemType &pre_e);
Status NextElem_Sq(SqList L, ElemType cur_e, ElemType &next_e);
Status GetElem_Sq(SqList L, int i, ElemType &e);
Status LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status ListTraverse_Sq(SqList L, Status(*visit)(ElemType));

//�ӹ��Ͳ���
void ClearList_Sq(SqList &L);
Status ListInsert_Sq(SqList &L, int i, ElemType e);
Status ListDelete_Sq(SqList &L, int i, ElemType &e);

//Ӧ�ú���
void UnionList_Sq(SqList &La, SqList Lb);
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc);


#endif // !_SQLIST_H_
