#ifndef _MAZE_H_
#define _MAZE_H_

#include "type.h"

Status Pass(PosType pos);
void FootPrint(PosType pos);
PosType NextPos(PosType pos, int di);
void MarkPrint(PosType pos);
Status MazePath(PosType start, PosType end);

#endif // !_MAZE_H_

