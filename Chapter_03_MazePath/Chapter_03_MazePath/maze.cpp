#include "headers.h"

Status Pass(PosType pos)
{
	if (Map[pos.row][pos.col] == 1)
		return FALSE;
	else
		return TRUE;
}

void FootPrint(PosType pos)
{
	Map[pos.row][pos.col] = 1;
}

PosType NextPos(PosType pos, int di)
{
	switch (di)
	{
	case 1:
		pos.col++;
		break;
	case 2:
		pos.row++;
		break;
	case 3:
		pos.col--;
		break;
	case 4:
		pos.row--;
		break;
	default:
		break;
	}
	return pos;
}

void MarkPrint(PosType pos)
{
	Map[pos.row][pos.col] = 1;
}

Status MazePath(PosType start, PosType end)
{
	/*���Թ�maze�д��ڴ����start������end��ͨ���������һ�������ջ�У���ջ�׵�ջ������
	���ҷ���TURE�����򷵻�FALSE*/
	//InitStack(S);
	SElemType e;
	PosType curpos = start;		//�趨����ǰλ�á�Ϊ�����λ�á�
	int curstep = 1;			//̽����һ��
	do {
		if (Pass(curpos)) {	//��ǰλ�ÿ���ͨ��������δ���ߵ�������һ���ߵ�����ͨ����
			FootPrint(curpos);	//�����㼣
			e = { curstep, curpos, 1 };
			Push(S, e);		//����·��
			if (curpos.col == end.col && curpos.row == curpos.row) {
				//�����յ㣨���ڣ�
				printf_s("һ�����е�·�����£�\n");
				StackTraverse(S, print_path);
				return TRUE;
			}	
			curpos = NextPos(curpos, 1);	//��һλ���ǵ�ǰλ�õĶ���
			curstep++;		//̽����һ��
		}//if
		else {	//��ǰλ�ò���ͨ��
			if (!StackEmpty(S)) {
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)) {
					MarkPrint(e.seat);
					Pop(S, e);		//���²���ͨ���ı�ǣ����˻�һ��
				}//while
				if (e.di < 4) {
					e.di++;
					Push(S, e);		//��һ������̽��
					curpos = NextPos(e.seat, e.di);	//�趨��ǰλ���Ǹ��·����ϵ����ڿ�
				}//if
			}//if
		}//else
	} while (!StackEmpty(S));
	return FALSE;
}