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
	int length,i,freq=0;
	char str1[100],chr;
	printf("Enter the string: ");
	fflush(stdin); fflush(stdout);
	gets(str1);
	printf("Enter a character to find frquency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&chr);
	length = strlen(str1);
	for ( i = 0 ; i < length ; i++)
	{
		if (str1[i] == chr)
		{
			freq++;
		}
		
	}

	printf("Frequency of %c = %d",chr,freq);
	
	
	
	return 0;
}


