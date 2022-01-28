/*
 * main.cc
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#include "stdio.h"
#include "string.h"
#include "student.h"

int main()
{
	char text_temp[40];
	unsigned char choice;
	DPRINTF("Welcome to the Student Management System\n");
	while(1) {
		DPRINTF("Choose the Task you want to perform\n");
		DPRINTF("1.  Add New Student Manually \n");
		DPRINTF("2.  Add New Student from File \n");
		DPRINTF("3.  Find Student With ID \n");
		DPRINTF("4.  Find Student With First Name \n");
		DPRINTF("5.  Find Students Registered in a course \n");
		DPRINTF("6.  Find Students Count \n");
		DPRINTF("7.  Delete a Student \n");
		DPRINTF("8.  View All Students \n");
		DPRINTF("9. Exit \n");
		DPRINTF("Enter your choice to perform task: ");
		//gets(text_temp);
		//DPRINTF("your choice was %d \n",atoi(text_temp));
		gets(text_temp);
		choice = atoi(text_temp);
		switch(choice) {

		case 1:
		add_student_manually();
		break;

		case 2:
		add_student_file();
		break;

		case 3:
		find_rl();
		break;

		case 4:
		find_fn();
		break;

		case 5:
		find_c();
		break;

		case 6:
		tot_s();
		break;

		case 7:
		del_s();
		break;

		case 8:
		show_s();
		break;

		case 9:
		DPRINTF("Existing --------------------------\n");
		return 0;
		}
	}

	return 0;
}
