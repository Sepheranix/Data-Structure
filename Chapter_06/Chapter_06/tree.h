#ifndef _TREE_H_
#define _TREE_H_

/* ����˫�ױ�ʾ����P135*/

#define MAX_TREE_SIZE 100
typedef struct {	//���ṹ
	TElemType data;
	int parent;	//˫��λ��
}PTNode;

typedef struct {	//���ṹ
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;	//����λ�úͽ����
}PTree;

#endif // !_TREE_H_
