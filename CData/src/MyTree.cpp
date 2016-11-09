/*
 * MyTree.cpp
 *
 *  Created on: 2016��9��12��
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
#include <stdio.h>
#include<string.h>
#include <math.h>
int InitBiTree(BitTree &T) {
	T = (BitTree) malloc(sizeof(BitNode));
	if (!T) {
		return 0;
	} else {
		T->data = NULL;
		T->lchild = NULL;
		T->rchild = NULL;
		return 1;
	}
}
//���򹹽����Ƕ��з�ʽ
Status CreateBitTree1(BitTree &T, char *str) {
	BitTree m, q;
	q = T;
	int length, i, j;
	length = strlen(str);
	cout << "length=" << length << endl;

	if (length < 1 && length > 31)
		return -1;
	q->data = str[0];

	for (i = 2; i <= length; i++) {
		m = (BitTree) malloc(sizeof(BitNode));
		m->data = str[i - 1];
		m->lchild = NULL;
		m->rchild = NULL;

		for (j = 1; j < (int) floor(log10(i) / log10(2)); j++) //log2(i)ΪҪ��ӽڵ����һ��
				{
			if (((int) floor(i / pow(2, (int) (log10(i) / log10(2)) - j))) % 2
					== 0) //0Ϊ����
					{
				if (q->lchild == NULL) {
					printf("�������,��%d���ڵ��޸��ڵ�\n", i);
					free(m);
					return 0;
				}
				q = q->lchild;
			}

			else {
				if (q->rchild == NULL) {
					printf("������󣬵�%d���ڵ��޸��ڵ�\n", i);
					free(m);
					return 0;
				}
				q = q->rchild;
			}
		}

		//�ж����Һ���
		if (i % 2 == 0) {
			q->lchild = m;
			printf("�����%c\n", m->data);
		} else {
			q->rchild = m;
			printf("�Ҳ���%c\n", m->data);
		}
		q = T;
	}
	return 0;
}
//���򹹽������з�ʽ
Status CreateBitTree2(BitTree &T, char *str) {
	int length = strlen(str);
	int i = 1;
	BitTree root, temp;
	queue q;
	q.InitQueue();
	//���ڵ�
	InitBiTree(root);
	root->data = str[0];
	q.EnQueue(root);
	T = root;

	while (!q.QueueEmpty()) {
		temp = q.DeQueue();
		if (i <= length && str[i] != '\0') {
			InitBiTree(root);
			root->data = str[i];
			q.EnQueue(root);
			temp->lchild = root;
		}
		i++;
		if (i <= length && str[i] != '\0') {
			InitBiTree(root);
			root->data = str[i];
			q.EnQueue(root);
			temp->rchild = root;
		}
		i++;
	}
	return 0;
}
void BitTreeTest1() {
	BitTree T, T1;
	char str[] = "ABCDEFGHIJKL";
	InitBiTree(T);
	CreateBitTree1(T, str);
	//PreOrderTraverseFor(T);
	//cout << endl;
	LevelOrderTraverse(T);
	cout << endl;
	InitBiTree(T1);
	CreateBitTree2(T1, str);
	LevelOrderTraverse(T1);
}
//��֪�������������
void CreateBitTree3(BitTree &T, char *preOder, char *midOder, int length) {
	if (length == 0) {
		T = NULL;
		return;
	}
	BitTree root;
	root = (BitTree) malloc(sizeof(BitNode));
	root->data = *preOder;
	T = root;

//	char *rootpos = strchr(midOder, root->data);
//	if (rootpos == NULL) {
//		cout << "input wrong order sample" << endl;
//	}
//	int lTreeLength = strlen(midOder) - strlen(rootpos);
//	int rTreeLength = length - lTreeLength - 1;
//
//	CreateBitTree3(root->lchild, preOder + 1, midOder, lTreeLength);
//	CreateBitTree3(root->rchild, preOder + lTreeLength + 1, rootpos + 1,
//			rTreeLength);
	int rootIndex = 0;
	for (; rootIndex < length; rootIndex++) {
		if (midOder[rootIndex] == *preOder)
			break;
	}
	CreateBitTree3(root->lchild, preOder + 1, midOder, rootIndex);
	CreateBitTree3(root->rchild, preOder + rootIndex + 1,
			midOder + rootIndex + 1, length - rootIndex - 1);
}
void BitTreeTest3() {
	BitTree T;
	char pre[] = "abdeijcfg";
	char mid[] = "dbiejafcg";
	CreateBitTree3(T, pre, mid, strlen(pre));
	PreOrderTraverseFor(T);
	cout << endl;
	PostOrderTraverseFor(T);
}
//��֪���򡢺���������
void CreateBitTree4(BitTree &T, char *midOder, char *postOder, int length) {
	if (length == 0) {
		T = NULL;
		return;
	}
	BitTree root;
	root = (BitTree) malloc(sizeof(BitNode));
	root->data = *(postOder + length - 1);
	T = root;

	int rootIndex = 0;
	for (; rootIndex < length; rootIndex++) {
		if (midOder[rootIndex] == *(postOder + length - 1))
			break;
	}
	CreateBitTree4(root->lchild, midOder, postOder, rootIndex);
	CreateBitTree4(root->rchild, midOder + rootIndex + 1, postOder + rootIndex,
			length - rootIndex - 1);

}
void BitTreeTest4() {
	BitTree T;
	char mid[] = "dbgeafc";
	char post[] = "dgebfca";
	CreateBitTree4(T, mid, post, strlen(mid));
	PreOrderTraverseFor(T);
	cout << endl;
	PostOrderTraverseFor(T);
}
//���������񣬵ݹ�ʵ��
void MirrorBitTree(BitTree &T) {
	if (NULL == T)
		return;
	if (NULL != T->lchild || NULL != T->rchild) {
		BitTree temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}

	if (T->lchild)
		MirrorBitTree(T->lchild);
	if (T->rchild)
		MirrorBitTree(T->rchild);
}
//���������񣬷ǵݹ�ʵ��
void MirrorBitTree1(BitTree &T) {
	if (NULL == T)
		return;
	stack s;
	s.inItStack();
	s.push(T);

	while (!s.isEmpty()) {
		BitTree root = s.getTop();
		s.pop();
		if (NULL != root->lchild || NULL != root->rchild) {
			BitTree temp = root->lchild;
			root->lchild = root->rchild;
			root->rchild = temp;
		}
		if (NULL != root->lchild)
			s.push(root->lchild);
		if (NULL != root->rchild)
			s.push(root->rchild);
	}
}

void BitTreeTest5() {
	BitTree T;
	char str[] = "ABCDEFGHIJKL";
	InitBiTree(T);
	CreateBitTree1(T, str);
	LevelOrderTraverse(T);
	cout << endl;
	MirrorBitTree(T);
	LevelOrderTraverse(T);
	cout << endl;
	MirrorBitTree1(T);
	LevelOrderTraverse(T);
	cout << endl;
}
/***************����������*********************************/
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
//�ݹ������С
BitTree BstFindMin(BitTree T) {
	if (!T)
		return NULL;
	else if (!T->lchild)
		return T;
	else
		return BstFindMin(T->lchild);
}
//�����������
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
//	BstInsert(T, '4');
//	BstInsert(T, '2');
//	BstInsert(T, '3');
//	BstInsert(T, '3');
//	BstInsert(T, '5');
//	BstInsert(T, '6');
//	BstInsert(T, '1');
	BstInsert(T, '7');
	BstInsert(T, '2');
	BstInsert(T, '4');
	BstInsert(T, '6');
	BstInsert(T, '3');
	BstInsert(T, '1');
	BstInsert(T, '5');
	InOrderTraverseFor(T);
	cout << endl;
	//BstDelete(T, '2');
	PreOrderTraverseFor(T);
	cout << endl;
	PostOrderTraverseFor(T);
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
	case EH: /*ԭ�����������ȸߣ�������������ʹ������*/
		T->bf = LH;    //�����EH����û��д�ı�Ҫ
		*taller = true;
		break;
	case RH: /*�½�����*T ���ӵ��������ϣ������������˫������*/
		lr = L->rchild; /*Lr ָ��*p ���ӵ������������*/
		switch (lr->bf) /*����*T ������������ƽ������*/
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
		L_Rotate(L); /*��*T ��������������ת����*/
		R_Rotate(T); /*��*T ������ת����*/
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
/*����*T ָ��Ľ��Ϊ�������������ҵ���ת��������֮��*T ָ��Ľ��Ϊ�������¸�*/
void R_Rotate(AVLTree &T) {
	AVLTree L = T->lchild; /*L ָ��*T �����������*/
	T->lchild = L->rchild; /*L ���������ҽ�*T ��������*/
	L->rchild = T;
	T = L; /* *L ָ���µĸ����*/
}

/*����*p ָ��Ľ��Ϊ����������������ת��������֮��*p ָ��Ľ��Ϊ�������¸�*/
void L_Rotate(AVLTree &T) {
	AVLTree Lr = T->rchild; /*Lr ָ��*T �����������*/
	T->rchild = Lr->lchild; /*L ���������ҽ�*p ��������*/
	Lr->lchild = T;
	T = Lr; /* *L ָ���µĸ����*/
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
