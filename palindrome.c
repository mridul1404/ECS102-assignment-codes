/* MRIDUL SHARMA, 21176, 05-05-2022, LAB4, WEEK4.
C program that will enter a line of text containing a word, a
phrase or a sentence, and determine whether or not the text is a
palindrome. */

#include<stdio.h>
#include<string.h>


int main()
{
   char string1[20];
   int i, length;
   int flag = 0;
   
   printf("Enter a string:");
   scanf("%s", string1);
   
   length = strlen(string1);
   
   for(i=0;i < length ; i++){
       if(string1[i] != string1[length-i-1])
            {
              flag = 1;
              break;
              }
            }
       if (flag) {
          printf("%s is not a palindrome", string1);
          }
          else {
             printf("%s is a palindrome", string1);
          }
      return 0;
}
