#pragma once

#define MAX_VERTEX_NUM 20					//图最大顶点个数
typedef enum {DG, DN, UDG, UDN} GraphKind;	//有向图，有向网，无向图，无向网
typedef char InfoType;						//弧相关信息指针
typedef char VertexType;					//顶点类型

//------ 图的数组（邻接矩阵）存储表示 -------
#define INFINITY INT_MAX					//最大值
typedef int VRType;							//顶点关系类型，对无权图，用0，1表示是否相邻；对带权图，表示权值类型
typedef struct ArcCell {
	VRType adj;	                            //权值
	InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];		//顶点向量
	AdjMatrix arcs;							//邻接矩阵
	int vexnum, arcnum;						//图的当前顶点数和弧数
	GraphKind kind;							//图的种类标志
}MGraph;