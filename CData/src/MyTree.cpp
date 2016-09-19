/*
 * MyTree.cpp
 *
 *  Created on: 2016年9月12日
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
int TreeHeight(BitTree T) {
	int h, left, right;
	if (!T) {
		return 0;
	}
	left = TreeHeight(T->lchild);
	right = TreeHeight(T->rchild);
	h = (left > right ? left : right) + 1;
	return h;
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
/***************二叉搜索树*********************************/
BitTree BstFind(BitTree T, TElemType e) {
//	if (!T)
//		return NULL;
//	if (e > T->data)
//		return BstFind(T->rchild, e);
//	else if (e < T->data)
//		return BstFind(T->lchild, e);
//	else
//		return T;
	while (T) {
		if (e > T->data)
			T = T->rchild;
		else if (e < T->data)
			T = T->lchild;
		else
			return T;
	}
	return NULL;
}
//递归查找最小
BitTree BstFindMin(BitTree T) {
	if (!T)
		return NULL;
	else if (!T->lchild)
		return T;
	else
		return BstFindMin(T->lchild);
}
//迭代查找最大
BitTree BstFindMax(BitTree T) {
	if (T) {
		while (T->rchild)
			T = T->rchild;
		return T;
	} else
		return NULL;
}
BitTree BstInsert(BitTree &T, TElemType e) {
	if (!T) {
		T = (BitTree) malloc(sizeof(BitNode));
		T->data = e;
		T->lchild = NULL;
		T->rchild = NULL;
	} else {
		if (e > T->data)
			BstInsert(T->rchild, e);
		else if (e < T->data)
			BstInsert(T->lchild, e);
		else
			return NULL;
	}
	return T;
}
BitTree BstDelete(BitTree T, TElemType e) {
	BitTree tmp;
	if (!T)
		cout << "tree is null" << endl;
	else if (e < T->data)
		T->lchild = BstDelete(T->lchild, e);
	else if (e > T->data)
		T->rchild = BstDelete(T->rchild, e);
	else {
		if (T->lchild && T->rchild) {
			tmp = BstFindMin(T->rchild);
			T->data = tmp->data;
			T->rchild = BstDelete(T->rchild, T->data);
			//free(tmp);
		} else {
			//tmp = T;
			if (!T->lchild && T->rchild)
				T = T->rchild;
			else if (!T->rchild && T->lchild)
				T = T->lchild;
			else
				T = NULL;
			//free(tmp);
		}
	}
}
void BstTest() {
	BitTree T = NULL, pos;
	BstInsert(T, '4');
	BstInsert(T, '2');
	BstInsert(T, '3');
	BstInsert(T, '3');
	BstInsert(T, '5');
	BstInsert(T, '6');
	BstInsert(T, '1');

	PreOrderTraverseFor(T);
	cout << endl;
	BstDelete(T, '2');
	PreOrderTraverseFor(T);
	cout << endl;
	pos = BstFindMin(T);
	cout << "min: " << pos->data << endl;
	pos = BstFindMax(T);
	cout << "max: " << pos->data << endl;
}
/*************************************************/
bool *taller = (bool*) malloc(sizeof(bool));
int AVLInsert(AVLTree &T, TElemType e, bool *taller) {
	if (!T) {
		T = (AVLTree) malloc(sizeof(AVLNode));
		T->data = e;
		T->bf = EH;
		T->lchild = T->rchild = NULL;
		*taller = true;
	} else {
		if (e == T->data) {
			*taller = false;
			return 0;
		}
		if (e < T->data) {
			if (!AVLInsert(T->lchild, e, taller))
				return 0;
			if (*taller) {
				switch (T->bf) {
				case EH:
					T->bf = LH;
					*taller = true;
					break;
				case LH:
					AVLLeftBalance(T);
					*taller = false;
					break;
				case RH:
					T->bf = EH;
					*taller = false;
					break;
				}
			}
		} else {
			if (!AVLInsert(T->rchild, e, taller))
				return 0;
			if (*taller) {
				switch (T->bf) {
				case EH:
					T->bf = RH;
					*taller = true;
					break;
				case LH:
					T->bf = EH;
					*taller = false;
					break;
				case RH:
					AVLRightBalance(T);
					*taller = false;
					break;
				}
			}
		}
	}
	return 1;
}
void AVLLeftBalance(AVLTree &T) {
	AVLTree L = T->lchild, lr;
	switch (L->bf) {
	case LH:
		T->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case EH: /*原本左、右子树等高，因左子树增高使树增高*/
		T->bf = LH;    //这里的EH好像没有写的必要
		*taller = true;
		break;
	case RH: /*新结点插在*T 左孩子的右子树上，需作先左后右双旋处理*/
		lr = L->rchild; /*Lr 指向*p 左孩子的右子树根结点*/
		switch (lr->bf) /*修正*T 及其左子树的平衡因子*/
		{
		case LH:
			T->bf = RH;
			L->bf = EH;
			break;
		case EH:
			T->bf = L->bf = EH;
			break;
		case RH:
			T->bf = EH;
			L->bf = LH;
			break;

		}
		lr->bf = EH;
		L_Rotate(L); /*对*T 的左子树作左旋转处理*/
		R_Rotate(T); /*对*T 作右旋转处理*/
	}
}
void AVLRightBalance(AVLTree &T) {
	AVLTree L = T->rchild, lr;
	switch (L->bf) {
	case RH:
		T->bf = L->bf = EH;
		L_Rotate(T);
		break;
	case EH:
		T->bf = RH;
		*taller = true;
		break;
	case LH:
		lr = L->lchild;
		switch (lr->bf) {
		case RH:
			T->bf = LH;
			L->bf = EH;
			break;
		case EH:
			T->bf = L->bf = EH;
			break;
		case LH:
			T->bf = EH;
			L->bf = LH;
			break;

		}
		lr->bf = EH;
		R_Rotate(L);
		L_Rotate(T);
	}
}
/*对以*T 指向的结点为根的子树，作右单旋转处理，处理之后，*T 指向的结点为子树的新根*/
void R_Rotate(AVLTree &T) {
	AVLTree L = T->lchild; /*L 指向*T 左子树根结点*/
	T->lchild = L->rchild; /*L 的右子树挂接*T 的左子树*/
	L->rchild = T;
	T = L; /* *L 指向新的根结点*/
}

/*对以*p 指向的结点为根的子树，作左单旋转处理，处理之后，*p 指向的结点为子树的新根*/
void L_Rotate(AVLTree &T) {
	AVLTree Lr = T->rchild; /*Lr 指向*T 右子树根结点*/
	T->rchild = Lr->lchild; /*L 的左子树挂接*p 的右子树*/
	Lr->lchild = T;
	T = Lr; /* *L 指向新的根结点*/
}
void AVLDelTree(AVLTree &T) {
	if (!T)
		exit(-1);
	AVLDelTree(T->lchild);
	AVLDelTree(T->rchild);
	free(T);
	T = NULL;
}
void AVLPrintTree(AVLTree &T) {
	if (T) {
		AVLPrintTree(T->lchild);
		if (T->data)
			cout << T->data << "\t";
		AVLPrintTree(T->rchild);
	}
}
void AVLTest() {
	AVLTree T = NULL;
	for (int i = 0; i < 10; i++) {
		AVLInsert(T, (char) ('a' + i), taller);
	}
	//AVLPrintTree(T);
	//AVLDelTree(T);
}
