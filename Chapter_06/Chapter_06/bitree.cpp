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


//���ո������ʽ������Ӧ������
void CrtExptree(BiTree &T, char exp[])
{
	SqStack S, PTR;
	InitStack(S);
	InitStack(PTR);
	Push(S, (int)'#');
}

//����Ҷ�ӽ��
void CrtNode(BiTree &T, char ch)
{

}

//��������
void CrtSubtree(BiTree &T, char c)
{

}