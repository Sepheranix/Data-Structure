//链队列的基本操作实现

#pragma once

typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {       //定义链队列
	QueuePtr front;   //队头指针
	QueuePtr rear;	  //队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead(LinkQueue Q, QElemType &e);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
Status QueueTraverse(LinkQueue Q, Status (*visit)(QElemType &e));
Status visit_display(QElemType &e);