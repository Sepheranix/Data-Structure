/*����������ʵ�ּ���ز���*/

#ifndef _THRBITREE_H_
#define _THRBITREE_H_

//------�������Ķ��������洢��ʾ------
typedef enum { Link, Thread } PointerTag;	//Link == 0:ָ�룬Thread == 1:����
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;	//���Һ���ָ��
	PointerTag LTag, RTag;	//���ұ�־
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree &T);
Status InOrderTraverse_Thr(BiThrTree T, Status(*visit)(TElemType e));
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);

#endif // !_THRBITREE_H_