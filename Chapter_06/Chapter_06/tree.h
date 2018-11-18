#ifndef _TREE_H_
#define _TREE_H_

//----- 树的双亲表示法，P135 -----
#define MAX_TREE_SIZE 100
typedef struct {	//结点结构
	TElemType data;
	int parent;	//双亲位置
}PTNode;

typedef struct {	//树结构
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;	//根的位置和结点数
}PTree;


//----- 树的孩子链表存储表示 ------
typedef struct CTNode {	//孩子结点
	int child;
	struct CTNode *next;
} *ChiledPtr;

typedef struct {
	TElemType data;
	ChiledPtr firstchild;	//孩子链表头指针
}CTBox;

typedef struct {
	CTBox nodes[MAX_TREE_SIZE];
	int n, r;	//结点数和根的位置
}CTree;


//------ 树的二叉链表（孩子-兄弟）存储表示 -------
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

//void CreatTree(CSTree &T);
//int TreeDepth(CSTree T);
//void AllPath(BiTree T, SqStack &S);
//void OutPath(BiTree T, SqStack &S);

#endif // !_TREE_H_
