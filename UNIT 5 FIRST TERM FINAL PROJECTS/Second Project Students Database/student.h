/*
 * student.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#ifndef STUDENT_H_
#define STUDENT_H_


#include "stdio.h"
#include "string.h"
#include "conio.h"
#include "stdlib.h"

#define DPRINTF(...) {fflush(stdout); \
					  fflush(stdin); \
					  printf(__VA_ARGS__); \
					  fflush(stdout); \
					  fflush(stdin);}


struct sinfo {
	int num_cid;
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[10];
} st[50];


static unsigned int total = 0;

void add_student_file();
void add_student_manually();
void find_rl();
void find_fn();
void find_c();
void tot_s();
void del_s();
void up_s();
void show_s();





#endif /* STUDENT_H_ */
