/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"


int main()
{	
	int arr[15],size = 0 , i , *ptr ;

	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);

	printf("Input %d number of elements in the array :\n",size);
	for ( i = 0; i < size; i++)
	{
		printf("element - %d : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",&arr[i]);
	}

	printf("The elements of array in reverse order are :\n");
	for (ptr = size + arr - 1,i=size ; ptr >= arr; ptr-- , i--)
	{
		printf("element - %d : %d \n",i,*ptr);
	}
	
	
	return 0;
}

