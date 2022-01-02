/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#include "stdio.h"
#include "stdlib.h"

#include "fifo.h"

void main() {
	FIFO_Buf_t FIFO_uart;
	element_type i , temp;
	if( FIFO_init(&FIFO_uart , buff , 5) == FIFO_no_error )
		printf("Fifo Init ----Done\n");
	for(i = 0 ; i < 7 ; i++)
	{
		printf("FIFO enqueue (%x)\n",i);
		if( FIFO_enqueue(&FIFO_uart ,i) == FIFO_no_error )
			printf("Fifo enqueue ----Done\n");
		else
			printf("Fifo enqueue ----failed\n");
	}

	FIFO_print(&FIFO_uart);
	if( FIFO_dequeue(&FIFO_uart ,&temp) == FIFO_no_error )
				printf("Fifo dequeue %x ----Done\n",temp);
	if( FIFO_dequeue(&FIFO_uart ,&temp) == FIFO_no_error )
				printf("Fifo enqueue %x ----Done\n",temp);

}
