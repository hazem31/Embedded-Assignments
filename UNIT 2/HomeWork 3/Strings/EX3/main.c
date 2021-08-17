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
	int length,i,j;
	char str1[50],str2[50];
	printf("Enter the string: ");
	fflush(stdin); fflush(stdout);
	gets(str1);

	length = strlen(str1);
	for ( i = length-1, j =0 ; i >= 0; i--,j++)
	{
		str2[j] = str1[i];
	}
	str2[j] = 0;

	printf("Reverse string is : %s",str2);
	
	
	
	return 0;
}


