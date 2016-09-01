/*
 * MyList.cpp
 *
 *  Created on: 2016Äê9ÔÂ1ÈÕ
 *      Author: Administrator
 */

#include <MyList.h>

void errInfo(char *info,int status)
{
	cout<<*info<<endl;
	exit(status);
}
void normalInfo(char *info)
{
	cout<<*info<<endl;
}
void MyListTest()
{
	ArrList *list1,*list2,*list3;
	int ret;
	ret=initList(list1,10);
	if(ret<0){
		cout<<"init err"<<endl;
	}
	ret=isEmpty(list1);
	if(ret){
		cout<<"list is empty"<<endl;
	}
}

Status initList(ArrList *L,int length)
{
	if(length==0)length=ARRLIST_INIT_SIZE;
	ElemType *newbase=(ElemType *)malloc(length*sizeof(ArrList));
	L->elem=newbase;
	if(!L->elem){
		errInfo("malloc err",-1);
	}
	L->length=0;
	L->listSize=length;
	return 0;
}
Status isEmpty(ArrList *L)
{
	if(L->length==0)
		return 0;
	else
		return -1;
}
Status insertList(ArrList *L,ElemType elem,int pos)
{
	if(pos<0||pos>L->length)
		errInfo("insert:position is out of range",-1);
	if(L->length>=L->listSize){
		ElemType *newbase=(ElemType*)realloc(L->elem,(L->listSize+ARRLISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			errInfo("malloc err",-1);
		L->elem=newbase;
		L->listSize+=ARRLISTINCREMENT;
	}
	ElemType *p,*q;
	p=L->elem+pos;
	q=L->elem+L->length+1;
	while(q!=p){
		*q=*(q-1);
		q--;
	}
	*p=elem;
	L->length+=1;
	return 0;
}
Status delList(ArrList *L,int pos)
{
	if(pos<0||pos>L->length)
		errInfo("del:postion is out of range",-1);
	ElemType *p;
	p=L->elem+pos;
	while(p<L->elem+L->length){
		*p=*(p+1);
		p++;
	}
	L->length-=1;
	return 0;
}
void printArrList(ArrList *L)
{
	for(int i=0;i<L->length;i++){
		cout<<*(L->elem+i)<<"\t";
	}
	cout<<endl;
}
