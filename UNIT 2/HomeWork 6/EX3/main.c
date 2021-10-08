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
	char str[50],*ptr;
	int size = 0;
	printf("Input a string : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",str);
	size = strlen(str);
	ptr = size + str;
	for ( ptr = size + str; ptr >= str ; ptr--)
	{
		printf("%c",*ptr);
	}
	
	return 0;
}

