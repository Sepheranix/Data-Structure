#include "headers.h"

int main(int argc, char const *argv[])
{
	LinkList2 L;
	InitList(L);
	for (int i = 0; i < 20; i++) {
		Link s;
		MakeNode(s, i);
		Append(L, s);
	}
	ListTraverse(L, visit_display);
	system("pause");


	/*struct LNode *La;
	InitList_L(La);
	ListInsert_L(La, 1, 1);
	ListInsert_L(La, 2, 2);
	ListInsert_L(La, 3, 5);
	ListInsert_L(La, 4, 7);
	ListInsert_L(La, 5, 10);
	ListTraverse_L(La, visit_display_L);
	printf("\n");

	struct LNode *Lb;
	InitList_L(Lb);
	ListInsert_L(Lb, 1, 0);
	ListInsert_L(Lb, 2, 3);
	ListInsert_L(Lb, 3, 6);
	ListInsert_L(Lb, 4, 7);
	ListInsert_L(Lb, 5, 10);
	ListTraverse_L(Lb, visit_display_L);
	printf("\n");

	struct LNode *Lc;
	MergeList_L(La, Lb, Lc);
	ListTraverse_L(Lc, visit_display_L);
	system("pause");*/

	return 0;
}