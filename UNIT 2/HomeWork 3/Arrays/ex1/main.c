/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	float m1[2][2];
	float m2[2][2] , sum[2][2];
	printf("Enter the elements of 1st matrix\n");
	printf("Enter a11: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m1[0][0]);
	printf("Enter a12: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m1[0][1]);
	printf("Enter a21: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m1[1][0]);
	printf("Enter a22: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m1[1][1]);
	

	printf("Enter the elements of 2nd matrix\n");
	printf("Enter b11: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m2[0][0]);
	printf("Enter b12: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m2[0][1]);
	printf("Enter b21: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m2[1][0]);
	printf("Enter b22: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&m2[1][1]);
	
	sum[0][0] = m1[0][0] + m2[0][0];
	sum[1][0] = m1[1][0] + m2[1][0];
	sum[0][1] = m1[0][1] + m2[0][1];
	sum[1][1] = m1[1][1] + m2[1][1];

	printf("Sum of the Matrix:\n%f\t%f\n%f\t%f",sum[0][0],sum[0][1],sum[1][0],sum[1][1]);
	return 0;
}


