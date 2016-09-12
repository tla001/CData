/*
 * MyString.cpp
 *
 *  Created on: 2016Äê9ÔÂ11ÈÕ
 *      Author: Administrator
 */

#include "MyString.h"

Status StrAssign(HString &T,char *chars)
{
	if(*chars==NULL)exit(-1);
	if(T.ch)
		free(T.ch);
	int length=0;
	char *c=chars;
	while(*c++!='\0'){
		++length;
	}
	if(length==0){
		T.ch=NULL;
		T.length=0;
	}else{
		if(!(T.ch=(char *)malloc(length*sizeof(char)))){
			exit(-1);
		}
		int i;
		for(i=0;i<length;i++){
			T.ch[i]=chars[i];
		}
		T.ch[i]='\0';
		T.length=length;
	}
	return 0;
}
int StrLength(HString S)
{
	return S.length;
}
int StrCompate(HString S,HString T)
{
	for(int i=0;i<S.length&&i<T.length;i++)
		if(S.ch[i]!=T.ch[i])return S.ch[i]-T.ch[i];
	return S.length-T.length;
}
Status ClearString(HString &S)
{
	if(S.ch){
		free(S.ch);
		S.ch=NULL;
	}
	S.length=0;
	return 0;
}
Status Concat(HString &T,HString S1,HString S2)
{
	if(T.ch)free(T.ch);
	if(!(T.ch=(char*)malloc((S1.length+S2.length)*sizeof(char))))
		exit(-1);
	for(int i=0;i<S1.length;i++){
		T.ch[i]=S1.ch[i];
	}
	for(int i=0;i<S2.length;i++){
		T.ch[S1.length+i]=S2.ch[i];
	}
	T.length=S1.length+S2.length;
	return 0;
}
Status SubString(HString &Sub,HString S,int pos,int len)
{
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
		exit(-1);
	if(Sub.ch)free(Sub.ch);
	if(!len){
		Sub.ch=NULL;
		Sub.length=0;
	}
	else{
		Sub.ch=(char*)malloc(sizeof(char)*len);
		int i;
		for(i=0;i<len;i++){
			Sub.ch[i]=S.ch[i+pos];
		}
		Sub.ch[i]='\0';
		Sub.length=len;
	}
	return 0;
}
void HStringTest()
{
	HString str1,str2,str3,str4,str5;
	char *ss1="hello";
	char *ss2="hellow";
	char *ss3="a";
	char *ss4="a";
	StrAssign(str1,ss1);
	StrAssign(str2,ss2);
	StrAssign(str3,ss3);
	StrAssign(str5,ss4);
	cout<<"str1: len: "<<str1.length<<" chars: "<<str1.ch<<endl;
	cout<<"str2: len: "<<str2.length<<" chars: "<<str2.ch<<endl;
	cout<<StrCompate(str1,str2)<<endl;
	Concat(str3,str1,str2);
	cout<<"str3: len: "<<str3.length<<" chars: "<<str3.ch<<endl;
	SubString(str5,str1,1,2);
	cout<<"str5: len: "<<str5.length<<" chars: "<<str5.ch<<endl;
	ClearString(str3);
	cout<<"str3: len: "<<str3.length<<" chars: "<<str3.ch<<endl;
}
