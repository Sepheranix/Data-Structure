#ifndef _SSTRING_H_
#define _SSTRING_H_

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1];
typedef int Status;

Status StrAssign(SString &T, char *chars);
Status StrCopy(SString &T, SString S);
bool StrEmpty(SString S);
Status StrCompare(SString S, SString T);
int StrLength(SString);
void ClearString(SString &S);
void Concat(SString &T, SString S1, SString S2);
void displayStr(SString T);
Status SubString(SString &Sub, SString S, int pos, int len);
int Index(SString S, SString T, int pos);
int Index_FL(SString S, SString T, int pos);
int Index_KMP(SString S, SString T, int pos);
void get_next(SString T, int next[]);
void get_nextval(SString T, int nextval[]);
Status Replace(SString &S, SString T, SString V);
Status StrInsert(SString &S, int pos, SString T);
Status StrDelete(SString &S, int pos, int len);


#endif // !_SSTRING_H_
