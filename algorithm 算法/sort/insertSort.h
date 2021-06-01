#pragma once

#include<iostream>

int* insertSort(int* arr,int begin,int size) {
	int k;
	int value;
	for (; begin < size; begin++) {
		k = begin;
		value = arr[k];
		while (k != 0 && value < arr[k - 1]) {
			arr[k] = arr[k - 1];
			k--;
		}
		arr[k] = value;

	};
	return arr;

}
