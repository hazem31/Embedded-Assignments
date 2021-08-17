/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: hazem
 */


#include <stdio.h>

int main()
{
	int m1[10][10] , m2[10][10];
	int rows,cols,i,j;
	printf("Enter rows and columns of matrix: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&rows,&cols);
	printf("Enter the elements of matrix\n");
	for ( i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("Enter elements a%d%d: ",i+1,j+1);	
			fflush(stdin); fflush(stdout);
			scanf("%d",&m1[i][j]);
		}
	}
	for ( i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			m2[j][i] = m1[i][j];
		}
		
	}
	printf("Entered Matrix:\n");
	for ( i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%d\t: ",m1[i][j]);	
		}
		printf("\n");
	}

	printf("Transpose of Matrix:\n");
	for ( i = 0; i < cols; i++)
	{
		for (j = 0; j < rows; j++)
		{
			printf("%d\t: ",m2[i][j]);	
		}
		printf("\n");
	}

	return 0;
}


