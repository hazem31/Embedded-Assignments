/*
 * student.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */


#include "student.h"

char exist[50] = {0};

unsigned char is_exist(unsigned char num) {

	return exist[num-1];
}

unsigned char get_roll_f(char buff[] ,unsigned char *index1) {
	unsigned char i = 0,temp ;
	unsigned char index = *index1;
	char temp_text[40];
	while(buff[index] != ' ')
		{
			temp_text[i] = buff[index];
			i++;
			index++;
		}
		index++;
		temp_text[i] = 0;
		temp = atoi(temp_text);
		if(is_exist(temp))
		{
			DPRINTF("[ERROR] Roll number is already taken %d\n" , temp);
			return 0;
		}
		else
		{
			exist[temp-1] = 1;
			st[temp-1].roll = temp;
		}
		*index1 = index;
		//DPRINTF("FOUDND %d \n",temp);
		return temp;

}

void get_first_f(char buff[], unsigned char *index1 , unsigned char roll)
{
	unsigned char i = 0;
	unsigned char index = *index1;
	char temp_text[40];
	while(buff[index] != ' ')
		{
			temp_text[i] = buff[index];
			i++;
			index++;
		}
		index++;
		temp_text[i] = 0;
		strcpy(st[roll].fname,temp_text);
		*index1 = index;
		//DPRINTF("FOUDND %s \n",st[total].fname);
}

void get_last_f(char buff[], unsigned char *index1 , unsigned char roll)
{
	unsigned char i = 0;
	unsigned char index = *index1;
	char temp_text[40];
	while(buff[index] != ' ')
		{
			temp_text[i] = buff[index];
			i++;
			index++;
		}
		index++;
		temp_text[i] = 0;
		strcpy(st[roll].lname,temp_text);
		*index1 = index;
		//DPRINTF("FOUDND %s \n",st[total].lname);
}

void get_GPA_f(char buff[] ,unsigned char *index1 , unsigned char roll) {
	unsigned char i = 0;
	float temp;
	unsigned char index = *index1;
	char temp_text[40];
	while(buff[index] != ' ')
		{
			temp_text[i] = buff[index];
			i++;
			index++;
		}
		index++;
		temp_text[i] = 0;
		temp = atof(temp_text);
		st[roll].GPA = temp;
		*index1 = index;
		//DPRINTF("FOUDND %f \n",st[total].GPA);
}

void get_cs_id_f(char buff[] ,unsigned char *index1 , unsigned char roll) {
	unsigned char i = 0;
	int temp;
	unsigned char index = *index1;
	char temp_text[40];
	while(buff[index] != ' ')
		{
			if(buff[index] == '\n' || buff[index] == EOF)
				break;
			temp_text[i] = buff[index];
			i++;
			index++;
		}
		index++;
		temp_text[i] = 0;
		temp = atoi(temp_text);
		st[roll].cid[st[roll].num_cid] = temp;
		st[roll].num_cid++;
		*index1 = index;
		//DPRINTF("FOUDND %d \n",st[total].cid[st[total].num_cid-1]);
}

void print_num_of_students() {
	DPRINTF("[INFO] the total number of students is %d \n" , total);
	DPRINTF("[INFO] you can add up to %d students \n" , 50);
	DPRINTF("[INFO] you can add %d more students \n" , 50-total);
}

void add_student_file() {

	FILE *fp;
	char buff[255];
	unsigned char index , roll_num;
	fp = fopen("data.txt", "r");
	while(1)
	{
		fgets(buff, 255, (FILE*)fp);
		index = 0;
		if(!strlen(buff))
		{
			break;
		}
		roll_num = get_roll_f(buff,&index);
		if(roll_num)
		{
			//DPRINTF("SUCCESS %d \n",index);
			get_first_f(buff,&index,roll_num - 1);
			//DPRINTF("SUCCESS %d \n",index);
			get_last_f(buff,&index,roll_num - 1);
			//DPRINTF("SUCCESS %d \n",index);
			get_GPA_f(buff,&index,roll_num - 1);
			//DPRINTF("SUCCESS %d \n",index);
			st[total].num_cid = 0;
			while(index < strlen(buff))
			{
				get_cs_id_f(buff,&index,roll_num - 1);
				//DPRINTF("SUCCESS %d \n",index);
			}
			DPRINTF("[INFO] Roll Number %d saved successfully \n",roll_num);
			total++;
			buff[0] = 0;
		}
		else
		{
			continue;
		}

	}
	// below code for getting the roll number
	DPRINTF("[INFO] Students Details is added successfully \n");
	DPRINTF("--------------------------------------------------------\n");
	print_num_of_students();
	fclose(fp);

}
void add_student_manually() {
	char text_temp[40];
	unsigned char temp;
	int i;
	DPRINTF("-------------------------------------\n");
	DPRINTF("Add the Student Details \n");
	DPRINTF("-------------------------------------\n");
	DPRINTF("Enter the Roll Number: ");
	gets(text_temp);
	temp = atoi(text_temp);
	if(temp > 0 && temp < 50)
	{
		if(exist[temp])
		{
			DPRINTF("[ERROR] Roll number already used\n");
			return;
		}
		else
		{
			st[temp-1].roll = temp;
			exist[temp-1] = 1;
		}
	}
	else
	{
		DPRINTF("[ERROR] Not valid Roll number\n");
		return;
	}
	DPRINTF("Enter the First Name of the Student: ");
	gets(text_temp);
	strcpy(st[temp-1].fname, text_temp);

	DPRINTF("Enter the Last Name of the Student: ");
	gets(text_temp);
	strcpy(st[temp-1].lname, text_temp);

	DPRINTF("Enter the GPA you obtained: ");
	gets(text_temp);
	st[temp-1].GPA = atof(text_temp);

	st[temp-1].num_cid = 0;
	DPRINTF("ENTER COURCES ID (to exit enter 0 instead of ID) \n");
	for(i = 0 ; i < 10 ; i++)
	{
		DPRINTF("Course %d ID: ",i+1);
		gets(text_temp);
		if(text_temp[0] == '0')
		{
			return;
		}
		else
		{
			st[temp-1].cid[st[temp-1].num_cid] = atoi(text_temp);
			st[temp-1].num_cid++;
		}
	}
	total++;
	DPRINTF("[INFO] Student Details Added Successfully\n");
	DPRINTF("----------------------------------------------\n");


	print_num_of_students();

}

void print_one_s(unsigned char roll)
{
	unsigned char index = roll - 1,i;
	DPRINTF("The Student Details are: \n");
	DPRINTF("The First Name is: %s\n",st[index].fname);
	DPRINTF("The Last Name is: %s\n",st[index].lname);
	DPRINTF("The GPA is: %f\n",st[index].GPA);
	DPRINTF("Enrolled Courses are:\n")
	for(i = 0 ; i < st[index].num_cid; i++)
	{
		DPRINTF("Course 1 ID is: %d\n",st[index].cid[i]);
	}
	DPRINTF("--------------------------------\n");
}

void find_rl() {
	int roll;
	DPRINTF("---------------------------------\n");
	DPRINTF("Enter the Roll number of the Student: ");
	scanf("%d",&roll);
	if(is_exist(roll))
	{
		print_one_s(roll);
		return;
	}
	else
	{
		DPRINTF("[ERROR] Student doesn't exist\n");
	}
	return;
}
void find_fn() {
	char text_temp[40],i;
	DPRINTF("-----------------------------------\n");
	DPRINTF("Enter First name: ");
	gets(text_temp);
	DPRINTF("All Possible Matches \n");
	DPRINTF("-----------------------------------\n");
	for(i = 0 ; i < sizeof(st)/sizeof(struct sinfo) ; i++)
	{
		if(is_exist(i+1))
		{
			if(strcmp(st[i].fname , text_temp) == 0)
			{
				print_one_s(i+1);
			}
		}
	}

}
void find_c() {
	int temp,i,j;
	DPRINTF("-----------------------------------\n");
	DPRINTF("Enter Course ID: ");
	scanf("%d",&temp);
	DPRINTF("All Possible Matches \n");
	DPRINTF("-----------------------------------\n");
	for(i = 0 ; i < sizeof(st)/sizeof(struct sinfo) ; i++)
	{
		if(is_exist(i+1))
		{
			for(j = 0 ; j < st[i].num_cid ; j++)
			{
				if(st[i].cid[j] == temp)
				{
					print_one_s(i+1);
				}
			}
		}
	}

}
void tot_s() {
	print_num_of_students();
}
void del_s() {
	int roll;
	DPRINTF("---------------------------------\n");
	DPRINTF("Enter the Roll number of the Student: ");
	scanf("%d",&roll);
	if(is_exist(roll))
	{
		exist[roll-1] = 0;
		total--;
		DPRINTF("[INFO] Student with Roll Number %d Deleted \n",roll);
	}
	else
	{
		DPRINTF("[ERROR] Student doesn't exist\n");
	}
	return;
}

void show_s() {
	int i,j;
	for(i = 0 ; i < sizeof(exist) ; i++)
	{
		if(exist[i])
		{
			DPRINTF("----------------------------------------\n");
			DPRINTF("Student First name : %s\n",st[i].fname);
			DPRINTF("Student Last name : %s\n",st[i].lname);
			DPRINTF("Student Roll Number : %d\n",st[i].roll);
			DPRINTF("Student GPA  Number : %f\n",st[i].GPA);
			for(j = 0 ; j < st[i].num_cid ; j++)
			{
				DPRINTF("The Course ID is %d\n" , st[i].cid[j]);
			}
		}
	}
}

