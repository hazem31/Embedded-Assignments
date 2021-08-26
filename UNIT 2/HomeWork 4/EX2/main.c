/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"

int factorial(int num);

int main()
{
	int num,result;
	printf("Enter a positive integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	result = factorial(num);
	printf("Factorial of %d = %d",num,result);
	return 0;
}


int factorial(int num) {
	
	if (num == 1 || num == 0)
	{
		return 1;
	}
	return num * factorial(num-1);
	
	
}
