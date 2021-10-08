/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>
#include "string.h"
#include "math.h"

struct Student
{
	char name[50];
	unsigned int id;
}s1,s2;



int main()
{	

	struct Student * arr[2];
	struct Student * (* ptr)[2];
	ptr = arr;
	strcpy(s1.name,"Alex");
	s1.id = 1002;

	(*ptr)[0] = &s1;

	printf("Employee Name : %s\n",(*ptr)[0]->name);
	printf("Employee ID : %d" , (*ptr)[0]->id);

	return 0;
}

