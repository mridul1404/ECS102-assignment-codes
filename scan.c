/* MRIDUL SHARMA, 21176, 05-05-2022, LAB4, WEEK4. */

#include<stdio.h>


int main()
{
char para[1000];
int len = 0, j =0;
printf("Please enter the lines : ");
scanf("%[^*]", para);
for(len = 0; len<1000; len++)
{
if(para[len] == '\0')
break;
}
//printf("%d", len);
for(j = 0; j < len; j++)
{
if((para[j] <= 122) && (para[j] >= 97))
{
para[j] = para[j]-32;
}
else{
continue;
}
}
printf("%s\n", para);
}
