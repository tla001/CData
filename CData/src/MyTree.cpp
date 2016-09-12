/*
 * MyTree.cpp
 *
 *  Created on: 2016Äê9ÔÂ12ÈÕ
 *      Author: Administrator
 */

#include "MyTree.h"

Status CreateBitTree(BitTree &T)
{
	char data;
	cin>>data;
	//cout<<data;
	if('$'==data)
		T=NULL;
	else{
		T=(BitTree)malloc(sizeof(BitNode));
		T->data=data;
		CreateBitTree(T->lchild);
		CreateBitTree(T->rchild);
	}
	return 0;
}
Status PreOrderTraverse(BitTree T)
{
	BitTree root;
	stack s;
	s.inItStack();
	root=T;
	while(root || !s.isEmpty()) {
		if(root) {
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
Status InOrderTraverse(BitTree T)
{

	return 0;
}
Status PostOrderTraverse(BitTree T)
{

	return 0;
}
void LevelOrderTraverse(BitTree T)
{
	 BitTree root,TNode;
	    queue q;
	    root = T;
	    if(!root) exit(-1);
	    q.EnQueue(root);
	    while (!q.QueueEmpty())
	    {
	        TNode =(BitTree) q.DeQueue();
	        Visit(TNode);
	        if (TNode->lchild) q.EnQueue(TNode->lchild);
	        if (TNode->rchild) q.EnQueue(TNode->rchild);
	    }
}
Status Visit(BitTree &T)
{
	if(T->data){
		cout<<T->data<<"\t";
		return 0;
	}
	return -1;
}
void BitTreeTest()
{
	int pos =1 ;
	BitTree T;
	cout<<"- + a * b - c d / e f\n";
	CreateBitTree(T);
	//PreOrderTraverse(T);
	LevelOrderTraverse(T);
}
