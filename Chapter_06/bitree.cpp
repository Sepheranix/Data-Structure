/*二叉链表存储二叉树基本算法实现*/

#include "headers.h"

using namespace std;

/*按先序顺序输入二叉树中结点的值（一个字符），空格字符表示空树，
构造二叉链表表示的二叉树T*/
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
		CreateBiTree(T->lchild);	//构造左子树
		CreateBiTree(T->rchild);	//构造右子树
	}
	return OK;
}

/*打印一个元素*/
Status display(TElemType e)
{
	printf("%c", e);
	return OK;
}

/*先序遍历二叉树T ，对每个结点调用函数Visit一次且仅一此。
一旦visit()失败，则操作失败*/
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

/*中序遍历二叉树T ，对每个结点调用函数Visit一次且仅一此。
一旦visit()失败，则操作失败*/
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

/*后序遍历二叉树T ，对每个结点调用函数Visit一次且仅一此。
一旦visit()失败，则操作失败*/
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

/*层序遍历二叉树，利用队列实现*/
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
			else	//队列为空时，退出while循环
				break;
		}
	}
	return OK;
}

/*非递归法实现先序遍历二叉树T*/
Status PreOrderTraverse2(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//访问根节点，左指针进栈，遍历左子树
			if (!visit(p->data))
				return ERROR;
			Push(S, p);
			p = p->lchild;
		}
		else {		//左指针退栈，遍历右子树
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}

/*非递归法实现中序遍历二叉树T*/
Status InOrderTraverse2(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S, T);		// 根指针进栈
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p)	//向左走到尽头
			Push(S, p->lchild);
		Pop(S, p);		//空指针退栈
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (!visit(p->data))
				return ERROR;
			Push(S, p->rchild);
		} // if
	} // while
	return OK;
}

/*非递归法实现中序遍历二叉树T*/
Status InOrderTraverse3(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//根指针进栈，遍历左子树
			Push(S, p);
			p = p->lchild;
		}
		else {		//根指针退栈，访问根结点，遍历右子树
			Pop(S, p);
			if (!visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	return OK;
}

/*非递归法实现后序遍历二叉树T*/
Status PostOrderTraverse2(BiTree T, Status(*visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	int Tag[20];	//用来标志栈
	int t = 1;		//层数
	p = T;
	while (p || !StackEmpty(S)) {
		while (p) {	//向左走向尽头
			Push(S, p);
			p = p->lchild;
			Tag[t++] = 0;
		}
		while (!StackEmpty(S) && Tag[t - 1]) {	//结点标志为1表示右子树已经访问过
			Pop(S, p);
			t--;
			if (!visit(p->data))
				return ERROR;
		}
		if (!StackEmpty(S)) {	//结点标志为0,则访问右子树，并将结点标志为1
			Tag[t - 1] = 1;
			GetTop(S, p);
			p = p->rchild;
		}
		else
			break;
	}
	return OK;
}
