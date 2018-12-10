#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynamic_search.h"

//在根指针T所指二叉树中递归地查找某关键字等于key的数组元素，
//若查找成功， 则返回指向该数据元素结点的的指针，否则返回空指针
BiTree SearchBST(BiTree T, KeyType key)
{
    if (!T || EQ(key, T->data.key))
        return (T);         //查找结束
    else if (LT(key, T->data.key))
        return (SearchBST(T->lchild, key)); //在右子树中继续查找
    else
        return (SearchBST(T->rchild, key));
}

//在根指针T所指二叉排序树中递归地查找其中关键字等于key的数据元素，若查找成功
//则指针p指向该数据元素结点，并返回TRUE，否则p指向查找路径上访问的
//最后一个结点并返回FALSE,指针f指向T的双亲，其初始值调用为NULL
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p)
{
    if (!T) {
        p = f;
        return FALSE;       //查找不成功
    }
    else if (EQ(key, T->data.key)) {
        p = T;
        return TRUE;        //查找成功
    }
    else if (LT(key, T->data.key))
        return SearchBST(T->lchild, key, T, p); //在左子树中继续查找
    else
        return SearchBST(T->rchild, key, T, p); //在右子树中继续查找
}

//当二叉排序树T中不存在关键字等于e.key的元素时，插入e并返回TRUE,
//否则返回FALSE
Status InsertBST(BiTree &T, ElemType e)
{
    BiTree p;
    BiTNode *s;
    if (!SearchBST(T, e.key, NULL, p)) {        //查找文件
        s = (BiTNode *)malloc(sizeof(BiTNode)); //新建一个要插入的结点
        s->data = e;
        s->lchild = NULL;
        s->rchild = NULL;

        if (p == NULL)                      //新插入的结点为根结点
            T = s;
        else if (LT(e.key, p->data.key))    //插入到左子树
            p->lchild = s;
        else                                //插入到右子树
            p->rchild = s;

        return OK;
    }
    else
        return ERROR;
}

//若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素的结点
//并返回TRUE，否则返回FALSE
Status DeleteBST(BiTree &T, KeyType key)
{
    if (!T)
        return FALSE;               //不存在关键字等于key的数据元素
    else {
        if (EQ(key, T->data.key))   //找到关键字等于key的数据元素
            return Delete(T);
        else if(LT(key, T->data.key))
            return DeleteBST(T->lchild, key);
        else
            return DeleteBST(T->rchild, key);
    }
}


//从二叉排序树中删除结点p，并重新接他的左右子树
Status Delete(BiTree &p)
{
    BiTree q, s;
    if (!p->rchild) {       //右子树空则只需要重接它的左子树
        q = p;
        p = p->lchild;
        free(q);
    }
    else if (!p->lchild) {  //左子树为空则只需要重接它的右子树
        q = p;
        p = p->rchild;
        free(q);
    }
    else {                  //左右子树均不空
        q = p;
        s = p->lchild;
        while (s->rchild) {
            q = s;
            s = s->lchild;  //左转，然后向右走到尽头
        }
        p->data = s->data;  //s指向被删结点的“前驱”
        if (q != p)
            q->rchild = s->lchild;  //重接*q的右子树
        else
            q->lchild = s->lchild;  //重接*q的左子树
        delete s;
    }
    return TRUE;
}

//对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树的根结点
//即旋转处理之前的左子树的根结点
void R_Rotate(BSTree &p)
{
    BSTree lc;
    lc = p->lchild;         //lc指向的*p的左子树根结点
    p->lchild = lc->rchild; //lc的右子树挂在p的左子树下
    lc->rchild = p;         //p挂在lc的左子树下
    p = lc;                 //p指向新的根结点
}

//对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树的根结点
//即旋转处理之前的右子树的根结点
void L_Roatate(BSTree &p)
{
    BSTree rc;
    rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}