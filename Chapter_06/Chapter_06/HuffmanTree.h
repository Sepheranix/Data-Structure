#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

typedef struct {
	unsigned int weight;	//权重结点
	unsigned int parent, lchild, rchild;	//定义双亲结点，左孩子，右孩子位置
}HTNode, *HuffmanTree;	//动态分配数组存储赫夫曼树

typedef char * *HuffmanCode;	//动态分配数组存储赫夫曼编码表

Status HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
Status Select(HuffmanTree HT, int n, int &s1, int &s2);
void max(HuffmanTree HT, int &s1, int &s2, int n);
void get_HuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n);

#endif // !_HUFFMAN_TREE_H_
