/* �����еĻ�������ʵ�� */

#include "headers.h"

/*����һ���ն���Q*/
Status InitQueue(LinkQueue &Q)
{
	Q.front = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		return ERROR;
	Q.front->next = NULL;
	Q.rear = Q.front;
	return OK;
}

/*���ٶ���*/
Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

/*��Q���, ���ͷŽ��ռ�*/
Status ClearQueue(LinkQueue &Q)
{
	QueuePtr p, temp;
	p = Q.front->next;
	Q.front->next = NULL;
	Q.rear = Q.front;
	while (p) {
		temp = p->next;
		free(p);
		p = temp;
	}
	return OK;
}

/*�ж�Q�Ƿ�Ϊ��, �Ƿ���TRUE�����򷵻�FALSE*/
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

/*����QԪ�ظ���*/
int QueueLength(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return ERROR;
	int i = 0;
	QueuePtr p = Q.front->next;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}

/*�����в��գ���e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR*/
Status GetHead(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = Q.front->next->data;
	return OK;
}

/*����Ԫ��eΪQ���µĶ�βԪ��*/
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

/*�����в��գ�ɾ������Q�Ķ�ͷԪ�أ���e������ֵ������OK�����򷵻�ERROR*/
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	QueuePtr p = Q.front->next;
	if (Q.front->next == Q.rear)	//������ֻ��һ��Ԫ��ʱ����Ҫ�޸�βָ��
		Q.rear = Q.front;
	Q.front->next = p->next;
	e = p->data;
	free(p);
	p = NULL;
	return OK;
}

/*�Ӷ�ͷ����β����Q��ÿ��Ԫ�ص���visit(), visit()ʧ�������ʧ��*/
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType &e))
{
	QueuePtr p = Q.front->next;
	while (p) {
		if (!(*visit)(p->data))
			return ERROR;
		p = p->next;
	}
	return OK;
}

///*��ӡԪ��*/
//Status visit_display(QElemType &e)
//{
//	printf_s("%d ", e);
//	return OK;
//}