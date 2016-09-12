/*
 * MyFIFO.cpp
 *
 *  Created on: 2016年9月6日
 *      Author: Administrator
 */
#include "Include.h"

int IsAQEmpty(AQueue *q)
{
	if(q->front==q->rear)return 1;
	else return 0;
}
//InitQueue(QUEUE *&Q) 传的是指针的地址。
void InitAQueue(AQueue *&q)
{
	q=(AQueue*)malloc(sizeof(ElemType)*MAX_AQUEUE);
	q->front=q->rear=-1;
}
void InAQueue(AQueue *q,ElemType e)
{
	if((q->rear+1)%MAX_AQUEUE==q->front)exit(-1);
	q->rear=(q->rear+1)%MAX_AQUEUE;
	q->elem[q->rear]=e;
}
void DeAQueue(AQueue *q,ElemType *e)
{
	if(IsAQEmpty(q)) exit(-1);
	q->front=(q->front+1)%MAX_AQUEUE;
	*e=q->elem[q->front];
}
void GetAQFront(AQueue *q,ElemType *e)
{
	if(IsAQEmpty(q)) exit(-1);
	*e=q->elem[(q->front+1)%MAX_AQUEUE];
}
void AQTest()
{
	AQueue *q;
	InitAQueue(q);
	InAQueue(q,1);
	InAQueue(q,2);
	ElemType e;
	DeAQueue(q,&e);
	cout<<"del "<<e<<endl;
}
/******************************************************/
Status InitLQueue(LQueue *q)
{
	q->front=(LqLinkList)malloc(sizeof(LqNode));
	if(!q->front)exit(-1);
	q->rear=q->front;
	q->front->next=NULL;
	return 0;
}
Status DestoryLQueue(LQueue *q)
{
	while(q->front){
		q->rear=q->front->next;
		free(q->front);
		q->front=q->rear;
	}
	return 0;
}
Status EnLQueue(LQueue *q,ElemType e)
{
	LqLinkList t;
	t=(LqLinkList)malloc(sizeof(LqNode));
	if(!t)exit(-1);
	t->elem=e;
	t->next=NULL;
	q->rear->next=t;
	q->rear=t;
	return 0;
}
Status DeLQueue(LQueue *q,ElemType &e)
{
	if(q->front==q->rear)exit(-1);
	LqLinkList t;
	t=q->front->next;
	e=t->elem;
	q->front->next=t->next;
	if(q->rear==t)q->rear=q->front;
	free(t);
	return 0;
}
void LQTest()
{
	LQueue q;
	InitLQueue(&q);
	EnLQueue(&q,1);
	EnLQueue(&q,2);
	ElemType e;
	DeLQueue(&q,e);
	cout<<"del "<<e<<endl;
}
