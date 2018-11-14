/*����������ʵ�ּ���ز���*/

#include "headers.h"

BiThrTree pre;

/*������˳���������*/
Status CreateBiThrTree(BiThrTree &T)
{
	char ch;
	ch = getchar();
	if (ch == ' ')
		T = NULL;
	else {
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!T)
			exit(OVERFLOW);
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;
		CreateBiThrTree(T->lchild);	//����������
		CreateBiThrTree(T->rchild);	//����������
	}
	return OK;
}

//Tָ��ͷָ�룬ͷ��������lchildָ���ָ�룬�ɲμ��������㷨
//�����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���visit
Status InOrderTraverse_Thr(BiThrTree T, Status(*visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;	//pָ������
	while (p != T) {	//�������������ʱ��p == T
		while (p->LTag == Link)
			p = p->lchild;	//�ߵ���������ͷ
		if (!visit(p->data))
			return ERROR;	//����������Ϊ�յĽ��
		while (p->RTag == Thread && p->rchild != T) {
			//����Ϊ������ָ���̽�㣬��pΪ���һ�����ʱ�� p->rchild == T(ͷ���)
			p = p->rchild;
			if (!visit(p->data))	//���ʺ�̽��
				return ERROR;
		}
		p = p->rchild;	//������������ʱ����pָ����������������pָ��ͷ��㣬������������
	}
	return OK;
}

//�������������T��������������������Thrtָ��ͷ���
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Link;	//��ͷ���
	Thrt->rchild = Thrt;	//ͷָ���ָ
	if (!T)
		Thrt->lchild = Thrt;	//��������Ϊ�գ�����ָ���ָ
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);	//�����������������
		pre->rchild = Thrt;
		pre->RTag = Thread;	//���һ�����������
		Thrt->rchild = pre;
	}
	return OK;
}

//�������������
void InThreading(BiThrTree p)
{
	if (p) {
		InThreading(p->lchild);	//������������
		if (!p->lchild) {	//ǰ������
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!p->rchild) {	//�������
			p->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;	//����preָ��p��ǰ��
		InThreading(p->rchild);	//������������
	}
}