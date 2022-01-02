/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#include "stdio.h"
#include "lifo.h"
#include "stdlib.h"

unsigned int buffer1[5];

void main() {

	int i;
	LIFO_Buf_t uart_lifo , I2C_lifo;
	LIFO_init(&uart_lifo , buffer1 , 5);
	unsigned int * buffer2 = (unsigned int *) malloc(5*sizeof(unsigned int));
	LIFO_init(&I2C_lifo , buffer2 , 5);


	for(i = 0; i < 5; i++) {
		if (LIFO_add_item(&uart_lifo , i) == LIFO_no_error )
			printf("UART_LIFO add : %d \n" ,i );
	}

	for(i = 0; i < 5; i++) {
		if (LIFO_add_item(&I2C_lifo , i) == LIFO_no_error)
			printf("I2C_LIFO add : %d \n" ,i );
	}
}
