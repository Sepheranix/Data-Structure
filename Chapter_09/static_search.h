#pragma once

#include "my_type.h"
#include "tree.h"

typedef struct {
    ElemType *elem;         //静态表元素，0号单元存储要查询的关键字值，作"哨兵"用
    int length;                 //静态表长度
} SSTable;

typedef BiTree SOSTree;         //次优查找树

Status CreateTable(SSTable &ST, int n, char *filename);
void DestoryTable(SSTable &ST);
int Search_Seq(SSTable ST, KeyType key);
int Search_Bin(SSTable ST, KeyType key);
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high);
void get_table_sw(ElemType R[], float sw[], int length);
Status CreateSOSTree(SOSTree &T, SSTable ST);