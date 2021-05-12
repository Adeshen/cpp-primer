#pragma once
#include<iostream>

int maxElement(int* a, int begin, int end) {
	if (end - begin == 1)  return a[begin];
	int mid = (begin + end) / 2;
	return maxElement(a, begin, mid) > maxElement(a, mid, end) ? maxElement(a, begin, mid) : maxElement(a, mid, end);
}

int MaxElement(int* a, int size) {
	if (size == 0) {
		printf("这并非是一个数组");
		exit(1);
	}
	return maxElement( a, 0, size - 1);
}

/*以上是递归求最大值*/
/*above is recursion to find max */

int linarMax(int* arr, int size) {
	int max = arr[0];
	for (int i = 1; i < size; i++) {
		max = max > arr[i] ? max : arr[i];
	}
	return max;
}
/*以上是线性扫描求最大值*/
/*above is linar finding to get max*/
