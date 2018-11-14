#include "headers.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*SqStack S;
	LinkQueue Q;
	InitQueue(Q);
	InitStack(S);
	for (int i = 0; i < 20; i++) {
		Push(S, i);
		EnQueue(Q, i * i);
	}
	printf_s("Stack:");
	StackTraverse(S, visit_display);
	printf_s("\n");
	printf_s("Queue:");
	QueueTraverse(Q, visit_display);
	printf_s("\n");*/

	//testing conversion
	/*printf_s("请输入一个十进制数：");
	int n;
	scanf_s("%d", &n);
	printf_s("转化八进制为：");
	conversion(n);
	cout << endl;*/

	//testint Push & Pop
	/*cout << "Pop:";
	SElemType e1, e2;
	Pop(S, e1);
	cout << e1 << endl;
	StackTraverse(S, visit_display);
	cout << endl;

	cout << "Push" << endl;
	cin >> e2;
	Push(S, e2);
	StackTraverse(S, visit_display);*/

	
	
	/*testing matching*/
	//char exp[100] = {'\0'};
	//cout << "testing matching" << endl;
	//cout << "Input:";
	//cin >> exp;
	//matching(exp);

	///*testing LineEdit*/
	//LineEdit();


	//testing suffix
	char suffix[100];
	char exp[100] = "a*b+(c-d/e)*f#";
	transform(suffix, exp);
	cout << exp << endl;
	//bug

	system("pause");
	return 0;
}