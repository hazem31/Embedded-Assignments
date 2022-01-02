/*
 * lifo.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: hazem
 */

#include "lifo.h"

LIFO_status LIFO_add_item(LIFO_Buf_t *lifo_buff ,unsigned int item)
{
	if(! lifo_buff->head || ! lifo_buff->base)
		return LIFO_Null;

	if(lifo_buff->count > lifo_buff->length)
		return LIFO_full;

	*(lifo_buff->head) = item;
	lifo_buff->head++;
	lifo_buff->count++;

	return LIFO_no_error;
}
LIFO_status LIFO_get_item(LIFO_Buf_t *lifo_buff ,unsigned int* item)
{
	if(! lifo_buff->head || ! lifo_buff->base)
		return LIFO_Null;

	if(lifo_buff->count == 0)
		return LIFO_empty;

	lifo_buff->head--;
	*item = *lifo_buff->head;
	lifo_buff->count--;
	return LIFO_no_error;
}
LIFO_status LIFO_init(LIFO_Buf_t *lifo_buff, unsigned int* buf , unsigned int size)
{
	if(! lifo_buff)
		return LIFO_Null;

	lifo_buff->head = buf;
	lifo_buff->base = buf;
	lifo_buff->length = size;
	lifo_buff->count = 0;
	return LIFO_no_error;
}
