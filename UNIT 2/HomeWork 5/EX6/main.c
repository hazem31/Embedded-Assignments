/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"


union jop
{
	char name[32];
	float salary;
	int no;
}u;

struct jop1
{
	char name[32];
	float salary;
	int no;
	
}s;


int main()
{
	
	printf("size of union= %d\n",sizeof(u));
	printf("size of struct= %d\n",sizeof(s));
		
	return 0;
}

