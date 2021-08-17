/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	float nums[100] , avg;
	int num , i;
	printf("Enter the number of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	for ( i = 0; i < num; i++)
	{
		printf("Enter number %d: ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&nums[i]);
		avg += nums[i];
	}
	

	printf("Average: %.2f",avg/num);
	return 0;
}


