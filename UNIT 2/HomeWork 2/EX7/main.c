/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	int input,factorial = 1;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&input);

	
	if (input < 0)
	{
		printf("Error! of a negative number doesn't exist");
		return 0;
	}
	int i;
	for ( i = 1; i <= input; i++)
	{
		factorial *= i;
	}
	
	printf("Factorial = %d",factorial);
	

	return 0;
}


