#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SqList.h"

using namespace std;

int main(int argc, char const *argv[])
{
	SqList La, Lb, Lc;
	InitList_Sq(La);
	InitList_Sq(Lb);
	int a[20];
	int b[20];
	int i = 0;
	int j = 0;
	for (i = 0; i < 20; i++)
	{
		ListInsert_Sq(La, i + 1, i);
		ListInsert_Sq(Lb, i + 1, i * 2);
	}
	
	cout << "La";
	ListTraverse_Sq(La, visit_display_Sq);
	
	cout << endl;
	cout << "Lb";
	ListTraverse_Sq(Lb, visit_display_Sq);

	/*cout << endl;
	MergeList_Sq(La, Lb, Lc);
	cout << "MergeList(La,Lb,Lc)";
	ListTraverse_Sq(Lc, visit_display_Sq);*/

	cout << endl;
	UnionList_Sq(La, Lb);
	cout << "UnionList_Sq(La,Lb)";
	ListTraverse_Sq(La, visit_display_Sq);
	cout << endl;
	system("pause");
	return 0;
}