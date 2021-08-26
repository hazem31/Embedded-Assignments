/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"

void findPrime(int x , int y);

int main()
{
	int x,y;
	printf("Enter two numbers(intervals): ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x,&y);
	findPrime(x,y);
	return 0;
}


void findPrime(int x , int y) {
	int i,h,j;
	printf("Prime numbers between %d and %d: ",x,y);
	for ( i = x; i <= y ; i++)
	{
		if ( i %2 == 0)
			continue;
		h = sqrt(i)+1;
		for ( j = 2 ; j < h; j++)
		{
			if (i % j == 0)
				break;
			
		}
		if (j == h)
			printf("%d ",i);
	}
	
}
