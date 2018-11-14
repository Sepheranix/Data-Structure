/*二叉树的二叉链表存储表示*/

#ifndef _BITREE_H_
#define _BITREE_H_

typedef int TElemType;	//定义二叉树结点的数据类型
typedef struct BiTNode {	//定义二叉树结点
	TElemType data;
	struct BiTNode *lchild, *rchild;	//左右孩子指针
}BiTNode, *BiTree;



typedef int Status;

//基本操作
Status CreateBiTree(BiTree &T);
Status display(TElemType e);
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e));
Status PreOrderTraverse2(BiTree T, Status(*visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e));
Status InOrderTraverse2(BiTree T, Status(*visit)(TElemType e));
Status InOrderTraverse3(BiTree T, Status(*visit)(TElemType e));
Status PosOrderTraverse(BiTree T, Status(*visit)(TElemType e));
Status PostOrderTraverse2(BiTree T, Status(*visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e));

//应用
void CountLeaf(BiTree T, int &count);
int Depth(BiTree T);
BiTNode *GetTreeNode(TElemType item, BiTNode *lptr, BiTNode *rptr);
BiTNode *CopyTree(BiTNode *T);
void CrtExptree(BiTree &T, char exp[]);
void CrtNode(BiTree &T, char ch);
void CrtSubtree(BiTree &T, char c);

#endif // !_BITREE_H_
