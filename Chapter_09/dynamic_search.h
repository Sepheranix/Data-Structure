#pragma once

#include "my_type.h"
#include "tree.h"

/* 二叉排序树基本操作 */
BiTree SearchBST(BiTree T, KeyType key);
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p);
Status InsertBST(BiTree &T, ElemType e);
Status DeleteBST(BiTree &T, KeyType key);
Status Delete(BiTree &p);


/* AVL平衡树 */
#define LH +1               //左高
#define EH 0                //等高
#define RH -1               //右高 

typedef struct BSTNode {
    ElemType data;          
    int bf;                             //结点的平衡因子
    struct BSTNode *lchild, *rchild;    //左右孩子指针
} BSTNode, *BSTree;

void R_Rotate(BSTree &p);
void L_Rotate(BSTree &p);
Status InsertAVL(BSTree &T, ElemType e, Boolean &taller);
void LeftBalance(BSTree &T);
void RightBalance(BSTree &T);