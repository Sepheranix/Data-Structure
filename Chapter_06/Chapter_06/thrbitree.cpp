/*线索二叉树实现及相关操作*/

#include "headers.h"

BiThrTree pre;

/*按先序顺序构造二叉树*/
Status CreateBiThrTree(BiThrTree &T)
{
	char ch;
	ch = getchar();
	if (ch == ' ')
		T = NULL;
	else {
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!T)
			exit(OVERFLOW);
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;
		CreateBiThrTree(T->lchild);	//构造左子树
		CreateBiThrTree(T->rchild);	//构造右子树
	}
	return OK;
}

//T指向头指针，头结点的左链lchild指向根指针，可参见线索化算法
//中序遍历二叉线索树T的非递归算法，对每个数据元素调用函数visit
Status InOrderTraverse_Thr(BiThrTree T, Status(*visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;	//p指向根结点
	while (p != T) {	//空树或遍历结束时，p == T
		while (p->LTag == Link)
			p = p->lchild;	//走到左子树尽头
		if (!visit(p->data))
			return ERROR;	//访问左子树为空的结点
		while (p->RTag == Thread && p->rchild != T) {
			//右链为线索，指向后继结点，当p为最后一个结点时， p->rchild == T(头结点)
			p = p->rchild;
			if (!visit(p->data))	//访问后继结点
				return ERROR;
		}
		p = p->rchild;	//右链不是线索时，将p指向其右子树，或者p指向头结点，表明遍历结束
	}
	return OK;
}

//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Link;	//建头结点
	Thrt->rchild = Thrt;	//头指针回指
	if (!T)
		Thrt->lchild = Thrt;	//若二叉树为空，则左指针回指
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);	//中序遍历进行线索化
		pre->rchild = Thrt;
		pre->RTag = Thread;	//最后一个结点线索化
		Thrt->rchild = pre;
	}
	return OK;
}

//中序遍历线索化
void InThreading(BiThrTree p)
{
	if (p) {
		InThreading(p->lchild);	//左子树线索化
		if (!p->lchild) {	//前驱线索
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!p->rchild) {	//后继线索
			p->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;	//保持pre指向p的前驱
		InThreading(p->rchild);	//右子树线索化
	}
}