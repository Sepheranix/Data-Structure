/*��������洢�����������㷨ʵ��*/

#include "headers.h"

using namespace std;

/*������˳������������н���ֵ��һ���ַ������ո��ַ���ʾ������
������������ʾ�Ķ�����T*/
Status CreateBiTree(BiTree &T)
{

	char ch;
	scanf("%c", &ch);
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
	printf("%c", e);
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

/*������������������ö���ʵ��*/
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	BiTree p;
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	while (p || !QueueEmpty(Q)) {
		if (p) {
			visit(p->data);
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
			if (!QueueEmpty(Q))
				DeQueue(Q, p);
			else	//����Ϊ��ʱ���˳�whileѭ��
				break;
		}
	}
	return OK;
}

/*�ǵݹ鷨ʵ���������������T*/
Status PreOrderTraverse2(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//���ʸ��ڵ㣬��ָ���ջ������������
			if (!visit(p->data))
				return ERROR;
			Push(S, p);
			p = p->lchild;
		}
		else {		//��ָ����ջ������������
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}

/*�ǵݹ鷨ʵ���������������T*/
Status InOrderTraverse2(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S, T);		// ��ָ���ջ
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p)	//�����ߵ���ͷ
			Push(S, p->lchild);
		Pop(S, p);		//��ָ����ջ
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (!visit(p->data))
				return ERROR;
			Push(S, p->rchild);
		} // if
	} // while
	return OK;
}

/*�ǵݹ鷨ʵ���������������T*/
Status InOrderTraverse3(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//��ָ���ջ������������
			Push(S, p);
			p = p->lchild;
		}
		else {		//��ָ����ջ�����ʸ���㣬����������
			Pop(S, p);
			if (!visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	return OK;
}

/*�ǵݹ鷨ʵ�ֺ������������T*/
Status PostOrderTraverse2(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	int Tag[20];	//������־ջ
	int t = 1;		//����
	p = T;
	while (p || !StackEmpty(S)) {
		while (p) {	//��������ͷ
			Push(S, p);
			p = p->lchild;
			Tag[t++] = 0;
		}
		while (!StackEmpty(S) && Tag[t - 1]) {	//����־Ϊ1��ʾ�������Ѿ����ʹ�
			Pop(S, p);
			t--;
			if (!visit(p->data))
				return ERROR;
		}
		if (!StackEmpty(S)) {	//����־Ϊ0,���������������������־Ϊ1
			Tag[t - 1] = 1;
			GetTop(S, p);
			p = p->rchild;
		}
		else
			break;
	}
	return OK;
}
