#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "linklist.h"

using namespace std;

int main(int argc, char const *argv[])
{
	LinkList L;
	int n;
	cin >> n;
	CreateList_L(L, n);
	ListTraverse_L(L, visit_display_L);
	system("pause");
	return 0;
}