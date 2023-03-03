/*
Mridul Sharma
21176
09|06|2022
Assignment 07
Lab 04
C code that takes n as input and further scans n integers
from standard input, into a dynamically allocated array and finally
output a sorted list of these numbers.
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    int *ptr;
    printf("Specify the size of the array : ");
    scanf("%d", &n);
    ptr = (int *)malloc(n * sizeof(int));

    printf("Enter the values below :\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ptr[i]);
    }

    int j;
    for (int i = 0; i < n; i++)
    {
        int current = ptr[i];
        int j = i - 1;
        while (ptr[j] > current && j >= 0)
        {
            ptr[j + 1] = ptr[j];
            j--;
        }

        ptr[j + 1] = current;
    }

    printf("Sorted order is : \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ptr[i]);
    }
    free(ptr);
    return 0;
}
