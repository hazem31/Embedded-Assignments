/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	float input1,input2,result;
	char op;
	printf("Enter operator eirher + or - or * or / : ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&op);
	printf("Enter two operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&input1,&input2);

	switch (op)
	{
		case '+':
		{
			result = input1 + input2;
		}
		break;
		case '-':
		{
			result = input1 - input2;
		}
		break;
		case '*':
		{
			result = input1 * input2;
		}
		break;
		case '/':
		{
			result = input1 / input2;
		}
		break;
	}
	
	printf("%f %c %f = %f",input1,op,input2,result);
	

	return 0;
}


