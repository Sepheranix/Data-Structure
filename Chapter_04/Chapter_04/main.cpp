#include "headers.h"

using namespace std;

int main(int argc, char const *argv[])
{
	char chars[] = "aaabaaabaaabaaabaaab";
	char chars3[] = "aaaab";
	char chars4[] = "aaaab";
	int nextval1[6];
	//int nextval2[5];
	int next1[6];
	//int next2[5];

	SString S, T;
	StrAssign(S, chars3);
	StrAssign(T, chars4);
	displayStr(S);
	printf_s("\n");
	displayStr(T);
	printf_s("\n");
	int i = Index_KMP(S, T, 1);
	printf_s("%d\n", i);

	get_nextval(S, nextval1);
	//get_nextval(T, nextval2);
	get_next(S, next1);
	//get_next(T, next2);

	cout << "next: ";
	for (int i = 1; i <= 5; ++i) {
		cout << next1[i] << " ";
	}

	cout << endl;
	cout << "nextval: ";
	for (int i = 1; i <= 5; i++) {
		cout << nextval1[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}