/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"

int Power(int n,int power);

int main()
{
	int num,power ;
	printf("Enter base number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	printf("Enter power number(positive integer): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&power);
	printf("%d^%d = %d",num,power,Power(num,power));
	return 0;
}

int Power(int n,int power){
	if (power == 0)
		return 1;
	
	return n * Power(n,power-1);
}
