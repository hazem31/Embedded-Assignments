/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

#define DPRINTF(...) {fflush(stdout); \
					  fflush(stdin); \
					  printf(__VA_ARGS__); \
					  fflush(stdout); \
					  fflush(stdin);}

struct Sdata {
	int ID;
	char name[40];
	float height;

};

struct SStudent {
	struct Sdata student;
	struct SStudent *next;
};

struct SStudent *FirstStudent = NULL;


void AddStudent()
{
	struct SStudent *pNewStudent , *temp;
	char text_temp[40];
	if(FirstStudent == NULL)
	{
		pNewStudent =(struct SStudent*) malloc(sizeof(struct SStudent));
		FirstStudent = pNewStudent;

	}
	else
	{
		temp = FirstStudent;
		while(temp->next != NULL)
			temp = temp->next;
		pNewStudent =(struct SStudent*) malloc(sizeof(struct SStudent));
		temp->next = pNewStudent;
	}

	DPRINTF("\nEnter the ID: ");
	gets(text_temp);
	pNewStudent->student.ID = atoi(text_temp);

	DPRINTF("\nEnter the Name: ");
	gets(pNewStudent->student.name);

	DPRINTF("\nEnter the Height: ");
	gets(text_temp);
	pNewStudent->student.height = atof(text_temp);

	pNewStudent->next = NULL;
	DPRINTF("\nRegistered ");

}

void DeleteStudent()
{
	char temp_text[40];
	unsigned int id;
	struct SStudent *prev = NULL,*curr = FirstStudent;
	DPRINTF("Enter the Student ID to be deleted: ");
	gets(temp_text);
	id = atoi(temp_text);
	if(FirstStudent)
	{
		while(curr)
		{
			if(curr->student.ID == id)
			{
				if(prev)
				{
					prev->next = curr->next;
				}
				else
				{
					FirstStudent = FirstStudent->next;
				}
				free(curr);
				DPRINTF("\nDeleted");
				return;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	DPRINTF("Student Not Found\n");
}

void PrintStudents()
{
	struct SStudent *curr = FirstStudent;
	int count=0;
	if(!curr)
	{
		DPRINTF("\nEMPTY LIST");
	}
	else
	{
		while(curr)
		{
			DPRINTF("\nRecord Number %d",count+1);
			DPRINTF("\n \t ID: %d",curr->student.ID);
			DPRINTF("\n \t Name: %s",curr->student.name);
			DPRINTF("\n \t Height: %f",curr->student.height);
			DPRINTF("\n ===========================");
			curr = curr->next;
			count++;
		}
	}
}

void DeleteAll()
{
	struct SStudent *curr = FirstStudent;
	int count=0;
	if(!curr)
	{
		DPRINTF("\nEMPTY LIST");
	}
	else
	{
		struct SStudent *temp = FirstStudent;
		while(curr)
		{
			temp = curr;
			curr = curr->next;
			free(temp);
		}
		FirstStudent = NULL;
		DPRINTF("Deleted All Records");
	}

}


void main()
{
	char temp_text[40];
	while(1)
	{
		DPRINTF("\n======================");
		DPRINTF("\n choose one o the following options");
		DPRINTF("\n 1: Add Student");
		DPRINTF("\n 2: Delete Student");
		DPRINTF("\n 3: Print Student");
		DPRINTF("\n 4: Delete All\n");

		gets(temp_text);
		DPRINTF("\n====================");
		switch(atoi(temp_text))
		{
		case 1:
			AddStudent();
			break;
		case 2:
			DeleteStudent();
			break;
		case 3:
			PrintStudents();
			break;
		case 4:
			DeleteAll();
			break;
		}
	}

}
