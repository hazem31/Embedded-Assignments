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
	char arr[26],*ptr;
	int i;
	for ( i = 0; i < 26; i++)
	{
		arr[i] = 65 + i;
	}
	ptr = arr;
	for ( i = 0; i < 26; i++)
	{
		printf("%c ",*(ptr+i));
	}
	
	return 0;
}

