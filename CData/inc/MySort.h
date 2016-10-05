/*
 * MySort.h
 *
 *  Created on: 2016Äê9ÔÂ20ÈÕ
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
void QuickSortTest();
void RadixSortTest();

#endif /* INC_MYSORT_H_ */
