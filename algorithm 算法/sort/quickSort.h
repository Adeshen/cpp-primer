#pragma once

#include<iostream>




//快速排序
void quickSort(int s[], int left, int right)
{
	if (left < right)
	{
		int ltemp = left, rtemp = right, x = s[left];
		while (ltemp < rtemp)
		{
			while (ltemp < rtemp && s[rtemp] >= x) // 从右向左找第一个小于x的数
				rtemp--;
			if (ltemp < rtemp)
			{
				
				s[ltemp++] = s[rtemp];   //先赋值再自增
			}

			while (ltemp < rtemp && s[ltemp] < x) // 从左向右找第一个大于等于x的数
				ltemp++;
			if (ltemp < rtemp)
				s[rtemp--] = s[ltemp];
			
		}
		s[ltemp] = x;//此时ltemp=rtemp，正好在中间
		quickSort(s, left, ltemp - +1); // 递归调用 
		quickSort(s, ltemp + 1, right);
	}
}
