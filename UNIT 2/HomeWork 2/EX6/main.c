/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	int input,sum = 0;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&input);

	int i = 0;
	for ( i = 0; i <= input; i++)
	{
		sum += i;
	}
	
	printf("Sum = %d",sum);
	

	return 0;
}


