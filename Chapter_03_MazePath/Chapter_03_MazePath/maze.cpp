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
	/*若迷宫maze中存在从入口start到出口end的通道，则求得一条存放在栈中（从栈底到栈顶），
	并且返回TURE；否则返回FALSE*/
	//InitStack(S);
	SElemType e;
	PosType curpos = start;		//设定“当前位置”为“入口位置”
	int curstep = 1;			//探索第一步
	do {
		if (Pass(curpos)) {	//当前位置可以通过，即是未曾走到过（第一次走到）的通道块
			FootPrint(curpos);	//留下足迹
			e = { curstep, curpos, 1 };
			Push(S, e);		//加入路径
			if (curpos.col == end.col && curpos.row == curpos.row) {
				//到达终点（出口）
				printf_s("一条可行的路径如下：\n");
				StackTraverse(S, print_path);
				return TRUE;
			}	
			curpos = NextPos(curpos, 1);	//下一位置是当前位置的东邻
			curstep++;		//探索下一步
		}//if
		else {	//当前位置不能通过
			if (!StackEmpty(S)) {
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)) {
					MarkPrint(e.seat);
					Pop(S, e);		//留下不能通过的标记，并退回一步
				}//while
				if (e.di < 4) {
					e.di++;
					Push(S, e);		//换一个方向探索
					curpos = NextPos(e.seat, e.di);	//设定当前位置是该新方向上的相邻块
				}//if
			}//if
		}//else
	} while (!StackEmpty(S));
	return FALSE;
}