/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"

void reverse(char arr[], int index);

int main()
{
	char str[30];
	printf("Enter a sentence: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	reverse(str,0);
	return 0;
}


void reverse(char arr[] , int index) {
	
	if(arr[index] == 0)
		return;
	
	reverse(arr,index+1);
	printf("%c",arr[index]);
}
