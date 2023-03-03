/* MRIDUL SHARMA, 21176, LAB4, 05-05-2022, Week4. 
program to inplement a simple calculator
*/

#include<stdio.h>


int main()
{
  int num1,num2;
  int add,sub,mul;
  float div;
 
  printf("Enter two numbers:");
  scanf("%d %d", &num1, &num2);
  
  add = num1 + num2;
  sub = num1 - num2;
  mul = num1 * num2;
  div = (float)num1 / num2;
  
  printf("\nThe addition of the two numbers is %d", add);
  printf("\nThe subtraction of the two numbers is %d", sub);
  printf("\nThe multiplication of the two numbers is %d", mul);
  printf("\nThe division of the two numbers is %f\n", div);

  return 0;
 }
