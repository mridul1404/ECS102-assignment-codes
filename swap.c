/*
Mridul Sharma
21176
09|06|2022
Assignment 07
Lab 04
program to swap two numbers

*/

#include <stdio.h>

int main()
{
	int x, y;
	printf("Enter Value of x: ");
	scanf("%d", &x);
	printf("\nEnter Value of y: ");
	scanf("%d", &y);

	int temp = x;
	x = y;
	y = temp;

	printf("After Swapping: x = %d, y = %d \n", x, y);
	return 0;
}

