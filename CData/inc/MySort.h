/*
 * MySort.h
 *
 *  Created on: 2016��9��20��
 *      Author: Administrator
 */

#ifndef INC_MYSORT_H_
#define INC_MYSORT_H_

#include "Include.h"

void merge1(int *list, int low, int mid, int high);
void mergeSort1(int *list, int low, int high);
void mergeSortTest1();
void mergeSort2(int *list, int length);
void mergeSortTest2();

void DirectInsertSortTest();
void BinaryInsertSortTest();
void TwoInsertSortTest();

void ShellInsertSortTest();
void SelectSortTest();
void HeapSortTest();
void BubbleSortTest();
void QuickSort(int a[], int left, int right);
void QuickSortTest();
void RadixSortTest();

void OutSortTest();

#endif /* INC_MYSORT_H_ */
