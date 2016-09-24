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
