
#pragma once


#include<iostream>


void bubblingSort(int* arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0 ; j < size - 1 - i; j++) {
			if (arr[j] > arr[j+1]) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}
