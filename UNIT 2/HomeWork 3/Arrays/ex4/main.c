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
	int i,size,element,location,prev1,prev2;
	printf("Enter num of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);
	for ( i = 0; i < size; i++)
	{
		nums[i] = i+1;
		printf("%d ",nums[i]);
	}
	printf("\n");
	
	printf("Enter the element to be inserted : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&element);

	printf("Enter the location : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);
	
	prev1 = nums[location-1];
	nums[location-1] = element;
	for ( i = location; i < size+1; i++)
	{
		prev2 = nums[i];
		nums[i] = prev1;
		prev1 = prev2;
	}
	
	for ( i = 0; i < size + 1; i++)
	{
		printf("%d ",nums[i]);
	}
	
	
	return 0;
}


