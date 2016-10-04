/*
 * MySort.cpp
 *
 *  Created on: 2016年9月20日
 *      Author: Administrator
 */
#include "MySort.h"
//二路一次归并过程的算法
//low为本次二路归并排序的第1有序区的第1个元素，i指向第1个元素, mid为第1有序区的最后1个元素
void merge1(int *list, int low, int mid, int high) {
	int i = low;
	int j = mid + 1;
	int *temp = (int *) malloc(sizeof(int) * (high - low + 1));
	if (!temp) {
		exit(-1);
	}
	int k = 0;
	while (i <= mid && j <= high) {
		if (list[i] <= list[j]) {
			temp[k++] = list[i++];
		} else {
			temp[k++] = list[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = list[i++];
	}
	while (j <= high) {
		temp[k++] = list[j++];
	}
	for (i = low, k = 0; i <= high; i++, k++) {
		list[i] = temp[k];
	}
	free(temp);
}
//递归实现二路归并
void mergeSort1(int *list, int low, int high) {
	//二路归并排序，分为两路
	int mid = (low + high) / 2;
	if (low < high) {
		mergeSort1(list, low, mid);
		mergeSort1(list, mid + 1, high);
		merge1(list, low, mid, high);
	}
}
void mergeSortTest1() {
	int list[] = { 25, 64, 12, 89, 41, 29, 30 };
	int n = sizeof(list) / sizeof(int);
	cout << n << endl;
	mergeSort1(list, 0, n - 1);
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << list[i] << "\t";
	}
}
//非递归方式实现二路归并排序 length代表数组长度
void mergeSort2(int *list, int length) {
	int size = 1;
	int low, mid, high;
	//size 用来标识小区间的大小，1,2,4.。。。
	while (size <= length - 1) {
		low = 0;
		while (low + size <= length - 1) {
			mid = low + size - 1;
			high = mid + size;
			if (high > length - 1) {
				high = length - 1;
			}
			merge1(list, low, mid, high);
			cout << "low: " << low << "mid: " << mid << "high: " << high
					<< endl;
			low = high + 1;
		}
		size *= 2;
	}
}
void mergeSortTest2() {
	int list[] = { 25, 64, 12, 89, 41, 29, 30 };
	int n = sizeof(list) / sizeof(int);
	cout << n << endl;
	mergeSort2(list, n);
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << list[i] << "\t";
	}
}
/******************直接插入排序************************/
void PrintDirectInsertSort(int a[], int n, int i) {
	cout << i << ":";
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}

void DirectInsertSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) { //找到小数
			int j = i - 1;
			int x = a[i]; //复制为哨兵，即存储待排序元素
			a[i] = a[i - 1]; //大数后移一次
			while (x < a[j] && j > -1) {
				a[j + 1] = a[j]; //找到小数应该在的位置
				j--;
			}
			a[j + 1] = x; //插入小数
		}
		PrintDirectInsertSort(a, n, i);
	}
}
void DirectInsertSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
	DirectInsertSort(a, n);
	PrintDirectInsertSort(a, n, n);
}
/******************二分插入排序************************/
void PrintBinaryInsertSort(int a[], int n, int i) {
	cout << i << ":";
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}

void BinaryInsertSort(int a[], int n) {
	//刚开始设有序序列只有一个元素 a[0],无序序列为[1...n]了
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) { //找到小数
			//当无序序列元素比有序序列最后一个元素小时，利用二分查找法在有序序列中查找插入位置
			int low = 0;
			int high = i - 1;
			int mid = 0;
			int x = a[i]; //复制为哨兵，即存储待排序元素

			while (low <= high) {
				mid = (low + high) / 2;
				if (x >= a[mid]) {
					low = mid + 1;
				} else {
					high = mid - 1;
				}
			}
			//low位置就是要插入的位置,所以low到i之间的元素都需要往后移动一个位置
			int j = i;
			while (j > low) {
				a[j] = a[j - 1];
				j--;
			}
			a[low] = x;
		}
		PrintDirectInsertSort(a, n, i);
	}
}
void BinaryInsertSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
	BinaryInsertSort(a, n);
	PrintBinaryInsertSort(a, n, n);
}
/******************二路插入排序************************/
void PrintTwoInsertSort(int a[], int n, int i) {
	cout << i << ":";
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}

void TwoInsertSort(int a[], int n) {
	int first = 0, final = 0;
	int k = 0;
	int *temp = (int *) malloc(sizeof(int) * n);
	temp[0] = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] < temp[first]) { // 待插入元素比最小的元素小
			first = (first - 1 + n) % n;
			temp[first] = a[i];
		} else if (a[i] > temp[final]) { // 待插入元素比最大元素大
			final = (final + 1 + n) % n;
			temp[final] = a[i];
		} else { // 插入元素比最小大，比最大小
			k = (final + 1 + n) % n;
			while (temp[(k - 1 + n) % n] > a[i]) {
				temp[(k + n) % n] = temp[((k - 1 + n) % n)];
				k = (k - 1 + n) % n;
			}
			temp[(k + n) % n] = a[i];
			final = (final + 1 + n) % n;
		}
		PrintTwoInsertSort(temp, n, i);
	}
	for (k = 0; k < n; k++) {
		a[k] = temp[(first + k) % n];
	}
	free(temp);
}
void TwoInsertSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
	TwoInsertSort(a, n);
	PrintTwoInsertSort(a, n, n);
}
/******************希尔排序（缩小增量排序）************************/
void PrintShellInsertSort(int a[], int n, int i) {
	cout << i << ":";
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}

void ShellInsertSort(int a[], int n, int dk) {
	for (int i = dk; i < n; i++) {
		if (a[i] < a[i - dk]) {
			int j = i - dk;
			int x = a[i];
			a[i] = a[j];
			while (x < a[j]) {
				a[j + dk] = a[j];
				j -= dk;
			}
			a[j + dk] = x;
		}
		PrintShellInsertSort(a, n, i);
	}
}
void ShellSort(int a[], int n) {
	int dk = n / 2;
	while (dk >= 1) {
		ShellInsertSort(a, n, dk);
		dk /= 2;
	}
}
void ShellInsertSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
	ShellSort(a, n);
	PrintShellInsertSort(a, n, n);
}
/******************选择排序************************/
void PrintSelectSort(int a[], int n, int i) {
	cout << i << ":";
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}

void SelectSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] > a[j]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
		PrintSelectSort(a, n, i);
	}
}
void SelectTwoSort(int a[], int n) {
	for (int i = 0; i < n / 2; i++) {
		int min = i, max = i;
		for (int j = i + 1; j < n - i; j++) {
			if (a[j] >= a[max]) {
				max = j;
				continue;
			}
			if (a[j] < a[min]) {
				min = j;
			}
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		temp = a[n - i - 1];
		a[n - i - 1] = a[max];
		a[max] = temp;
		PrintSelectSort(a, n, i);
	}
}
void SelectSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
//	SelectSort(a, n);
//	PrintSelectSort(a, n, n);
//	cout << endl << endl;
	SelectTwoSort(a, n);
	PrintSelectSort(a, n, n);
}
/******************堆排序************************/
void PrintHeapSort(int a[], int n) {
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}
void HeapAdjust(int a[], int parent, int length) {
	int temp = a[parent]; //保存当前父节点
	int child = 2 * parent + 1; //获取左孩子
	while (child < length) {
		/*****大顶堆*******
		 //如果有有孩子，且右孩子大于做孩子，选取右孩子节点
		 if (child + 1 < length && a[child] < a[child + 1]) {
		 child++;
		 }
		 // 如果父结点的值已经大于孩子结点的值，则直接结束
		 if (a[parent] >= a[child]) {
		 break;
		 }*/
		/*****小顶堆********/
		//如果有有孩子，且右孩子小于做孩子，选取右孩子节点
		if (child + 1 < length && a[child] > a[child + 1]) {
			child++;
		}
		// 如果父结点的值已经小于孩子结点的值，则直接结束
		if (a[parent] < a[child]) {
			break;
		}
		// 把孩子结点的值赋给父结点
		a[parent] = a[child];
		// 选取孩子结点的左孩子结点,继续向下筛选
		parent = child;
		child = 2 * child + 1;
		a[parent] = temp;
	}
	//PrintHeapSort(a, length);
}
/** 
 * 初始堆进行调整
 * 将H[0..length-1]建成堆
 * 调整完之后第一个元素是序列的最小的元素
 */
void BuildHeap(int a[], int length) {
	for (int i = (length - 1) / 2; i >= 0; --i) {
		HeapAdjust(a, i, length);
	}
}
void HeapSort(int a[], int length) {
	BuildHeap(a, length);
	PrintHeapSort(a, length);
	for (int i = length - 1; i > 0; i--) { //大顶堆时，顺序；小顶堆时，逆序
		int temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		HeapAdjust(a, 0, i);
		PrintHeapSort(a, length);
	}
}
void HeapSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
	HeapSort(a, n);
	PrintHeapSort(a, n);
}
/******************冒泡排序************************/
void PrintBubbleSort(int a[], int n, int i) {
	cout << i << ":";
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\t";
	}
	cout << endl;
}
void BubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
		PrintBubbleSort(a, n, i);
	}
}
//设置一标志性变量pos,用于记录每趟排序中最后一次进行交换的位置。
//由于pos位置之后的记录均已交换到位,故在进行下一趟排序时只要扫描到pos位置即可
void BubbleSort1(int a[], int n) {
	int i = n - 1;
	while (i > 0) {
		int pos = 0;
		for (int j = 0; j < i; j++) {
			if (a[j] > a[j + 1]) {
				pos = j;
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
		i = pos;
		PrintBubbleSort(a, n, i);
	}
}
void BubbleSort2(int a[], int n) {
	int low = 0;
	int high = n - 1;
	int j, temp;
	while (low < high) {
		for (j = low; j < high; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
		--high;
		for (j = high; j > low; --j) {
			if (a[j] < a[j - 1]) {
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
		++low;
		PrintBubbleSort(a, n, n);
	}
}
void BubbleSortTest() {
	int a[] = { 3, 2, 1, 5, 8, 9, 4, 3, 11, 10 };
	int n = sizeof(a) / sizeof(int);
	//BubbleSort(a, n);
	//BubbleSort1(a, n);
	BubbleSort2(a, n);
	PrintBubbleSort(a, n, n);
}
