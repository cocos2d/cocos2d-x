#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

static void cc_qsort_impl(void** array, int left, int right, CCDataCompareFunc cmp)
{
	int save_left  = left;
	int save_right = right;
	void* x = array[left];

	while(left < right)
	{
		while(cmp(array[right], x) >= 0 && left < right) right--;
		if(left != right)
		{
			array[left] = array[right];
			left++;
		}

		while(cmp(array[left], x) <= 0 && left < right)	left++;
		if(left != right)
		{
			array[right] = array[left];
			right--;
		}
	}
	array[left] = x;

	if(save_left < left)
	{
		cc_qsort_impl(array, save_left, left-1, cmp);
	}

	if(save_right > left)
	{
		cc_qsort_impl(array, left+1, save_right, cmp);
	}
}

int cc_qsort(void** array, int nr, CCDataCompareFunc cmp)
{
	if (array == NULL || cmp == NULL)
		return 0;

	if(nr > 1)
	{
		cc_qsort_impl(array, 0, nr - 1, cmp);
	}

	return 1;
}

