/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	char input;
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&input);
	
	switch (input)
	{
	case 'A':
	case 'a':
		{
			printf("%c is a voewl\n",input);
		}
		break;
	case 'E':
	case 'e':
		{
			printf("%c is a voewl\n",input);
		}
		break;
	case 'I':
	case 'i':
		{
			printf("%c is a voewl\n",input);
		}
		break;
	case 'O':
	case 'o':
		{
			printf("%c is a voewl\n",input);
		}
		break;
	case 'U':
	case 'u':
		{
			printf("%c is a voewl\n",input);
		}
		break;
	
	default:
		{
			printf("%c is a consonant\n" , input);
		}
		break;
	}
	
	return 0;
}


