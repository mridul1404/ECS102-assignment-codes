/*
Mridul Sharma
21176
02|06|2022
Assignment 07
Lab 04
program to print determinant to an nxn integer matrix
*/

#include<stdio.h>
#include<stdlib.h>

int readMatrix(int **mat, int size);
int displayMatric(int **mat,int size);
int** subMatrix( int **mat, int size, int row, int column);
int determinant(int **mat, int size);

int main()
{
 int size, i, j, **mat;
 printf("Enter size of matrix = ");
 scanf("%d", &size);
 mat = (int **) malloc(size*(sizeof(int *)));
	
 for(i=0; i<size; i++)
 {
  mat[i] = (int *) malloc(size*(sizeof(int)));
 }

 readMatrix(mat,size);
 displayMatric(mat,size);
 printf("Determinant = %d\n", determinant(mat,size));

 for(j=0; j<size; j++)
 {
  free(mat[j]);
 }
 free(mat);
 return 0;
}

int readMatrix(int **mat, int size)
{
 int i,j;
 printf("Enter %dx%d matrix = ", size, size);
 for(i=0; i<size; i++)
 {
  for(j=0;j<size;j++)
  {
   scanf("%d",&mat[i][j]);
  }
 }
 printf("\n-----------------------\n\n");
}

int displayMatric(int **mat,int size)
{
 int i,j;
 for(i=0; i<size; i++)
 {
  for(j=0;j<size;j++)
  {
   printf("%d ", mat[i][j]);
  }
  printf("\n");
 }
 printf("\n-----------------------\n\n");
}

int** subMatrix( int **mat, int size, int row, int column)
{
 int **subMat, i, j, I=0, J=0;

 subMat = (int **) malloc((size-1)*(sizeof(int *)));

 for(i=0; i<(size-1); i++)
 {
  subMat[i] = (int *) malloc((size-1)*(sizeof(int)));
 }
	
 for(i=0; i<(size-1); i++)
 {
  if(i>=(row))
  {
   I=1;
  }

  for(j=0;j<(size-1);j++)
  {
   J=0;
   if(j>=(column))
   {
    J=1;
   }
   
   subMat[i][j] = mat[i+I][j+J];  
  
  }
 }

 return(subMat);
	
 /*for(j=0; j<(size-1); j++)
 {
  free(subMat[j]);
 }
 free(subMat);*/
}

int determinant(int **mat, int size)
{
 int i=0, j, I, det=0; 

 if(size==2)
 {
  return((mat[0][0]*mat[1][1])-(mat[0][1]*mat[1][0]));
 }

 else if(size==1)
 {
  return(mat[1][1]);
 }
	
 else
 {
  for(j=0;j<size;j++)
  {
   I = -1;
   if((i+j)%2==0)
   {
    I = 1;
   }
	
   det = det + ((I)*(mat[i][j])*(determinant((subMatrix(mat,size,i,j)),(size-1))));
   
  }
  return det;
 }
}
