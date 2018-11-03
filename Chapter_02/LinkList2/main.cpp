#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "linklist.h"

using namespace std;

int main(int argc, char const *argv[])
{
	LinkList L;
	InitList(L);
	for (int i = 0; i < 20; i++) {
		Link s;
		MakeNode(s, i);
		Append(L, s);
	}
	ListTraverse(L, visit_display);
	system("pause");
	return 0;
}