/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"




struct Complex
{
	float real;
	float img;
}c1,c2,c3;


struct Complex Add(struct Complex num1, struct Complex num2) {
	struct Complex sum;
	sum.real = num1.real + num2.real;
	sum.img = num1.img + num2.img;

	return sum;
}


int main()
{

	printf("for the 1st Complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&c1.real,&c1.img);
	
	printf("for the 2nd Complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&c2.real,&c2.img);
	
	c3 = Add(c1,c2);
	
	printf("Sum= %.2f+%.2fi",c3.real,c3.img);
	
	return 0;
}

