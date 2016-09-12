/*
 * MyString.h
 *
 *  Created on: 2016Äê9ÔÂ11ÈÕ
 *      Author: Administrator
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_
#include "Include.h"

typedef struct{
	char *ch;
	int length;
}HString;


Status StrAssign(HString &T,char *chars);
int StrLength(HString S);
int StrCompate(HString S,HString T);
Status ClearString(HString &S);
Status Concat(HString &T,HString S1,HString S2);
Status SubString(HString &Sub,HString S,int pos,int len);
void HStringTest();


#endif /* MYSTRING_H_ */
