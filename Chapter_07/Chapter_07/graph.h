#pragma once

#define MAX_VERTEX_NUM 20					//ͼ��󶥵����
typedef enum {DG, DN, UDG, UDN} GraphKind;	//����ͼ��������������ͼ��������
typedef char InfoType;						//�������Ϣָ��
typedef char VertexType;					//��������

//------ ͼ�����飨�ڽӾ��󣩴洢��ʾ -------
#define INFINITY INT_MAX					//���ֵ
typedef int VRType;							//�����ϵ���ͣ�����Ȩͼ����0��1��ʾ�Ƿ����ڣ��Դ�Ȩͼ����ʾȨֵ����
typedef struct ArcCell {
	VRType adj;	                            //Ȩֵ
	InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];		//��������
	AdjMatrix arcs;							//�ڽӾ���
	int vexnum, arcnum;						//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;							//ͼ�������־
}MGraph;