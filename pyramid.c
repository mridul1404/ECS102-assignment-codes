/*
MRIDUL SHARMA
21176
LAB4
05-05-2022
Week4
C-program to print the following pyramid
         1
        232
       34543
      4567654
     567898765
    67890109876
   7890123210987
  890123454321098
 90123456765432109
0123456789876543210
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
int a, b, c, d, rowMax, elements;
rowMax = 10;
elements = (2*rowMax)-1;
for(int row = 1; row <= rowMax; row++)
{
for(int e=1 ; e <= elements; e++)
{
if((e < ((elements+1)/2)-(row-1)) || (e > ((elements+1)/2)+(row-1)))
{
printf(" ");
}
else
{
a = (((2*row)-1) - (abs(((elements+1)/2) - e)));
a = a%10;
printf("%d", a);
}
}
printf("\n");
}

}

