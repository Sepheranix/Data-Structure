#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "hash_table.h"

int hashsize[] = {11, 111, 997};    //哈希表容量递增表，一个合适的素数序列


//在开放定址哈希表H中查找关键字为K的元素，若查找成功，以p指示待查数据，并返回
//SUCCESS，否则以p指示插入位置，并返回UNSUCCESS，c统计冲突次数，其初值为0。
//当查找时发现哈希表已满时则重新哈希表扩大容量。
bool SearchHash(HashTable &H, KeyType K, int &p, int &c)
{
    c = 0;
    p = Hash(K, hashsize[H.sizeindex]);
    while (H.elem[p].key != NULLKEY && !EQ(K, H.elem[p].key)) {
        //表中有元素，而且关键字不等
        c++;    //冲突次数加一
        if (c == hashsize[H.sizeindex]) {   //哈希表已满，重建
            p = hashsize[H.sizeindex];      //插入位置
            RecreateHashTable(H);
            return true;
        }
        collision(p, c, hashsize[H.sizeindex]);
    }

    if EQ(K, H.elem[p].key)     //查找成功
        return true;
    else //查找不成功
        return false;
}

//哈希函数，直接定址法
int Hash(KeyType K, int p)
{
    return (K % p);
}

//产生冲突时，由开放地址法生成下一个位置，c为增量，len为哈希表长，由p返回位置
Status collision(int &p, int c, int len)
{
    if (c == len)
        return ERROR;
    else {
        p = (p + c) % len;
        return OK;
    }
}

//查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK,若冲突次数太大
//则重建哈希表并返回UNSUCCESS
Status InsertHash(HashTable &H, ElemType e)
{
    int p, c;
    c = 0;
    if (SearchHash(H, e.key, p, c) == true)
        return DUPLICATE;   //重复
    else if (c < hashsize[H.sizeindex] / 2) {   //冲突次数小于表长一半
        H.elem[p] = e;
        H.count++;
        return OK;
    }
    else {
        RecreateHashTable(H);
        return ERROR;
    }
}

//重建哈希表，成功返回OK,失败返回ERROR
Status RecreateHashTable(HashTable &H)
{
    H.elem = (ElemType *)realloc(H.elem, hashsize[H.sizeindex + 1] * sizeof(ElemType));
    if (H.elem == NULL)
        return ERROR;
    else {
        for (int i = hashsize[H.sizeindex]; i < hashsize[H.sizeindex + 1]; ++i)
            H.elem[i].key = NULLKEY;
        H.sizeindex++;
        return OK;
    }
}

Status InitHashTable(HashTable &H)
{
    H.sizeindex = 0;
    H.count = 0;
    H.elem = (ElemType *)malloc(hashsize[H.sizeindex] * sizeof(ElemType));
    if(H.elem == NULL)
        return ERROR;
    for (int i = 0; i < hashsize[H.sizeindex]; ++i)
        H.elem[i].key = NULLKEY;
    return OK;
}

Status CreateHashTable(HashTable &H, char *filename)
{
    ElemType e;
    FILE *pf;
    InitHashTable(H);
    pf = fopen(filename, "r");
    if (pf == NULL) {
        printf_s("打开文件%s失败！\n", filename);
        return ERROR;
    }
    while (fscanf(pf, "%d", &e.key) != EOF)
        InsertHash(H, e);
    fclose(pf);
    return OK;
}

//打印哈希表中的元素的关键字
void DisplayHashTable(HashTable H)
{
    for(size_t i = 0; i < hashsize[H.sizeindex]; i++)
        if (H.elem[i].key != NULLKEY)
            printf_s("%d", H.elem[i].key);
}