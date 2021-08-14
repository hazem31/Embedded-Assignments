/*
 * main.c
 *
 *  Created on: ??ş/??ş/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	int input1 , input2;
	printf("Enter two integers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&input1,&input2);
	printf("\nSum: %d",input1 + input2);
	return 0;
}


