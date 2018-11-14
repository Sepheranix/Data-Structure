/*�������Ķ�������洢��ʾ*/

#ifndef _BITREE_H_
#define _BITREE_H_

typedef int TElemType;	//���������������������
typedef struct BiTNode {	//������������
	TElemType data;
	struct BiTNode *lchild, *rchild;	//���Һ���ָ��
}BiTNode, *BiTree;



typedef int Status;

//��������
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

//Ӧ��
void CountLeaf(BiTree T, int &count);
int Depth(BiTree T);
BiTNode *GetTreeNode(TElemType item, BiTNode *lptr, BiTNode *rptr);
BiTNode *CopyTree(BiTNode *T);
void CrtExptree(BiTree &T, char exp[]);
void CrtNode(BiTree &T, char ch);
void CrtSubtree(BiTree &T, char c);

#endif // !_BITREE_H_
