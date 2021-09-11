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
	struct Student student;
	printf("Enter Name: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",student.name);
	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&student.roll);
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&student.marks);
	
	printf("Displaying Information\nname: %s\nRoll: %d\nMarks: %f\n",student.name,student.roll,student.marks);
	
	return 0;
}

