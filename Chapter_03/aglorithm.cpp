#include "headers.h"

using namespace std;

/*����ת��,10����ת8����*/
void conversion()
{
	int decimal;
	cout << "Input:";
	cin >> decimal;
	SqStack S;
	InitStack(S);
	SElemType e;
	while (decimal) {
		Push(S, decimal % 8);
		decimal = decimal / 8;
	}
	cout << "Output:";
	while (!StackEmpty(S)) {
		Pop(S, e);
		printf_s("%d", e);
	}
}

/*����ƥ�����*/
void matching(char *exp)
{
	int state = 1;
	int i = 0;
	SElemType e;
	SqStack S;
	InitStack(S);
	while (exp[i] != '\0' && state) {
		switch (exp[i])
		{
		case '(':
		{
			Push(S, 1);
			i++;
			break;
		}
		case '[':
		{
			Push(S, 2);
			i++;
			break;
		}
		case '{':
		{
			Push(S, 3);
			i++;
			break;
		}
		case ')':
		{
			if (!StackEmpty(S) && GetTop(S) == 1) {
				Pop(S, e);
				i++;
			}
			else
				state = 0;
			break;
		}
		case ']':
		{
			if (!StackEmpty(S) && GetTop(S) == 2) {
				Pop(S, e);
				i++;
			}
			else
				state = 0;
			break;
		}
		case '}':
		{
			if (!StackEmpty(S) && GetTop(S) == 3) {
				Pop(S, e);
				i++;
			}
			else
				state = 0;
			break;
		}
		default:
			break;

		}
	}
	if (StackEmpty(S) && state)
		cout << "ƥ��" << endl;
	else
		cout << "��ƥ��" << endl;
}

/*�б༭����#: �˸�@: ��ո���, EOF: �˳�*/
void LineEdit()
{
	char ch;
	SElemType e;
	SqStack S;
	InitStack(S);
	ch = getchar();
	while (ch != EOF) {
		while (ch != EOF && ch != '\n') {
			switch (ch) {
			case '#':
				Pop(S, e);
				break;
			case '@':
				ClearStack(S);
				break;
			default:
				Push(S, (int)ch);
				break;
			}
			ch = getchar();
		}
		StackTraverse(S, display_char);
		cout << endl;
		ClearStack(S);
		if (ch != EOF)
			ch = getchar();
	}
}

/*�����ʽת��Ϊ��׺ʽ*/
/*bug*/
void transform(char suffix[], char exp[])
{
	SqStack S;
	InitStack(S);
	Push(S, (int)'#');
	char *p = exp;
	char ch = *p;
	SElemType c;

	while (!StackEmpty(S)) {
		if (!IN(ch))
			Pass(suffix, ch);
		else {
			switch (ch)
			{
			case '(':
				Push(S, (int)ch);
				break;
			case ')':
				Pop(S, c);
				while ((char)c != '(') {
					Pass(suffix, (char)c);
					Pop(S, c);
					break;
				}
			default:
				while (!GetTop(S, c) && (precede(c, ch))) {
					Pass(suffix, (char)c);
					Pop(S, c);
				}
				if (ch != '#') 
					Push(S, ch);
				break;
			}
		}
	}
}

Status precede(char c1, char c2)
{
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case '+':
		case '-':
		case ')':
		case '#':
			return TRUE;
			break;
		case '*':
		case '/':
		case '(':
			return FALSE;
			break;
		default:
			break;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return TRUE;
			break;
		case '(':
			return FALSE;
			break;
		default:
			break;
		}
		break;
	case '(':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return FALSE;
			break;
		case ')':
			return FALSE;
			break;
		default:
			break;
		}
		break;
	case ')':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return TRUE;
			break;
		default:
			break;
		}
		break;
	case '#':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return FALSE;
			break;
		case '#':
			return FALSE;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

Status IN(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#')
		return TRUE;
	return FALSE;
}

void Pass(char suffix[], char ch)
{
	static int i = 0;
	suffix[i++] = ch;
}


///*�㷨3.4���������ʽ��ֵ*/
//int EvaluateExpression()
//{
//
//}