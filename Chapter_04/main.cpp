#include "headers.h"

int main(int argc, char const *argv[])
{
	char chars[] = "aabaaabaaabaaabaaab";
	char chars2[] = "aaab";
	SString S, T;
	StrAssign(S, chars);
	StrAssign(S, chars2);
	displayStr(S);
	printf_s("\n");
	displayStr(T);
	printf_s("\n");
	int i = Index_KMP(S, T, 1);
	printf_s("%d\n", i);
	system("pause");
	return 0;
}