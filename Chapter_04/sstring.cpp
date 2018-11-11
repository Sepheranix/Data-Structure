#include "headers.h"

/*����һ����ֵ����chars�Ĵ�T, chars���ַ�������*/
Status StrAssign(SString &T, char *chars)
{
	int i = 0;
	while (chars[++i] != '\0' && i < MAXSTRLEN)
		T[i] = chars[i];
	T[0] = --i;	//�����ȸ���0�ŵ�Ԫ
	return 0;
}

/*�ɴ�S���Ƶô�T*/
Status StrCopy(SString &T, SString S)
{
	int i;
	for (i = 0; i <= S[0]; i++) {
		T[i] = S[i];
	}
	return 0;
}

/*��SΪ�մ�������true�����򷵻�false*/
bool StrEmpty(SString S)
{
	if (S[0] == 0)
		return TRUE;
	return FALSE;
}

/*��S>T, ����>0, S=T, =0, S<T, <0*/
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

/*���ش�����*/
int StrLength(SString S)
{
	return S[0];
}

/*��S���Ϊ�մ�*/
void ClearString(SString &S)
{
	S[0] = 0;
}

/*��T����S1��S2���������Ĵ�*/
void Concat(SString &T, SString S1, SString S2)
{
	int i = 1, j = 1;
	while (i <= S1[0] && i <= MAXSTRLEN) 
		T[i++] = S1[i++];
	while (j <= S2[0] && i <= MAXSTRLEN)
		T[i++] = S2[j++];
	T[0] = i - 1;
}

/*��ӡ��*/
void displayStr(SString T)
{
	for (int i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
}

/*��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ����������Ϸ�����ERROR, ���򷵻�OK*/
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

/*���㷨����������S�е�pos-1���ַ�����Ӵ�Tλ��, �����ڷ���0; ���У�TΪ�ǿմ���1<=pos<=StrLength(S)*/
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

/*��βƥ���㷨*/
int Index_FL(SString S, SString T, int pos)
{
	int slen = S[0];
	int tlen = T[0];
	int i = pos;
	char patStartChar = T[1];
	char patEndChar = T[tlen];

	while (i <= slen - tlen + 1) {
		if (S[i] != patStartChar)
			i++;	//ģʽ���ġ�ͷ�ַ�����ƥ�䣬���²���ƥ�����
		else if (S[i + tlen - 1] != patEndChar)
			i++;	//ģʽ���ġ�β�ַ�����ƥ�䣬���²���ƥ�����
		else {		//����м��ַ���ƥ�����
			int k = 1;
			int j = 2;
			while (j < tlen && S[i + k] == T[j]) {
				k++;
				j++;
			}
			if (j == tlen)
				return i;
			else	//���¿�ʼ��һ�ε�ƥ����
				i++;
		}
	}

}

/*KMP�㷨*/
int Index_KMP(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	int nextval[MAXSTRLEN];
	get_nextval(T, nextval);
	while (i <= S[0] && j <= T[0]) {
		if (j == 0 || S[i] == T[j]) {	//�����ȽϺ���ַ�
			i++;
			j++;
		}
		else
			j = nextval[j];	//ģʽ�������ƶ�
	}
	if (j > T[0])
		return i - T[0];	//ƥ��ɹ�
	else
		return 0;
}

/*��ģʽ��T��next����ֵ����������next*/
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

/*get_next�Ż�����ģʽ��T��next����ֵ����������nextval*/
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

/*�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T, ��ѭ�ض�ԭ��*/
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
	if (pos == S[0] + 1) {	//�������������
		while (S[0] + j <= MAXSTRLEN && j <= T[0]) {
			S[S[0] + j] = T[j];
			j++;
		}
		if (j <= T[0])	//�ռ䲻�����ض���
			S[0] = MAXSTRLEN;
		else
			S[0] = S[0] + T[0];
	}
	else {		//�����м�����
		for (i = S[0]; i >= pos; i--) {
			if (i + tlen <= MAXSTRLEN)
				S[i + tlen] = S[i];
			else
				k = i;	// �����λ��
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
			if (k != 0)	//����������
				S[0] = MAXSTRLEN;
			else
				S[0] = S[0] + T[0];
		}
	}
	return OK;
}

/*�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�*/
Status StrDelete(SString &S, int pos, int len)
{
	int i;
	if (pos < 1 || pos > S[0] - len + 1)
		return ERROR;
	if (S[0] == pos + len - 1)
		S[0] = S[0] - len;
	else {
		i = pos + len;
		while (i <= S[0]) {	//ɾ���Ӵ�
			S[i - len] = S[i];
			i++;
		}
		S[0] = S[0] - len;
	}
	return OK;
}

/*T�Ƿǿմ�����V�滻������������T��ȵĲ��ص����Ӵ�*/
Status Replace(SString &S, SString T, SString V)
{
	int pos;
	pos = 1;
	pos = Index(S, T, pos);
	while (0 != pos && ERROR != pos) {	//�ҵ����Ӵ�
		StrDelete(S, pos, T[0]);	//��ɾ���Ӵ�
		StrInsert(S, pos, V);		//�ٲ���Ҫ�滻�Ĵ�
		pos = Index(S, T, pos + V[0]);
	}
	return OK;
}
