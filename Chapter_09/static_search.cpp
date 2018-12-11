//静态链表查找的相关算法实现

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

#include "static_search.h"

//构造一个含n个数据元素的静态查找表ST，表中数据从指定文件filename中读取
//构造成功返回OK，打开文件失败错误返回FILE_NOT_EXIT，其他错误返回ERROR
Status CreateTable(SSTable &ST, int n, char *filename)
{
    FILE *pFile;
    ST.length = n;
    ST.elem = (ElemType *)malloc((ST.length + 1) * sizeof(ElemType));
    if (ST.elem)
        return ERROR;   //分配内存失败

    pFile = fopen(filename, "r");
    if (pFile == NULL) {
        printf_s("打开文件%s失败！\n", filename);
        return FILE_NOT_EXIT;
    }
    else {
        //打开文件成功
        
        for(size_t i = 1; i <= ST.length; i++)
        {
            
            if (EOF == fscanf(pFile, "%d %s %f", 
                &ST.elem[i].key, 
                &ST.elem[i].data, 
                &ST.elem[i].weight)) {
                //printf_s("读取记录出错！\n", i, filename, ST.length);
                printf_s("读取记录出错！\n");
                return ERROR;
            }
            
        }
        fclose(pFile);
        return OK;
    }
}


//静态查找表ST存在，销毁表ST
void DestroyTable(SSTable &ST)
{
    if (ST.elem != NULL) {
        free(ST.elem);
        ST.elem = NULL;
        ST.length = 0;
    }
    
}

//算法9.1，在顺序表ST中关键字等于key的数据元素
//若找到，返回元素位置，否则返回0
int Search_Seq(SSTable ST, KeyType key)
{
    int pos;
    ST.elem[0].key = key;   //哨兵
    for (pos = ST.length; !EQ(ST.elem[pos].key, key); pos--){
        ;
    }
    return pos;
}

//在有序表ST中折半查找其关键字等于key的数据元素。若找到，函数值为
//该元素在表中的位置，否则返回0
int Search_Bin(SSTable ST, KeyType key)
{
    int mid;
    int low = 1, high = ST.length;      //置区间初值
    
    while(low <= high){
        mid = (low + high) / 2;
        if (EQ(key, ST.elem[mid].key))
            return mid;                 //找到待查元素
        else if (LT(key, ST.elem[mid].key))
            high = mid - 1;             //继续在前半区间查找
        else
            low = mid + 1;              //继续在后半区间查找
    }

    //顺序表中不存在待查元素
    return 0;
}

//算法9.3，由有序表R[low...high]及其累计权值
//表sw(其中sw[0] == 0)递归构造次优查找树
// ΔPi = |(SWh + SWl-1) - (SWi + SWi-1)|
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high)
{
    int i, j;
    i = low;
    float min = abs(float(sw[high] - sw[low]));
    float dw = sw[high] + sw[low - 1];
    for (j = low + 1; j <= high; ++j)     //选择最小的ΔPi值
    {
        if(abs(float(dw - sw[j] - sw[j - 1])) < min) {
            i = j;
            min = abs(dw - sw[j] - sw[j - 1]);
        }
    }

    T = (BiTree)malloc(sizeof(BiTNode));
    T->data.key = R[i].key;
    if (i == low) {
        T->lchild = NULL;               //左子树为空
    }
    else{
        SecondOptimal(T->rchild, R, sw, i + 1, high);   //构造左子树
    }

    if (i == high) {
        T->rchild = NULL;               //左子树为空
    }
    else {
        SecondOptimal(T->rchild, R, sw, i + 1, high);   //构造右子树
    }
}

//计算有序表R[0...length]的累计权值，结果保存在sw[]中
void get_table_sw(ElemType R[], float sw[], int length)
{
    int i;
    sw[0] = 0;
    for (i = 1; i <= length; i++) {
        sw[i] = sw[i - 1] + R[i].weight;
    }
}

//算法9.4， 由有序表ST构造一棵次优查找树T
Status CreateSOSTree(SOSTree &T, SSTable ST)
{
    float *sw;
    sw = (float *)malloc((ST.length + 1) * sizeof(float));
    if (sw == NULL) {
        return ERROR;
    }
    if (ST.length)
        T = NULL;
    else {
        get_table_sw(ST.elem, sw, ST.length);
        SecondOptimal(T, ST.elem, sw, 1, ST.length);
    }
    return OK;
}