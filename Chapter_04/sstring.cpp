#include "headers.h"

/*生成一个其值等于chars的串T, chars是字符串常量*/
Status StrAssign(SString &T, char *chars)
{
	int i = 0;
	while (chars[++i] != '\0' && i < MAXSTRLEN)
		T[i] = chars[i];
	T[0] = --i;	//串长度赋给0号单元
	return 0;
}

/*由串S复制得串T*/
Status StrCopy(SString &T, SString S)
{
	int i;
	for (i = 0; i <= S[0]; i++) {
		T[i] = S[i];
	}
	return 0;
}

/*串S为空串，返回true，否则返回false*/
bool StrEmpty(SString S)
{
	if (S[0] == 0)
		return TRUE;
	return FALSE;
}

/*若S>T, 返回>0, S=T, =0, S<T, <0*/
Status StrCompare(SString S, SString T)
{
	int i = 1;
	while (i <= S[0] && i <= T[0]) {
		if (S[i] > T[i])
			return 1;
		else if (S[i] < T[i])
			return -1;
		else
			i++;
	}
	if (S[0] == T[0])
		return 0;
	else if (S[0] > T[0])
		return 1;
	else
		return -1;
}

/*返回串长度*/
int StrLength(SString S)
{
	return S[0];
}

/*将S清空为空串*/
void ClearString(SString &S)
{
	S[0] = 0;
}

/*用T返回S1和S2连接起来的串*/
void Concat(SString &T, SString S1, SString S2)
{
	int i = 1, j = 1;
	while (i <= S1[0] && i <= MAXSTRLEN) 
		T[i++] = S1[i++];
	while (j <= S2[0] && i <= MAXSTRLEN)
		T[i++] = S2[j++];
	T[0] = i - 1;
}

/*打印串*/
void displayStr(SString T)
{
	for (int i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
}

/*用Sub返回串S的第pos个字符起长度为len的子串，参数不合法返回ERROR, 否则返回OK*/
Status SubString(SString &Sub, SString S, int pos, int len)
{
	if (pos <  1 || pos + len > S[0] + 1 || len < 0 || pos > S[0])
		return ERROR;
	Sub[0] = len;
	for (int i = 1; i <= len; i++, pos++) {
		Sub[i] = S[pos];
	}
	return OK;
}

/*简单算法。查找主串S中第pos-1个字符后的子串T位置, 不存在返回0; 其中，T为非空串，1<=pos<=StrLength(S)*/
int Index(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	while (i <= S[0] && j <= T[0]) {
		if (S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T[0])
		return i - j + 1;
	return 0;
}

/*首尾匹配算法*/
int Index_FL(SString S, SString T, int pos)
{
	int slen = S[0];
	int tlen = T[0];
	int i = pos;
	char patStartChar = T[1];
	char patEndChar = T[tlen];

	while (i <= slen - tlen + 1) {
		if (S[i] != patStartChar)
			i++;	//模式串的“头字符”不匹配，重新查找匹配起点
		else if (S[i + tlen - 1] != patEndChar)
			i++;	//模式串的“尾字符”不匹配，重新查找匹配起点
		else {		//检查中间字符的匹配情况
			int k = 1;
			int j = 2;
			while (j < tlen && S[i + k] == T[j]) {
				k++;
				j++;
			}
			if (j == tlen)
				return i;
			else	//重新开始下一次的匹配检测
				i++;
		}
	}

}

/*KMP算法*/
int Index_KMP(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	int nextval[MAXSTRLEN];
	get_nextval(T, nextval);
	while (i <= S[0] && j <= T[0]) {
		if (j == 0 || S[i] == T[j]) {	//继续比较后继字符
			i++;
			j++;
		}
		else
			j = nextval[j];	//模式串向右移动
	}
	if (j > T[0])
		return i - T[0];	//匹配成功
	else
		return 0;
}

/*求模式串T的next函数值并存入数组next*/
void get_next(SString T, int next[])
{
	int i = 1;
	int j = 0;
	next[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

/*get_next优化，求模式串T的next函数值并存入数组nextval*/
void get_nextval(SString T, int nextval[]) 
{
	int i = 1;
	int j = 0;
	nextval[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {
			i++;
			j++;
			if (T[i] != T[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}

/*在串S的第pos个字符之前插入串T, 遵循截断原则*/
Status StrInsert(SString &S, int pos, SString T)
{
	if (pos < 1 || pos > S[0] + 1)
		return ERROR;
	int tlen, slen;
	int i, j, k;
	k = 0;
	tlen = T[0];
	slen = S[0];
	i = pos;
	j = 1;
	if (pos == S[0] + 1) {	//插在最后面的情况
		while (S[0] + j <= MAXSTRLEN && j <= T[0]) {
			S[S[0] + j] = T[j];
			j++;
		}
		if (j <= T[0])	//空间不够，截断了
			S[0] = MAXSTRLEN;
		else
			S[0] = S[0] + T[0];
	}
	else {		//插在中间的情况
		for (i = S[0]; i >= pos; i--) {
			if (i + tlen <= MAXSTRLEN)
				S[i + tlen] = S[i];
			else
				k = i;	// 溢出的位置
		}
		i = pos;
		j = 1;
		while (i <= MAXSTRLEN && j <= tlen) {
			S[i] = T[j];
			i++;
			j++;
		}
		if (j <= T[0])
			S[0] = MAXSTRLEN;
		else {
			if (k != 0)	//插入后溢出了
				S[0] = MAXSTRLEN;
			else
				S[0] = S[0] + T[0];
		}
	}
	return OK;
}

/*从串S中删除第pos个字符起长度为len的子串*/
Status StrDelete(SString &S, int pos, int len)
{
	int i;
	if (pos < 1 || pos > S[0] - len + 1)
		return ERROR;
	if (S[0] == pos + len - 1)
		S[0] = S[0] - len;
	else {
		i = pos + len;
		while (i <= S[0]) {	//删除子串
			S[i - len] = S[i];
			i++;
		}
		S[0] = S[0] - len;
	}
	return OK;
}

/*T是非空串，用V替换主串中所有与T相等的不重叠的子串*/
Status Replace(SString &S, SString T, SString V)
{
	int pos;
	pos = 1;
	pos = Index(S, T, pos);
	while (0 != pos && ERROR != pos) {	//找到了子串
		StrDelete(S, pos, T[0]);	//先删除子串
		StrInsert(S, pos, V);		//再插入要替换的串
		pos = Index(S, T, pos + V[0]);
	}
	return OK;
}
