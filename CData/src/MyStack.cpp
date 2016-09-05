/*
 * MyStack.cpp
 *
 *  Created on: 2016年9月5日
 *      Author: Administrator
 */
#include "MyStack.h"
/************************顺序栈*************************************************/
Status InitSqStack(SqStack &s)
{
	s.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!s.base)exit(-1);
	s.top=s.base;
	s.stackSize=STACK_INIT_SIZE;
	return 0;
}
Status SqGetTop(SqStack s,SElemType &e)
{
	if(s.base==s.top)return -1;
	e=*(s.top-1);
	return 0;
}
Status SqPush(SqStack &s,SElemType e)
{
	if(s.top-s.base>=STACK_INIT_SIZE){
		s.base=(SElemType*)realloc(s.base,(s.stackSize+STACKINCREMENT)*sizeof(SElemType));
		if(!s.base)return -1;
		s.top=s.base+s.stackSize;
		s.stackSize+=STACKINCREMENT;
	}
	*s.top++=e;
	return 0;
}
Status SqPop(SqStack &s,SElemType &e)
{
	if(s.top==s.base)return -1;
	e=*--s.top;
	return 0;
}

void SqStackTest()
{
	SqStack s;
	InitSqStack(s);
	for(int i=2;i<5;i++)
		SqPush(s,i);
	SElemType e=0;
	SqGetTop(s,e);
	cout<<"top "<<e<<endl;
	SqPop(s,e);
	cout<<"pop "<<e<<endl;
	SqGetTop(s,e);
	cout<<"top "<<e<<endl;
}
/************************链表栈*************************************************/
Status InitLStack(LStack &s)
{
	s.top=NULL;
	return 0;
}
Status LGetTop(LStack &s,LElemType &e)
{
	if(s.top==NULL)return -1;
	e=s.top->data;
	return 0;
}
Status LPush(LStack &s,LElemType e)
{
	LinkListS p=(LinkListS)malloc(sizeof(LiNode));
	if(!p)return -1;
	p->data=e;
	p->next=s.top;
	s.top=p;
	return 0;
}
Status LPop(LStack &s,LElemType &e)
{
	if(s.top==NULL) return -1;
	e=s.top->data;
	s.top=s.top->next;
	return 0;
}
void LStackTest()
{
	LStack s;
	InitLStack(s);
	for(int i=2;i<9;i++)
		LPush(s,i);
	LElemType e=0;
	LGetTop(s,e);
	cout<<"top "<<e<<endl;
	LPop(s,e);
	cout<<"pop "<<e<<endl;
	LGetTop(s,e);
	cout<<"top "<<e<<endl;
}
