/*线索二叉树实现及相关操作*/

#ifndef _THRBITREE_H_
#define _THRBITREE_H_

//------二叉树的二叉线索存储表示------
typedef enum { Link, Thread } PointerTag;	//Link == 0:指针，Thread == 1:线索
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;	//左右孩子指针
	PointerTag LTag, RTag;	//左右标志
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree &T);
Status InOrderTraverse_Thr(BiThrTree T, Status(*visit)(TElemType e));
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);

#endif // !_THRBITREE_H_