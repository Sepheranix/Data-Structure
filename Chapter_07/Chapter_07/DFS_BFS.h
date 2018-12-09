#ifndef _DFS_BFS_H_
#define _DFS_BFS_H_

typedef VeretxType CSElemType;
typedef struct CSNode {
    CSElemType data;
    struct CSNode *lchild, *nextsibling;
} CSNode, *CSTree;

typedef struct //Prime算法辅助结构
{
    VertexType adjvex;
    VRType lowcost;
}lowedge[MAX_VERTEX_NUM];

typedef bool Boolean;

void DFSTraverse(ALGraph G, Status (*Visit)(ALGraph G, int v));
void DFS(ALGraph G, int v);
Status display(ALGraph G, int v);
void BFSTraverse(ALGraph G, Status (*Visit)(ALGraph G, int v));

Status DFSForst(ALGraph G, CSTree &T, bool visited[]);
Status DFSTree(ALGraph G, int v, CSTree T, bool visited[]);

#endif // !_DFS_BFS_H_
