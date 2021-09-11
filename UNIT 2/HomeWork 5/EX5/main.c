/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"



#define area(r) 3.14*(r)*(r)


int main()
{
	
	int rad;
	printf("Enter the radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&rad);
		
	printf("Area = %f",area(rad));
	
	
	return 0;
}

