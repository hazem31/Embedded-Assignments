/*
 * lifo.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#ifndef LIFO_H_
#define LIFO_H_

typedef struct {
	unsigned int length;
	unsigned int count;
	unsigned int *head;
	unsigned int *base;
}LIFO_Buf_t;

typedef enum {
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_Null
}LIFO_status;

LIFO_status LIFO_add_item(LIFO_Buf_t *lifo_buff ,unsigned int item);
LIFO_status LIFO_get_item(LIFO_Buf_t *lifo_buff ,unsigned int* item);
LIFO_status LIFO_init(LIFO_Buf_t *lifo_buff, unsigned int* buf , unsigned int size);


#endif /* LIFO_H_ */
