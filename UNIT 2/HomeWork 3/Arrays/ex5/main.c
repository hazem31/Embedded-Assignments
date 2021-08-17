/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	int nums[20];
	int i,size,element;
	printf("Enter num of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);
	for ( i = 0; i < size; i++)
	{
		nums[i] = (i+1) * 11;
		printf("%d ",nums[i]);
	}
	printf("\n");

	printf("Enter the element to be searched : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&element);

	for ( i = 0; i < size + 1; i++)
	{	
		if(nums[i] == element)
		{
			printf("Number found at the location = %d",i+1);
			break;
		}
		
	}
	
	
	return 0;
}


