#include <stdio.h>
#include "headers.h"

//算法7.1，采用数组（邻接矩阵）表示法，构造图G
Status CreateGraph(MGraph &G) {
    printf("DG = 0, DN =1, UDG = 2, UDN = 3\n");
    printf("构造图类型为：");
    scanf("%d", &G.kind);
    switch (G.kind) {
        case DG:    return CreateDG(G);
        case DN:    return CreateDN(G);
        case UDG:   return CreateUDG(G);
        case UDN:   return CreateUDN(G);
    }
}

//算法7.2，采用数组（邻接矩阵）表示法，构造无向图G
Status CreateUDG(MGraph &G)
{
    int IncInfo;
    int i, j, k;
    VertexType v1, v2;
    VRType w;
    printf("输入顶点数，弧数，弧信息标志（空格分隔）：");
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);    //IncInfo为1表弧相关信息
    getchar();  //接受最后的换行符
    printf("输入%d个顶点向量：", G.vexnum);
    for (i = 0; i < G.vexnum; ++i){ //构造顶点向量
        scanf("%c", &G.vexs[i]);
        getchar();
    }
    for (i = 0; i < G.vexnum; ++i){ //初始化邻接矩阵
        for (j = 0; j < G.vexnum; ++j){
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
    }
    printf("输入%d条边：\n", G.arcnum);
    for (k = 0; k < G.arcnum; k++){ //构造邻接矩阵
        printf("输入第%d条边依附的顶点及权值：", k + 1);
        scanf("%c %c %d", &v1, &v2, &w);
        getchar();
        i = LocateVex(G, v1);   //确定v1,v2在G中的位置
        j = LocateVex(G, v2);
        G.arcs[i][j].adj = w;   //弧<v1, v2>的权值
        if (IncInfo)            //如果弧有相关信息则输入
            Input(G.arcs[i][j].info);
        G.arcs[j][i] = G.arcs[i][j];    
    }
    return OK;
}

//采用数组（邻接矩阵）表示法，构造有向网G
Status CreateDN(MGraph &G)
{
    int IncInfo;
    int i, j, k;
    VertexType v1, v2;
    VRType w;
    printf("输入顶点数、弧数、弧信息标志（空格分隔）: ");	
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	//IncInfo为1表示弧有相关信息
	getchar();	//接收最后的换行符
	printf("输入%d个顶点向量：", G.vexnum);
	for (i = 0; i < G.vexnum; ++i) {		//构造顶点向量
		scanf("%c", &G.vexs[i]);
		getchar();	//接收最后的换行符
	}
	for (i = 0; i < G.vexnum; ++i) {		//初始化邻接矩阵
		for (j = 0; j < G.vexnum; ++j) {
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	printf("输入%d条边：\n", G.arcnum);
	for (k = 0; k < G.arcnum; ++k) {		//构造邻接矩阵
		printf("输入第%d条边依附的顶点及权值：", k + 1);
		scanf("%c %c %d", &v1, &v2, &w);
		getchar();	//接收最后的换行符
		i = LocateVex(G, v1);			//确定v1,v2在G中的位置
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;			//弧<v1, v2>的权值
		if (IncInfo)				//如果弧有相关信息则输入
			Input(G.arcs[i][j].info);
	}
	return OK;
}

//若G中顶点u存在，返回该顶点在图中的位置，否则返回ERROR
//即在G的顶点向量中查找u的位置
int LocateVex(MGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; ++i){
        if (G.vexs[i] == u)
            return i;
    }
    return ERROR;
}

int LocateVex(OLGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; ++i){
        if (G.xlist[i].data == u)
            return i;
    }
    return ERROR;
}

int LocateVex(ALGraph G, VertexType u)
{
    int i;
    for (i = 0; i <G.vexnum; ++i){
        if (G.vertices[i].data == u)
            return i;
    }
    return ERROR;
}

//输入弧相关信息
void Input(InfoType * &info)
{
    info = (InfoType *)malloc(50 * sizeof(InfoType));
    printf("输入弧的相关信息：");
    gets_s(info, 50 * sizeof(InfoType));
}

//创建邻接表存储的无向图
Status CreateUDG(ALGraph &G)
{
    int i, j, k, IncInfo;
    ArcNode *p;
    VertexType v1, v2;
    G.kind = UDG;   //无向图
    printf("请输入图的顶点数、弧数及弧信息标志：");
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
    getchar();
    printf("输入%d个顶点：", G.vexnum);
    for (i = 0; i < G.vexnum; ++i) {
        scanf("%c", &G.vertices[i].data);
        getchar();
        G.vertices[i].firstarc = NULL;
    }
    printf("输入%d条弧\n", G.arcnum);
    for (k = 0; k < G.arcnum; ++k) {
        printf("输入第%d条弧：", k + 1);
        scanf("%c %c", &v1, &v2);
        getchar();
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p = (ArcNode *)malloc(sizeof(ArcNode));
        if (!p) 
            return ERROR;
        p->nextarc = G.vertices[i].firstarc;
        p->adjvex = j;
        G.vertices[i].firstarc = p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        if (!p)
            return ERROR;
        p->nextarc = G.vertices[j].firstarc;
        p->adjvex = i;
        G.vertices[j].firstarc = p;
        if (IncInfo) {
            Input(p->info);
            G.vertices[i].firstarc->info = p->info;
        }
    }
    return OK;
}

//创建邻接表存储的有向图
Status CreateDG(ALGraph &G)
{
    int i, j, k, IncInfo;
    ArcNode *p;
    VertexType v1, v2;
    G.kind = DG;    //有向图
    printf("请输入有向图的顶点数、弧数及弧信息标志：");
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
    getchar();
    printf("输入%d个顶点：", G.vexnum);
    for (i = 0; i < G.vexnum; ++i) {
        scanf("%c", &G.vertices[i].data);
        getchar();
        G.vertices[i].firstarc = NULL;
    }
    printf("输入%d条弧（有向）\n", G.arcnum);
    for (k = 0; k < G.arcnum; ++k) {
        printf("输入第%d条弧：", k + 1);
        scanf("%c %c", &v1, &v2);
        getchar();
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p = (ArcNode *)malloc(sizeof(ArcNode));
        if (!p)
            return ERROR;
        p->nextarc = G.vertices[i].firstarc;
        p->adjvex = j;
        G.vertices[i].firstarc = p;
        if (IncInfo) {
            Input(p->info);
            G.vertices[i].firstarc->info = p->info;
        }
    }
    return OK;
}

//创建邻接表存储的有向网，弧信息即为权值
Status CreateDN(ALGraph &G)
{
    int i, j, k, IncInfo;
    ArcNode *p;
    char value[10];     //权值信息
    VertexType v1, v2;
    G.kind = DN;    //图的种类为有向网
    printf("请输入有向网的顶点数和弧数：");
    scanf("%d %d", &G.vexnum, &G.arcnum);
    getchar();
    printf("输入%d个顶点：", G.vexnum);
    
    for( i = 0; i < G.vexnum; i++)
    {
        scanf("%c", &G.vertices[i].data);
        getchar();
        G.vertices[i].firstarc = NULL;
    }

    printf("输入%d条弧（有向）\n", G.arcnum);
    
    for( k = 0; k < G.arcnum; k++)
    {
        printf("输入第%d条弧及权值（空格分隔）：", k + 1);
        scanf("%c %c %s", &v1, &v2, value);
        getchar();
        i = LocateVex(G, v1);   //头
        j = LocateVex(G, v2);   //尾
        p = (ArcNode *)malloc(sizeof(ArcNode));
        if (!p)
            return ERROR;
        p->nextarc = G.vertices[i].firstarc;
        p->adjvex = j;
        G.vertices[i].firstarc = p;
        G.vertices[i].firstarc->info = (char *)malloc(50 * sizeof(char));
        strcpy(G.vertices[i].firstarc->info, value);
    }
    return OK;
}

//邻接表存储表示的无向图G存在，V是G中的顶点
//返回指定第v个顶点的第一个邻接顶点的位置，若顶点在G中不存在邻接顶点，返回-1
int FirstAdjVet(ALGraph G, int v)
{
    if (G.vertices[v].firstarc != NULL)
    {
        return G.verticese[v].firstarc->adjvex;
    }
    else
    {
        return -1;
    }
}

//邻接表存储表示的无向图存在，v是G中的顶点，w的v的邻接点
//返回v的下一个（相对于w）的临界点的位置，若w是最后一个，则返回-1
int NextAdjVex(ALGraph G, int v, int w)
{
    ArcNode *p; //弧指针
    p = G.vertices[v].firstarc;
    
    while(p){   //查找w在v的邻接链表中的位置
        if(p->adjvex == w){
            p = p->nextarc;
            if(p != NULL)   //v的下一个（相对于w）邻接点存在
                return p->adjvex;
            else
                return -1;
        }
        else
            p = p->nextarc;
    }
}

//返回邻接表第v个结点的信息
VertexType GetVex(ALGraph G, int v)
{
    return G.vertices[v].data;
}

//算法7.3，创建十字链表存储表示的有向图
Status CreateDG(OLGraph &G)
{
    int i, j, k, IncInfo;
    VertexType v1, v2;
    ArcBox *p;
    printf("输入有向图顶点数和弧数及弧是否含信息(0/1)：");
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
    getchar();
    printf("输入%d个顶点（空格分隔）：", G.vexnum);
    
    for( i = 0; i < G.vexnum; i++)
    {
        scanf("%c", &G.xlist[i].data);
        G.xlist[i].firstin = NULL;
        G.xlist[i].firstout = NULL;
        getchar();
    }
    
    for( k = 0; k < G.armnum; k++)
    {
        printf("输入一条弧的起点和终点：");
        scanf("%c %c", &v1, &v2);
        getchar();
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p = (ArcBox *)malloc(sizeof(ArcBox));
        if (!p)
            return ERROR;
        (*p).headvex = j;
        (*p).tailvex = i;
        (*p).hlink = G.xlist[j].firstin;
        (*p).tlink = G.xlist[i].firstout;
        (*p).info = NULL;
        G.xlist[i].firstout = G.xlist[j].firstin = p;
        if (IncInfo)
            Input((*p).info);
    }
    return OK;
}