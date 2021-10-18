#include "uart.h"
unsigned char string_buffer[100] = "learn-in-depth";
void main()
{
	Uart_Send_String(string_buffer);
}