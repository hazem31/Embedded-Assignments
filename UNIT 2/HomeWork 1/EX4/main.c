/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	float input1 , input2;
	printf("Enter two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&input1,&input2);
	printf("\nProduct: %f",input1 * input2);
	return 0;
}


