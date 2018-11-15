/*��������洢�����������㷨ʵ��*/

#include "headers.h"

using namespace std;



/*��������*/

/*������˳������������н���ֵ��һ���ַ������ո��ַ���ʾ������
������������ʾ�Ķ�����T*/
Status CreateBiTree(BiTree &T)
{

	char ch;
	ch = getchar();
	if (ch == ' ')
		T = NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(OVERFLOW);
		T->data = ch;
		CreateBiTree(T->lchild);	//����������
		CreateBiTree(T->rchild);	//����������
	}
	return OK;
}

/*��ӡһ��Ԫ��*/
Status display(TElemType e)
{
	printf_s("%c", e);
	return OK;
}

/*�������������T ����ÿ�������ú���Visitһ���ҽ�һ�ˡ�
һ��visit()ʧ�ܣ������ʧ��*/
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if (visit(T->data) == OK)
			if (PreOrderTraverse(T->lchild, visit))
				if (PreOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}

/*�������������T ����ÿ�������ú���Visitһ���ҽ�һ�ˡ�
һ��visit()ʧ�ܣ������ʧ��*/
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if (InOrderTraverse(T->lchild, visit))
			if (visit(T->data) == OK)
				if (InOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}

/*�������������T ����ÿ�������ú���Visitһ���ҽ�һ�ˡ�
һ��visit()ʧ�ܣ������ʧ��*/
Status PosOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if (InOrderTraverse(T->lchild, visit))
			if (InOrderTraverse(T->rchild, visit))
				if (visit(T->data) == OK)
					return OK;
		return ERROR;
	}
	else
		return OK;
}


/*Ӧ��*/

//ͳ�ƶ�������Ҷ�ӽ����������������
void CountLeaf(BiTree T, int &count)
{
	if (T) {
		if ((!T->lchild) && (!T->rchild))
			count++;	//	Ҳ�ɺ��������������������������������
		CountLeaf(T->lchild, count);
		CountLeaf(T->rchild, count);
	}
}

//���������ȣ����������
int Depth(BiTree T)
{
	int depthval, depthLeft, depthRight;
	if (!T)
		depthval = 0;
	else {
		depthLeft = Depth(T->lchild);
		depthRight = Depth(T->rchild);
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);	//depth = Max{d1, d2} + 1
	}
	return depthval;
}

//����һ�����������
BiTNode *GetTreeNode(TElemType item, BiTNode *lptr, BiTNode *rptr)
{
	BiTree T;
	if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
		exit(OVERFLOW);
	T->data = item;
	T->lchild = lptr;
	T->rchild = rptr;
	return T;
}

//���ƶ����������������
BiTNode *CopyTree(BiTNode *T)
{
	BiTree newlptr, newrptr, newnode;
	if (!T)
		return NULL;
	if (T->lchild)
		newlptr = CopyTree(T->lchild);
	else
		newlptr = NULL;
	if (T->rchild)
		newrptr = CopyTree(T->rchild);
	else
		newrptr = NULL;
	newnode = GetTreeNode(T->data, newlptr, newrptr);
	return newnode;
}



bool IN(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return true;
	else
		return false;
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


//���ո������ʽ������Ӧ������
void CrtExptree(BiTree &T, char exp[])
{
	char c;
	Stack<char> S;
	char *p = exp;
	char ch = *p;
	while (!(S.top(c) == '#' && ch == '#')) {
		if (!IN(ch)) {
			BiTree t;
			CrtNode(t, ch);	//����Ҷ�ӽ�㲢��ջ
		}
		else {
			switch (ch)
			{
			case '(':
				S.push(ch);
				break;
			case ')':
				S.pop(c);
				while (c != '(') {
					BiTree t;
					CrtSubtree(t, c);	//������������ջ
					S.pop(c);
				}
				break;
			default:
				while (!S.top(c) && (precede(c, ch))) {
					BiTree t;
					CrtSubtree(t, c);
					S.pop(c);
				}
				if (ch != '#')
					S.push(ch);
				break;
			}
		}
		if (ch != '#') {
			p++;
			ch = *p;
		}
		PTR.pop(T);
	}
}

//����Ҷ�ӽ��
void CrtNode(BiTree &T, char ch)
{
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data = ch;
	T->lchild = T->rchild = NULL;
	PTR.push(T);
}

//��������
void CrtSubtree(BiTree &T, char e)
{
	BiTree lc, rc;
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data = e;
	PTR.pop(lc);
	T->lchild = lc;
	PTR.pop(rc);
	T->rchild = rc;
	PTR.push(T);
}