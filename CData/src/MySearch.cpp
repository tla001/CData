/*
 * MyFound.cpp
 *
 *  Created on: 2016年10月14日
 *      Author: Administrator
 */
#include "MySearch.h"
/*
 * 顺序查找
 * 平均查找长度：（n+1）/2
 * 算法复杂度：o（n）
 * ret:first position
 */
int OrderSearch(int *a, int length, int dest) {
	for (int i = 0; i < length; i++) {
		if (a[i] == dest) {
			return i;
		}
	}
	return -1;
}
void OrderSearchTest() {
	int a[] = { 3, 5, 2, 12, 7, 9, 4 };
	int length = sizeof(a) / sizeof(a[0]);
	int dest = 12;
	int pos = -2;
	pos = OrderSearch(a, length, dest);
	printf("pos= %d\n", pos);
}
/*
 * 二分查找
 * 最多查找长度：log（n+1）/log（2）
 * 算法复杂度：O(log2n)
 * ret:position
 */
void printArr(int *a, int length) {
	for (int i = 0; i < length; i++) {
		cout << a[i] << "\t";
	}
	cout << endl;
}
int BinarySearch(int *a, int length, int dest) {
	int low = 0;
	int high = length - 1;
	int mid;
	while (low <= high) {
		mid = low + (high - low) / 2;
		if (a[mid] == dest) {
			return mid;
		} else if (a[mid] > dest) {
			high = mid - 1;
		} else if (a[mid] < dest) {
			low = mid + 1;
		}
	}
	return -1;
}
void BinarySearchTest() {
	int a[] = { 3, 5, 2, 12, 7, 9, 4 };
	int length = sizeof(a) / sizeof(a[0]);
	int dest = 3;
	int pos = -2;
	QuickSort(a, 0, length - 1);
	printArr(a, length);
	pos = BinarySearch(a, length, dest);
	printf("pos= %d\n", pos);
}
/*
 * 哈希表
 */
//哈希表
HashHeadPtr hashTable[HASHTABLEMAX];

/*
 * 哈希表散列计算函数
 * 通过id计算哈希表的位置
 */
HashIdType HashFunc(HashIdType id) {
	HashIdType pos = 0;
	pos = id % HASHTABLEMAX;
	return pos;
}
/*
 * 链表初始化
 */
HLinkNodePtr initHLinkNode() {
	HLinkNodePtr node = (HLinkNodePtr) malloc(sizeof(HLinkNode));
	return node;
}
/*
 * hash table head init
 */
HashHeadPtr initHashHeadNode() {
	HashHeadPtr node = (HashHeadPtr) malloc(sizeof(HashHead));
	node->next = NULL;
	return node;
}
/*
 * hash table init
 */
void initHashTable(HashHeadPtr hashTable[]) {
	int i = 0;
	for (i = 0; i < HASHTABLEMAX; i++) {
		hashTable[i] = initHashHeadNode();
		hashTable[i]->next = NULL;
	}
}
void insertLinkNode(HashHeadPtr hashTable[], HLinkNodePtr newnode) {
	HLinkNodePtr node;
	HashIdType pos = 0;
	newnode->next = NULL;
	pos = HashFunc(newnode->id);
	//printf("newnode id = %d\n", newnode->id);
	if (hashTable[pos]->next == NULL) { //hashtable head is null
		hashTable[pos]->next = newnode;
	} else {
		node = hashTable[pos]->next;
		while (node->next != NULL) {
			node = node->next;
		}
		node->next = newnode;
	}
}
/*
 * 搜索节点
 * root返回节点信息,norm 返回上一节点信息
 * root是根节点标志 1 yes 0 no
 */
HLinkNodePtr searchLinkNode(HashHeadPtr hashTable[], HashIdType id, int *root) {
	HLinkNodePtr node;
	HashIdType pos = 0;
	pos = HashFunc(id);
	node = hashTable[pos]->next;
	if (node == NULL) {
		return NULL;
	}
	if (node->id == id) {
		*root = 1;
		return node;
	} else {
		*root = 0;
		while (node->next != NULL) {
			if (node->next->id == id) { // caution
				return node;
			} else {
				node = node->next;
			}
		}
	}
	return NULL;
}
/*
 * hash table delete normal node
 */
void deleteLinkNode(HashHeadPtr hashTable[], HLinkNodePtr node) {
	HLinkNodePtr dnode;
	dnode = node->next;
	node->next = dnode->next;

	free(dnode);
	dnode = NULL;
}
/*
 * hash table delete head node
 */
void deleteHLinkNode(HashHeadPtr hashTable[], HLinkNodePtr node) {
	HashIdType pos = 0;
	pos = HashFunc(node->id);
	if (node != NULL) {
		hashTable[pos]->next = node->next;
		free(node);
		node = NULL;
	}
}
/*
 * get node num
 */
int getNodeNum(HashHeadPtr hashTable[]) {
	HLinkNodePtr node;
	int num = 0;
	for (int i = 0; i < HASHTABLEMAX; i++) {
		node = hashTable[i]->next;
		while (node != NULL) {
			num++;
			node = node->next;
		}
	}
	return num;
}
/*
 * get node from index
 */
HLinkNodePtr getNodeFromIndex(HashHeadPtr hashTable[], int index, int *root) {
	HLinkNodePtr node;
	int num = 0;
	for (int i = 0; i < HASHTABLEMAX; i++) {
		node = hashTable[i]->next;
		if (node == NULL) {
			continue;
		}
		num++;
		if (num == index) {
			*root = 1;
			return node;
		}
		while (node->next != NULL) {
			num++;
			if (num == index) {
				*root = 0;
				return node;
			}
			node = node->next;
		}
	}
	return NULL;
}
/*
 * delete hash table
 */
void dropHash(HashHeadPtr hashTable[]) {
	HLinkNodePtr node;
	HLinkNodePtr nodeNext;

	for (int i = 0; i < HASHTABLEMAX; i++) {
		node = hashTable[i]->next;
		while (1) {
			if (node == NULL) {
				hashTable[i]->next = NULL;
				break;
			}
			nodeNext = node->next;
			free(node);
			node = nodeNext;
		}
	}
}
/*
 * print hash table
 */
void printHash(HashHeadPtr hashTable[]) {
	HLinkNodePtr node;
	int root;
	int num;
	printf("--------------Print Hash Table------------------\n");
	num = getNodeNum(hashTable);
	for (int i = 1; i <= num; i++) {
		node = getNodeFromIndex(hashTable, i, &root);
		if (node != NULL) {
			if (root) {
				printf("root:id %d,data %d\n", node->id, node->data);
			} else {
				printf("norm:id %d,data %d\n", node->next->id,
						node->next->data);
			}
		}
	}
}
void hashTableTest() {
	HLinkNodePtr node;
	int root;

	initHashTable(hashTable);

//	node = initHLinkNode();
//	node->id = 10;
//	node->data = 200;
//	insertLinkNode(hashTable, node);
//	printf("node nums= %d\n", getNodeNum(hashTable));

	for (int i = 0; i < 5; i++) {
		node = initHLinkNode();
		node->id = i * 10;
		node->data = i;
		insertLinkNode(hashTable, node);
	}
	for (int i = 0; i < 5; i++) {
		node = initHLinkNode();
		node->id = i * 10 + HASHTABLEMAX;
		node->data = i;
		insertLinkNode(hashTable, node);
	}
	printf("node nums= %d\n", getNodeNum(hashTable));
//	node = searchLinkNode(hashTable, 10, &root);
//	if (node != NULL) {
//		if (root) {
//			printf("root:id %d,data %d\n", node->id, node->data);
//			deleteHLinkNode(hashTable, node);
//		} else {
//			printf("norm:id %d,data %d\n", node->id, node->data);
//			deleteLinkNode(hashTable, node);
//		}
//	}
//	printf("node nums= %d\n", getNodeNum(hashTable));
	node = searchLinkNode(hashTable, 110, &root);
	if (node != NULL) {
		if (root) {
			printf("root:id %d,data %d\n", node->id, node->data);
			deleteHLinkNode(hashTable, node);
		} else {
			printf("norm:id %d,data %d\n", node->next->id, node->next->data);
			deleteLinkNode(hashTable, node);
		}
	}
	printf("node nums= %d\n", getNodeNum(hashTable));

	printHash(hashTable);
}
