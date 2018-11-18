/* �����еĻ�������ʵ�� */

#include "headers.h"

/**
 * ����һ���ն���Q
 */
Status InitQueue(LinkQueue &Q)
{
	Q.front = (QNode *)malloc(sizeof(QNode));
	if (!Q.front)
		return ERROR;
	Q.front->next = NULL;
	Q.rear = Q.front;
	return OK;
}

/**
 *  ���ٶ���
 */
Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

/**
 * ��Q���, ���ͷŽ��ռ�
 */
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

/**
 * �ж�Q�Ƿ�Ϊ��, �Ƿ���TRUE�����򷵻�FALSE
 */
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

/**
 * ����QԪ�ظ���
 */
int QueueLength(LinkQueue Q)
{
	QueuePtr p;
	int len = 0;
	p = Q.front->next;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

/**
 * �����в��գ���e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
 */
Status GetHead(LinkQueue Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = Q.front->next->data;
	return OK;
}

/**
 * ����Ԫ��eΪQ���µĶ�βԪ��
 */
Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QNode *)malloc(sizeof(QNode));   //�����µĽ��
	if (!p)
		return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

/**
 * �����в��գ�ɾ������Q�Ķ�ͷԪ�أ���e������ֵ������OK�����򷵻�ERROR
 */
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;
	p = Q.front->next;
	if (Q.front == Q.rear)
		return ERROR;
	e = p->data;
	if (Q.front->next == Q.rear)	//������ֻ��һ��Ԫ��ʱ����Ҫ�޸�βָ��
		Q.rear = Q.front;
	Q.front->next = p->next;
	free(p);
	p = NULL;
	return OK;
}

/**
 * �Ӷ�ͷ����β����Q��ÿ��Ԫ�ص���visit(), visit()ʧ�������ʧ��
 */
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType &e))
{
	QueuePtr p;
	p = Q.front->next;
	while (p) {
		if (!(*visit)(p->data))
			return ERROR;
		p = p->next;
	}
	return OK;
}