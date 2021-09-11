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
	int roll;
	float marks;
};



int main()
{
	struct Student students[10];
	int i;

	printf("Enter inforamtion for students\n");
	for ( i = 0; i < 10; i++)
	{
		students[i].roll = i+1;
		printf("for roll number: %d\n",i+1);
		printf("Enter Name: ");
		fflush(stdin); fflush(stdout);
		scanf("%s",students[i].name);
		printf("Enter marks: ");
		fflush(stdin); fflush(stdout);
		scanf("%f",&students[i].marks);
	}
	printf("Displaying inforamtion for students\n");
	for (i = 0; i < 10; i++)
	{
		printf("Information for roll number %d:\nName: %s\nMarks: %f\n",students[i].roll,students[i].name,students[i].marks);
	}
	
	
	return 0;
}

