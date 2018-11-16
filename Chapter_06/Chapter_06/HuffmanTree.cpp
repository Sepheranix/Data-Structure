/*赫夫曼树及赫夫曼编码实现*/

#include "headers.h"

/*
**算法6.12，求赫夫曼编码的算法
**w存放n个字符的权值（大于零），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
*/
Status HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int m, i, s1, s2, start, current, further;
	HuffmanTree p;
	char *cd;
	s1 = s2 = 0;
	if (n <= 1)
		return ERROR;
	m = 2 * n - 1;	//一棵有n个结点的赫夫曼树有2 * n - 1个结点
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));	//0号单元未使用
	for (p = (HT + 1), i = 1; i <= n; ++i, ++p, ++w) 
		*p = { *w, 0, 0, 0 };	//初始化前n个结点，并将n个权值依次赋给它们
	for (; i <= m; ++i, ++p)
		*p = { 0, 0, 0, 0 };	//初始化其他向量
	for (i = n + 1; i <= m; ++i) {	//建赫夫曼树
		s1 = 0;
		s2 = 0;
		Select(HT, i - 1, s1, s2);	//找到权值最小的两个结点，且s1的权值小于s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//----从叶子结点到根逆向求每个字符的赫夫曼编码----
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));	//分配n个字符编码的头指针向量，0单元未用
	cd = (char *)malloc(n * sizeof(char));	//分配求编码的工作空间，n个字符的编码最多为n - 1位，最后一位存储‘\0’
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++) {	//逐个字符求赫夫曼编码
		start = n - 1;
		for (current = i, further = HT[i].parent; further != 0; current = further, further = HT[further].parent) {
			//从叶子开始到根逆向求编码
			if (current = HT[further].lchild)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc((n - start) * sizeof(char));	//为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	cd = NULL;
	return OK;
}

/*在数组HT[1...n]中选择parent为0且weight最小的两个结点，其序号分别为s1，s2，并且s1的权小于s2的权*/
Status Select(HuffmanTree HT, int n, int &s1, int &s2)
{
	int i;
	for (i = 1; i <= n; i++) {	//逐个查找权值最小的两个结点
		if (HT[i].parent == 0) {	//在权值为0的结点中寻找
			if (s1 == 0)
				s1 = i;
			else if (s2 = 0)
				s2 = i;
			else
				max(HT, s1, s2, i);
		}
	}
	if (s1 > s2) {
		i = s1;
		s1 = s2;
		s2 = i;
	}
	return OK;
}

/*s1,s2返回HT[n],s1,s2中权值最小的两个*/
void max(HuffmanTree HT, int &s1, int &s2, int n)
{
	if (HT[s1].weight < HT[s2].weight) {
		if (HT[n].weight < HT[s2].weight)
			s2 = n;
	}	
	else {
		if (HT[n].weight < HT[s1].weight)
			s1 = n;
	}
}

/*
**算法6.13，遍历赫夫曼树求编码，从根节点开始
**HT为已存在的赫夫曼树，HC保存字符编码, n为字符个数,即树的叶子个数
*/
void get_HuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	int i;
	char *cd;	//编码的工作空间
	int cdlen;	//编码长度
	char p;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));	//分配指向编码的头指针空间，0号单元未使用
	cd = (char *)malloc(n * sizeof(char));
	cdlen = 0;
	p = 2 * n - 1;	//p指向根节点

	for (i = 1; i <= p; i++)
		HT[i].weight = 0;	//遍历赫夫曼树时用作结点状态标志
	while (p) {

	}
}
