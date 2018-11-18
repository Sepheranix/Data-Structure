#ifndef _TREE_H_
#define _TREE_H_

//----- ����˫�ױ�ʾ����P135 -----
#define MAX_TREE_SIZE 100
typedef struct {	//���ṹ
	TElemType data;
	int parent;	//˫��λ��
}PTNode;

typedef struct {	//���ṹ
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;	//����λ�úͽ����
}PTree;


//----- ���ĺ�������洢��ʾ ------
typedef struct CTNode {	//���ӽ��
	int child;
	struct CTNode *next;
} *ChiledPtr;

typedef struct {
	TElemType data;
	ChiledPtr firstchild;	//��������ͷָ��
}CTBox;

typedef struct {
	CTBox nodes[MAX_TREE_SIZE];
	int n, r;	//������͸���λ��
}CTree;


//------ ���Ķ�����������-�ֵܣ��洢��ʾ -------
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

//void CreatTree(CSTree &T);
//int TreeDepth(CSTree T);
//void AllPath(BiTree T, SqStack &S);
//void OutPath(BiTree T, SqStack &S);

#endif // !_TREE_H_
