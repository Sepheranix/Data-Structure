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


/* B-树 */
#define m 3
#define RECORD_MAX_SIZE 100     //记录中字符的最大值
typedef char Record[RECORD_MAX_SIZE];

typedef struct BTNode {     //定义B-树的结点
    int keynum;             //结点中关键字个数
    struct BTNode *parent;  //指向双亲结点
    KeyType Key[m + 1];     //关键字向量，0号单元未使用
    struct BTNode *ptr[m + 1];  //子树指针向量
    Record recpter[m + 1];  //记录指针向量，0号单元未使用
} BTNode, *BTree;

typedef struct {
    BTNode *pt;             //指向找到的结点
    int i;                  //1...m,在结点中的序号
    int tag;                //1：查找成功，0：查找失败
} Result;                   //B-树的查找类型

Result SearchBTree(BTree T, KeyType K);
int Search(BTree T, KeyType K);
Status InsertBTree(BTree &T, KeyType K, BTree q, int i);
Status Insert(BTree p, int i, KeyType x, BTree ap);
Status split(BTree p, int s, BTree &ap);
Status NewRoot(BTree &T, BTree q, KeyType x, BTree ap);
Status CreateBTree(BTree &T, char *filename);
Status DisplayBTree(BTree T);

