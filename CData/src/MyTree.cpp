/*
 * MyTree.cpp
 *
 *  Created on: 2016Äê9ÔÂ12ÈÕ
 *      Author: Administrator
 */

#include "MyTree.h"

Status CreateBitTree(BitTree &T) {
	char data;
	cin >> data;
	//cout<<data;
	if ('$' == data)
		T = NULL;
	else {
		T = (BitTree) malloc(sizeof(BitNode));
		T->data = data;
		CreateBitTree(T->lchild);
		CreateBitTree(T->rchild);
	}
	return 0;
}
void PreOrderTraverseFor(BitTree T) {
	if (T) {
		Visit(T);
		PreOrderTraverseFor(T->lchild);
		PreOrderTraverseFor(T->rchild);
	}
}
void InOrderTraverseFor(BitTree T) {
	if (T) {
		InOrderTraverseFor(T->lchild);
		Visit(T);
		InOrderTraverseFor(T->rchild);
	}
}
void PostOrderTraverseFor(BitTree T) {
	if (T) {
		PostOrderTraverseFor(T->lchild);
		PostOrderTraverseFor(T->rchild);
		Visit(T);
	}
}
Status PreOrderTraverse(BitTree T) {
	BitTree root;
	stack s;
	s.inItStack();
	root = T;
	while (root || !s.isEmpty()) {
		if (root) {
			Visit(root);
			s.push(root);
			root = root->lchild;
		} else {
			root = s.getTop();
			s.pop();
			root = root->rchild;
		}
	}
	return 0;
}
Status InOrderTraverse(BitTree T) {
	BitTree root;
	stack s;
	s.inItStack();
	root = T;
	while (root || !s.isEmpty()) {
		while (root) {
			s.push(root);
			root = root->lchild;
		}
		if (!s.isEmpty()) {
			root = s.getTop();
			s.pop();
			Visit(root);
			root = root->rchild;
		}
	}
	return 0;
}
Status PostOrderTraverse(BitTree T) {
	BitTree root;
	stack s;
	s.inItStack();
	root = T;
	while (root || !s.isEmpty()) {
		while (root) {
			s.push(root);
			s.SetTag(0);
			root = root->lchild;
		}
		if (s.GetTag() == 0) {
			root = s.getTop();
			s.SetTag(1);
			root = root->rchild;
		} else {
			while (s.GetTag() == 1) {
				root = s.getTop();
				s.pop();
				Visit(root);
			}
			root = NULL;
		}
	}
	return 0;
}

void LevelOrderTraverse(BitTree T) {
	BitTree root, TNode;
	queue q;
	q.InitQueue();
	root = T;
	if (!root)
		exit(-1);
	q.EnQueue(root);
	while (!q.QueueEmpty()) {
		TNode = (BitTree) q.DeQueue();
		Visit(TNode);
		if (TNode->lchild)
			q.EnQueue(TNode->lchild);
		if (TNode->rchild)
			q.EnQueue(TNode->rchild);
	}
}
Status Visit(BitTree &T) {
	if (T->data) {
		cout << T->data << "\t";
		return 0;
	}
	return -1;
}
void BitTreeTest() {
	BitTree T;
	cout << "- + a * b - c d / e f\n";
	CreateBitTree(T);
	cout << "Create done" << endl;
	cout << "PreFor:\t\t";
	PreOrderTraverseFor(T);
	cout << endl;
	cout << "InFor:\t\t";
	InOrderTraverseFor(T);
	cout << endl;
	cout << "PosFor:\t\t";
	PostOrderTraverseFor(T);
	cout << endl;
	cout << "Pre:\t\t";
	PreOrderTraverse(T);
	cout << endl;
	cout << "Lev:\t\t";
	LevelOrderTraverse(T);
	cout << endl;
	cout << "In:\t\t";
	InOrderTraverse(T);
	cout << endl;
	cout << "Post:\t\t";
	PostOrderTraverse(T);
}
