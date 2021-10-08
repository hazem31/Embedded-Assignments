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
	int m = 29;
	printf("Address of m : 0x%x\n", &m);
	printf("Value of m : %d\n",m);

	int *ab = &m;
	printf("Now ab is assigned with the address of m.\n");
	printf("Address of pointer ab : 0x%x\n", ab);
	printf("Content of pointer ab : %d\n",*ab);

	m = 34;

	printf("The value of m assigned to %d now\n",m);
	printf("Address of pointer ab : 0x%x\n", ab);
	printf("Content of pointer ab : %d\n",*ab);

	*ab = 7;

	printf("The pointer variable ab is assigned with the value %d now.\n",m);
	printf("Address of m : 0x%x\n", &m);
	printf("Value of m : %d\n",m);
	return 0;
}

