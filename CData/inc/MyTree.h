/*
 * MyTree.h
 *
 *  Created on: 2016年9月12日
 *      Author: Administrator
 */

#ifndef MYTREE_H_
#define MYTREE_H_

#include "Include.h"

typedef char TElemType;

typedef struct BitNode {
	TElemType data;
	struct BitNode *lchild, *rchild;
} BitNode, *BitTree;

Status CreateBitTree(BitTree &T);
Status PreOrderTraverse(BitTree T);
Status InOrderTraverse(BitTree T);
Status PostOrderTraverse(BitTree T);
void LevelOrderTraverse(BitTree T);
Status Visit(BitTree &T);
void BitTreeTest();
void PreOrderTraverseFor(BitTree T);
void InOrderTraverseFor(BitTree T);
void PostOrderTraverseFor(BitTree T);

typedef BitTree StackElemType;
typedef BitTree QueueElemType;

#define MAX 10 // MAXIMUM STACK CONTENT
#define MAX_QUEUE 10 // MAXIMUM QUEUE CONTENT
class stack {
private:
	StackElemType arr[MAX];
	int tag[MAX];
	int top;
public:
	stack() {
		inItStack();
	}
	/************************************************************************/
	/* 初始化栈                                                                     */
	/************************************************************************/
	void inItStack() {
		top = -1;
	}
	/************************************************************************/
	/* 入栈                                                                     */
	/************************************************************************/
	void push(StackElemType a) {
		top++;
		if (top < MAX) {
			arr[top] = a;
		} else {
			cout << "STACK FULL!!" << top;
		}
	}
	/************************************************************************/
	/* 出栈                                                                     */
	/************************************************************************/
	StackElemType pop() {
		if (isEmpty()) {
			cout << "STACK IS EMPTY ";
			return NULL;
		} else {
			StackElemType data = arr[top];
			arr[top] = NULL;
			top--;
			return data;
		}
	}

	/************************************************************************/
	/* 出栈                                                                     */
	/************************************************************************/
	StackElemType getTop() {
		if (isEmpty()) {
			cout << "STACK IS EMPTY ";
			return NULL;
		} else {
			return arr[top];
		}
	}
	/************************************************************************/
	/* 是否为空                                                                     */
	/************************************************************************/
	bool isEmpty() {
		if (top == -1)
			return true;
		else
			return false;
	}

	int SetTag(int v) {
		tag[top] = v;
	}
	int GetTag() {
		return tag[top];
	}
};

class queue {
private:
	QueueElemType elem[MAX_QUEUE];     ///假设当数组只剩下一个单元时认为队满
	int front;      //队头指针
	int rear;       //队尾指针
public:
	/************************************************************************/
	/*
	 初始化
	 直接使用结构体指针变量，必须先分配内存地址，即地址的指针
	 */
	/************************************************************************/
	void InitQueue() {
		front = rear = -1;

	}
	/************************************************************************/
	/*     入队
	 */
	/************************************************************************/

	void EnQueue(QueueElemType e) {
		if ((rear + 1) % MAX_QUEUE == front)
			exit(-1);
		rear = (rear + 1) % MAX_QUEUE;
		//cout << e->data;
		elem[rear] = e;
	}
	/************************************************************************/
	/*     出队
	 */
	/************************************************************************/
	QueueElemType DeQueue() {
		if (QueueEmpty())
			exit(-1);
		front = (front + 1) % MAX_QUEUE;
//		if (elem[front] != NULL) {
//			cout << elem[front]->data;
//		}

		return elem[front];
	}
	/************************************************************************/
	/*    获取队头元素内容
	 */
	/************************************************************************/

	QueueElemType GetFront() {
		if (QueueEmpty())
			exit(-1);
		return elem[(front + 1) % MAX_QUEUE];
	}
	/************************************************************************/
	/*    判断队列Q是否为空
	 */
	/************************************************************************/
	int QueueEmpty() {
		if (front == rear)
			return 1;
		else
			return 0;
	}

};

#endif /* MYTREE_H_ */
