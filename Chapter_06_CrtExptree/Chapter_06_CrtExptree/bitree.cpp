/*二叉链表存储二叉树基本算法实现*/

#include "headers.h"

using namespace std;



/*基本操作*/

/*按先序顺序输入二叉树中结点的值（一个字符），空格字符表示空树，
构造二叉链表表示的二叉树T*/
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
		CreateBiTree(T->lchild);	//构造左子树
		CreateBiTree(T->rchild);	//构造右子树
	}
	return OK;
}

/*打印一个元素*/
Status display(TElemType e)
{
	printf_s("%c", e);
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


/*应用*/

//统计二叉树中叶子结点个数（先序遍历）
void CountLeaf(BiTree T, int &count)
{
	if (T) {
		if ((!T->lchild) && (!T->rchild))
			count++;	//	也可后序遍历，但是能先序遍历便用先序遍历
		CountLeaf(T->lchild, count);
		CountLeaf(T->rchild, count);
	}
}

//求二叉树深度（后序遍历）
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

//生成一个二叉树结点
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

//复制二叉树（后序遍历）
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


//按照给定表达式建立相应二叉树
void CrtExptree(BiTree &T, char exp[])
{
	char c;
	Stack<char> S;
	char *p = exp;
	char ch = *p;
	while (!(S.top(c) == '#' && ch == '#')) {
		if (!IN(ch)) {
			BiTree t;
			CrtNode(t, ch);	//建立叶子结点并入栈
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
					CrtSubtree(t, c);	//建二叉树并入栈
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

//建立叶子结点
void CrtNode(BiTree &T, char ch)
{
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data = ch;
	T->lchild = T->rchild = NULL;
	PTR.push(T);
}

//建立子树
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