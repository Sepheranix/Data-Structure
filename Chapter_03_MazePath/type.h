/* �궨�弰���Ͷ��� */
#ifndef _TYPE_H_
#define _TYPE_H_

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100     //ջ��ʼ��ֵ
#define STACKINCREMENT 10       //ջ����ÿ�����ӵ�ֵ
#define SIZE 10			//�����Թ���ͼ��С

typedef struct {
	int row;    // �У�0��ʼ
	int col;    // �У�0��ʼ
}PosType;

typedef struct {
	int ord;	// ͨ������·���ϵ����
	PosType seat;   // ͨ�������Թ��е�����λ��
	int di;		//�Ӵ�ͨ��������һͨ����ķ���
}SElemType;

typedef int Status;

#endif