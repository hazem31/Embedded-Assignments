/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	int input;
	printf("Enter an integer you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&input);
	
	if (input%2 == 0)
		printf("%d is even",input);
	else
		printf("%d is odd",input);
	
	
	return 0;
}


