/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"




struct Distance
{
	int feet;
	float inch;
}d1,d2,d3;



int main()
{

	printf("Enter information for the 1st distance\n");
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&d1.feet);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d1.inch);
	
	printf("Enter information for the 2nd distance\n");
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&d2.feet);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d2.inch);
	
	d3.feet = d1.feet + d2.feet;
	d3.inch = d1.inch + d2.inch;

	if (d3.inch >= 12)
	{
		d3.inch -= 12;
		d3.feet++;
	}
	
	
	printf("Sum of the distances=%d\'%.2f",d3.feet,d3.inch);
	
	return 0;
}

