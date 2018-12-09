#include "headers.h"

//------算法7.4和7.5使用的全局变量------
Boolean visited[MAX_VERTEX_NUM];    //访问标志数组
Status (*VisitFunc)(ALGraph, int);           //函数变量

//算法7.4，对图G作深度优先遍历，数组visited[]为访问标准数组，Visit为访问函数
void DFSTraverse(ALGraph G, Status (*Visit)(ALGraph G, int v))
{
    int v;
    VisitFunc = Visit;          //使用全局变量VisitFunc，使DFS不必设函数指针参数
    for (v = 0; v < G.vexnum; v++)
        visited[v] = false;     //初始化标志数组
    for (v = 0; v < G.vexnum; v++) {
        if (!visited[v])        //对尚未访问过的结点调用DFS
            DFS(G, v);
    }
}

//从第v个顶点出发递归地深度优先遍历图G
void DFS(ALGraph G, int v)
{
    int w;
    visited[v] = true;
    VisitFunc(G, v);    //访问第v个结点
    for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
        if (!visited[w])
        DFS(G, w);      //对v的尚未访问的邻接点w递归调用DFS
    }
}

//打印图G中第v个顶点的信息
Status dispaly(ALGraph G, int v)
{
    printf("%c", G.vertices[v].data);
    return OK;
}

//算法7.6，按广度优先非递归遍历图G，使用辅助队列Q和访问标志数组visited
void BFSTraverse(ALGraph G, Status (*Visit)(ALGraph G, int v))
{
    int u, v, w;
    LinkQueue Q;
    InitQueue(Q);

    for (v = 0; v < G.vexnum; v++)
        visited[v] = false;
    
    for (v = 0; v < G.vexnum; v++) {
        
        if (!visited[v]) {
            visited[v] = true;
            Visit(G, v);
            EnQueue(Q, v);      //v入队列
            
            while(!QueueEmpty(Q)){
                DeQueue(Q, u);  //队头元素出队并置为u
                
                for( w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
                {       
                    
                    if (!visited[w]) {
                        visited[w] = true;
                        Visit(G, w);
                        EnQueue(Q, w);
                    }
                    
                }
                
            }
            
        }
        
    }
}


//------- 深度优先搜索遍历的应用 --------

static int cur_pos = 0;

void Append(char *PATH, char vex)
{
    PATH[cur_pos++] = vex;
}
void Delete()
{
    cur_pos = 0;
}

//求一条从顶点i到顶点s的简单路径，并记录在PATH中
void DFSearch(ALGraph G, int v, int s, char *PATH)
{
    visited[v] = true;  //访问第v个结点
    Append(PATH, GetVex(G, v));

    for (w = FirstAdjVex(G, v); w != 0 && !found; w = NextAdjVex(G, v)) {
        
        if (w == s) {
            found = true;
            Append(PATH, GetVex(G, w));
        }
        else if (!visited[w])
        {
            DFSearch(G, w, s, PATH);
        }
        if (!found)
            Delete();
    }
}








//算法7.7，建立无向图G的深度优先生成森林的孩子兄弟链表
Status DFSForst(ALGraph G, CSTree &T, bool visited[])
{
    int v;
    CSTree p, q;
    T = NULL;
    
    for( v = 0; v < G.vexnum; v++)
    {
        if(!visited[v]) {
            p = (CSTree)malloc(sizeof(CSNode));
            if(!p)
                return ERROR;
            p->data = GetVex(G, v);
            p->lchild = NULL;
            
        }
    }
    
}