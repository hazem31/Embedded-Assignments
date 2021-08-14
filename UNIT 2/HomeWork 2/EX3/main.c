/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	float a,b,c,max;
	printf("Enter three numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&a,&b,&c);
	
	max = (a > b) ? ((a>c) ? a : b) : ((b > c) ? b : c);
	printf("Largest number: %f" , max);
	return 0;
}


