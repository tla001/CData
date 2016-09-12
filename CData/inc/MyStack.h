/*
 * MyStack.h
 *
 *  Created on: 2016Äê9ÔÂ5ÈÕ
 *      Author: Administrator
 */

#ifndef MYSTACK_H_
#define MYSTACK_H_

#include "Include.h"

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;
typedef int Status;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stackSize;
}SqStack;

Status InitSqStack(SqStack &s);
Status SqGetTop(SqStack s,SElemType &e);
Status SqPush(SqStack &s,SElemType e);
Status SqPop(SqStack &s,SElemType &e);
void SqStackTest();
/*************************************************************************/
typedef  int LElemType;
typedef struct LiNode{
	LElemType data;
	struct LiNode *next;
}LiNode,*LinkListS;
typedef struct LStack{
	LinkListS top;
}LStack;

Status InitLStack(LStack &s);
Status LGetTop(LStack &s,LElemType &e);
Status LPush(LStack &s,LElemType e);
Status LPop(LStack &s,LElemType &e);
void LStackTest();

void hanoiTest();

#endif /* MYSTACK_H_ */
