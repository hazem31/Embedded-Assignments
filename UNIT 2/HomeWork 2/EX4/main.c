/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	float input;
	printf("Enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&input);
	
	if (input > 0)
		printf("%f is positive",input);
	else if (input < 0)
		printf("%f is negative",input);
	else
		printf("You entered zero.");
	
	return 0;
}


