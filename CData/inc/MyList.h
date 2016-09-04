/*
 * MyList.h
 *
 *  Created on: 2016年9月1日
 *      Author: Administrator
 */

#ifndef MYLIST_H_
#define MYLIST_H_

#include "Include.h"

#define ARRLIST_INIT_SIZE 50
#define ARRLISTINCREMENT 10

typedef  int ElemType;
typedef  int Status;

typedef struct{
	ElemType *elem;		//基地址
	int length;
	int listSize;
}ArrList;


void errInfo(char *info,int status);
void normalInfo(char *info);
void MyListTest();
Status initList(ArrList *L,int length);
Status isEmpty(ArrList *L);
Status insertList(ArrList *L,ElemType elem,int pos);
Status delList(ArrList *L,int pos);
void printArrList(ArrList *L);
Status mergeLists(ArrList *list1,ArrList *list2,ArrList *list3);
Status quickSort(ArrList *list,int left,int right);

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

Status initLinkList(LinkList &list);
Status createLinkList(LinkList list,int n);
Status printLinkList(LinkList list);
void testLinkList();
Status insertLinkList(LinkList list,ElemType elem,int pos);
Status delLinkList(LinkList list,int pos,ElemType &elem);


#endif /* MYLIST_H_ */
