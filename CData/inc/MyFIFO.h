/*
 * MyFIFO.h
 *
 *  Created on: 2016Äê9ÔÂ6ÈÕ
 *      Author: Administrator
 */

#ifndef MYFIFO_H_
#define MYFIFO_H_

#include "Include.h"

typedef int Status;
typedef int ElemType;

#define MAX_AQUEUE 10

typedef struct aqueue{
	ElemType elem[MAX_AQUEUE];
	int front;
	int rear;
}AQueue;

int IsAQEmpty(AQueue *q);
void InitAQueue(AQueue *&q);
void InAQueue(AQueue *q,ElemType e);
void DeAQueue(AQueue *q,ElemType *e);
void GetAQFront(AQueue *q,ElemType *e);
void AQTest();

/******************************************************/
typedef struct LqNode{
	ElemType elem;
	struct LqNode *next;
}LqNode,*LqLinkList;

typedef struct lqueue{
	LqLinkList front;
	LqLinkList rear;
}LQueue;

Status InitLQueue(LQueue *q);
Status DestoryLQueue(LQueue *q);
Status EnLQueue(LQueue *q,ElemType e);
Status DeLQueue(LQueue *q,ElemType &e);
void LQTest();

#endif /* MYFIFO_H_ */
