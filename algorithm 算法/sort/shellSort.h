/*希尔排序，是利用分组排序的方法进行排序
减半的操作称之为希尔增量,希尔排序的最坏情况将会达到n^2,  如果采用通向公式为2^k-1的{1,3,7,15...}的增量序列，最坏情况将会降至n^(3/2)
*/


#pragma once

#include<iostream>


void shellSort(int* a, int len) {
	int temp;
	int j;
	int x=0;
	for (int r = len / 2; r > 0; r /= 2) {
		for (int i = r; i < len; i++) {
			temp = a[i];    //暂时存放a[i]的数据

			j = i - r;
			while (j >= 0 && temp < a[j]) {
				a[j + r] = a[j];
				j -= r;

			}
			a[j + r] = temp;

		}
		/*x++;
		std::cout << "第" << x << "步排序结果:";
		for (int h = 0; h < len; h++) {
			std::cout << a[h]<<std::endl;
		}        测试代码可以自行取用     */
	}


}
