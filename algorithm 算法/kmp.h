#pragma once


#include<iostream>
using namespace std;
#define KMP_MAXSIZE   20

void getNext(int next[], char arr[], int size) {
	
	int Right = 0;
	int Left = -1;
	
	next[0] = -1;

	while (Right < size - 1) {
		if (Left == -1 || arr[Right] == arr[Left]) {
			Right++; Left++;
			next[Right] = Left;
		}
		else {
			Left = next[Left];
		}
	}
}

int KMPIndex(char mainArr[],int mainSize, char sonArr[], int sonSize) {
	int next[KMP_MAXSIZE], mainPoint = 0, sonPoint = 0;

	getNext(next, sonArr, sonSize);
	while (mainPoint < mainSize && sonPoint < sonSize) {
		if (sonPoint == -1 || mainArr[mainPoint] == sonArr[sonPoint]) {
			sonPoint++; mainPoint++;
		}
		else sonPoint = next[sonPoint];       //根据next回退

	}

	if (sonPoint >= sonSize) {
		return (mainPoint - sonSize);
	}
	else {
		return -1;
	}

}
