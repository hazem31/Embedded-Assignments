/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"

int main()
{
	int length,i=0;
	char str[50];
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	while (str[i] != 0)
	{
		length++;
		i++;
	}
	
	printf("Length of string: %d",length);
	
	
	
	return 0;
}


