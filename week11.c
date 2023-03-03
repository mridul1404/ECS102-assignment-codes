/*
Name : Mridul Sharma
Roll No. : 21176
Date : 10/07/2022
compute the determinant of a rational
(arbitrary large precision) matrix of size n × n.
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Defining the Structures required for the code.
typedef struct {
	int sign;
	char *digit;
	int size;
} nstrng;
typedef struct {
	nstrng d;
	int r;
} strdiv;
typedef struct {
	nstrng num;
	nstrng den;
	} Rational;

//functions being used
nstrng num_add(nstrng n1, nstrng n2);
nstrng num_diff(nstrng n1, nstrng n2);
nstrng read_num();
void print_num(nstrng n1);
nstrng num_mult(nstrng n1, nstrng n2);
int readMatrix(Rational **mat, int size);
int displayMatric(Rational **mat,int size);
Rational** subMatrix( Rational **mat, int size, int row, int column);
Rational determinant(Rational **mat, int size);
Rational** inverse(Rational **mat, int size);
Rational redRat(nstrng n, nstrng d);
void printRat(Rational R);
Rational addRat(Rational R1, Rational R2);
Rational subRat(Rational R1, Rational R2);
Rational mutRat(Rational R1, Rational R2);
Rational divRat(Rational R1, Rational R2);
strdiv num_div(nstrng n1, int d);

//Main Function
int main()
{
	int size, i, j;
	Rational **mat, **invM, det;
	printf("Enter the size of the Matrix = ");
	scanf("%d", &size);

	//allotment of matrix of required size(input taken above)
	mat = (Rational **) malloc(size*(sizeof(Rational *)));
	for(i=0; i<size; i++)
	{
		mat[i] = (Rational *) malloc(size*(sizeof(Rational)));
	}
	
	invM = (Rational **) malloc(size*(sizeof(Rational *)));
	for(i=0; i<size; i++)
	{
		invM[i] = (Rational *) malloc(size*(sizeof(Rational)));
	}

	readMatrix(mat,size);
	displayMatric(mat,size);
	det = determinant(mat,size);
	det = redRat(det.num, det.den);
	
	//checking if the matrix is invertible or not( By checking if determinant is 0 )
	if(det.num.digit[0]=='0')
		printf("The Matrix entered is invertible \n");
	else
		printf("Determinant of the Matrix = ");
		printRat(det);
		printf("\n");
		printf("\n============================================");
		printf("\n============================================\n\n");
		invM = inverse(mat,size);
		displayMatric(invM,size);

	//freeing of the Matrix:
	for(j=0; j<size; j++)
	{
		free(mat[j]);
	}
	free(mat);

	for(j=0; j<size; j++)
	{
		free(invM[j]);
	}
	free(invM);

	return 0;
}

//To read a string number:
nstrng read_num()
{
	nstrng temp;
	int i,l;
	char temp1[300];
	l=0;
	
	scanf("%s",temp1);
	if(temp1[0]=='-')
		temp.sign=(-1);
	else
		temp.sign=(+1);		
	
	for(i=1;temp1[i]!='\0';i++)
	temp.size=i;
	
	//allocation of the required memory
	temp.digit = (char*)malloc(temp.size*(sizeof(char)));

	for(i=0;i<(temp.size);i++)
	{
		temp.digit[i]=temp1[i+1];
	}
	
	return(temp);
}

//To print a string number with its respective symbol:
void print_num(nstrng n1)
{
	char sign1;
	int i;

	//To print the sign of the string number('+' or '-'):
	if(n1.sign==1)
	{
		sign1='+';
	}	
	else
	{
		sign1='-';
	}
	
	printf("%c", sign1);

	for(i=0;i<(n1.size);i++)
	{
		printf("%c",n1.digit[i]);
	}
}

//Function to add two arbitrary precision numbers:
nstrng num_add(nstrng n1, nstrng n2)
{
	nstrng sum1,n3;
	int num1[255], num2[255], sum[255];
	int I,J,K;
	int l1,l2;
	int N1=0,N2=0;
	l1=n1.size;
	l2=n2.size;
	
	//To check which string number is larger:
	if(l1>l2)
	{
		N1=1;
	}
	else if(l2>l1)
	{
		N2=1;
	}
	else if(l2==l1)
	{
		for(I=0;I<l1;I++)
		{
			if(n1.digit[I]!=n2.digit[I])
			{
				N1=((n1.digit[I]-n2.digit[I])>0) ? 1:(-1);
				break;
			}
		}
	}
	
	//If the signs are different make a third positive string number and then subtratcing them
	if((n1.sign)!=(n2.sign))
	{
		if(n1.sign==(-1))
		{
			n3.digit=(char*)malloc((n1.size)*sizeof(char));
			n3.digit=n1.digit;
			n3.size=n1.size;
			n3.sign=1;
			sum1=num_diff(n3,n2);
		}
		else
		{
			n3.digit=(char*)malloc((n2.size)*sizeof(char));
			n3.digit=n2.digit;
			n3.size=n2.size;
			n3.sign=1;
			sum1=num_diff(n1,n3);
		}
		
		if(((N2>N1)&&(n2.sign==(-1)))||((N1>N2)&&(n1.sign==(-1))))
		{
			sum1.sign=(-1);
		}
		else
		{
			sum1.sign=1;
		}
		
		return(sum1);
	}
		
	//Converting the string in a int array:
	for (I=0;I<(n1.size);I++)
	{
		num1[I] = n1.digit[I] - '0';
	} 	
	for (I=0;I<(n2.size);I++)
	{
		num2[I] = n2.digit[I] - '0';
	}
 	
	l1=n1.size;
	l2=n2.size;

	int carry = 0;
	int k = 0;
	int i = l1 - 1;
	int j = l2 - 1;
	for (; i >= 0 && j >= 0; i--, j--, k++) 
 	{
		sum[k] = (num1[i] + num2[j] + carry) % 10;
		carry = (num1[i] + num2[j] + carry) / 10;
	} 

	if (l1 > l2) 
	{
 		while (i >= 0) 
		{
			sum[k++] = (num1[i] + carry) % 10;
			carry = (num1[i--] + carry) / 10;
     		}
 
	} 
	else if (l1 < l2) 
	{
		while (j >= 0) 
     		{
			sum[k++] = (num2[j] + carry) % 10;
			carry = (num2[j--] + carry) / 10;
     		}

	} 
	else 
	{
		if (carry > 0)
		sum[k++] = carry;
  	}

	K=k;
	sum1.digit = (char*)malloc(K*(sizeof(char)));

	for (k--; k >= 0; k--)
	{
		sum1.digit[K-(k+1)]='0'+sum[k];
	}
	sum1.size=K;
	sum1.sign=1;
	
	//Checking if the answer is 0:
	if(sum1.size==0)
	{
		sum1.digit = (char*)malloc(1*(sizeof(char)));
		sum1.size=1;
		sum1.digit[0]='0';
	}

	//Allocating the sign to the result obtained:
	if(n1.sign==(-1))
	{
		sum1.sign=(-1);
	}

	return(sum1);
}

//Function to subtract two arbitrary precision numbers:
nstrng num_diff(nstrng n1, nstrng n2)
{
	nstrng sum1,n3;	
	int num1[255], num2[255], sum[255];
	int ii,I,J,K,L;
	int l1,l2;
	int N1=0,N2=0,ndif=0;
	l1=n1.size;
	l2=n2.size;
	
	//To check which string number is larger:
	if(l1>l2)
	{
		N1=1;
	}
	else if(l2>l1)
	{
		N2=1;
	}
	else if(l2==l1)
	{
		for(I=0;I<l1;I++)
		{
			if(n1.digit[I]!=n2.digit[I])
			{
				N1=((n1.digit[I]-n2.digit[I])>0) ? 1:(-1);
				break;
			}
		}
	}
	
	//If the signs are different make a third positive string number and then adding them:
	if(n1.sign!=n2.sign)
	{
		if(n1.sign==(-1))
		{
			n3.digit=(char*)malloc((n1.size)*sizeof(char));
			n3.size=n1.size;
			n3.sign=1;
			n3.digit=n1.digit;
			sum1=num_add(n3,n2);
		}
		else
		{
			n3.digit=(char*)malloc((n2.size)*sizeof(char));
			n3.size=n2.size;
			n3.sign=1;
			n3.digit=n2.digit;
			sum1=num_add(n1,n3);
		}

		if(n1.sign==(-1))
		{
			sum1.sign=(-1);
		}
		else
		{
			sum1.sign=1;
		}

		return(sum1);
	}
	
	//Make both numbers of same size by adding zeroes infront of the smaller number:
	if(N1>=N2)
	{
		for (I=0;I<l1;I++)
		{
			num1[I] = n1.digit[I] - '0';
		}
 	
		for (I=0;I<l1;I++)
		{
			if(I<(l1-l2))
			{
				num2[I] = 0;
			}
			else
			{
				num2[I] = n2.digit[I-(l1-l2)] - '0';
			}
		}
 	}
	else
	{
		for (I=0;I<l2;I++)
		{
			if(I<(l2-l1))
			{
				num2[I] = 0;
			}
			else
			{
				num2[I] = n1.digit[I-(l2-l1)] - '0';
			}
		}	
		for (I=0;I<l2;I++)
		{
			num1[I] = n2.digit[I] - '0';
		}
	}
	
	//Giving l1 and l2 the larger value:
	l1=(l1>l2)?l1:l2;
	l2=(l1>l2)?l1:l2;

	int carry = 0;
	int k = 0;
	int i = l1 - 1;
	int j = l2 - 1;
	for (; i >= 0 && j >= 0; i--, j--, k++) 
 	{
		if((num1[i]<=0)&&(num2[i]!=0))
		{
			num1[i]=10+num1[i];
			num1[i-1]=num1[i-1]-1;
		}
		
		if(num1[i]<num2[j])
		{
			num1[i]=num1[i]+10;
			num1[i-1]=num1[i-1]-1;
		}

		sum[k] = (num1[i] - num2[j]);
		
	}
	
	//check if the answer cointains any leading zeroes:
	K=k;
	L=0;
	for (k--; k >= 0; k--)
	{
		if(sum[k]==0)
		{
			L=L+1;
		}
		else
		{
			break;
		}
	}

	//allocate the required size to the resultant:
	K=K-L;
	k=K;
	sum1.digit = (char*)malloc(K*(sizeof(char)));

	for (k--; k >= 0; k--)
	{
		sum1.digit[K-(k+1)]='0'+sum[k];
	}
	sum1.size=K;
	sum1.sign=1;
	
	if(sum1.size==0)
	{
		sum1.digit = (char*)malloc(1*(sizeof(char)));
		sum1.size=1;
		sum1.digit[0]='0';
	}
	
	//Giving the sign to the result obtained:
	if((N2>N1)&&(n1.sign==1))
	{
		sum1.sign=(-1);
	}
	if((N1>N2)&&(n1.sign==(-1)))
	{
		sum1.sign=(-1);
	}

	return(sum1);
}

//multiplication of two arbitrary precision numbers:
nstrng num_mult(nstrng n1, nstrng n2)
{
	nstrng sum1;
	int a[100],b[100],s;
	int ans[200]={0};
	int i,j,tmp,I;
	char s1[101],s2[101];

	int l1 = strlen(n1.digit);
	int l2 = strlen(n2.digit);

	for(i = l1-1,j=0;i>=0;i--,j++)
    	{
        	a[j] = n1.digit[i]-'0';
    	}
	
	for(i = l2-1,j=0; i>=0; i--, j++)
    	{
        	b[j] = n2.digit[i]-'0';
    	}

	for(i = 0;i < l2; i++)
    	{
        	for(j = 0;j < l1; j++)
        	{
            		ans[i+j] += b[i]*a[j];
        	}
    	}
	
	for(i = 0;i < l1+l2;i++)
    	{
        	tmp = ans[i]/10;
        	ans[i] = ans[i]%10;
        	ans[i+1] = ans[i+1] + tmp;
    	}
	
	for(i = l1+l2; i>= 0;i--)
    	{
        	if(ans[i] > 0)
		break;
    	}
	
	I=i;
	sum1.digit = (char*)malloc(I*(sizeof(char)));

	for(;i >= 0;i--)
    	{
        	sum1.digit[I-i]='0'+ans[i];
    	}

	sum1.size=I+1;

	//giving the required sign to the resultant
	if(n1.sign!=n2.sign)
	{
		sum1.sign=(-1);
	}
	else
	{
		sum1.sign=1;
	}
	
	//checking if the answer is zero:
	if(sum1.size==0)
	{
		sum1.digit = (char*)malloc(1*(sizeof(char)));
		sum1.size=1;
		sum1.digit[0]='0';
		sum1.sign=1;
	}

	return (sum1);
}

//To divide a string number by an integer:
strdiv num_div(nstrng n1, int d)
{
	nstrng D;
	strdiv res;
	int I,K,q,r,qp,l1,l2,lq;
	int N1=0,N2=0;
	
	l1=n1.size;
	
	q=0; r=0; I=0; qp=0; lq=0;

	while((q<d)&&(I<l1))
	{
		K=0;
		while((q<d)&&(I<l1))
		{
			q=(10*q)+(n1.digit[I]-'0');
			I++;
			K++;
			if(q==0)
			{
				break;
			}
			
		}
		if(q<d)
		{
			r=q;
			qp=(10*qp);
			lq=lq+1;
		}
		else
		{
			for(K=1;K<=9;K++)
			{
				if(q<=(d*K))
				{
					if(q==(d*K))
					{
						K++;
					}
					break;
				}
			}
			K=K-1;
			r=(q-(d*K));
			qp=(10*qp)+K;
			lq=lq+1;
			q=r;
		}
	}
	
	res.r=q;
	lq=lq-1;
	D.sign=n1.sign;
	D.digit=(char*)malloc(lq*(sizeof(char)));
	for(I=0;I<=lq;I++)
	{
		D.digit[lq-I]= '0' + (qp%10);
		qp=qp/10;
	}
	D.size=lq+1;
	res.d=D;

	return(res);
}

//function to create a rational number in reduced form
Rational redRat(nstrng n, nstrng d)
{
	Rational rat;
	int l1,l2,I,i1=0,i2=0,i,r1,r2;
	strdiv R1,R2;
	
	//making the denominator positive
	if(d.sign==(-1))
	{
		n.sign = (-1)*(n.sign);
	}
	d.sign = 1;

	//if num is 0 making the den 1 for proper calculation:
	if (n.digit[0]=='0')
	{
		rat.num.digit=(char*)malloc(1*sizeof(char));
		rat.den.digit=(char*)malloc(1*sizeof(char));

		rat.num.digit[0] = '0';
		rat.num.size=1;
		rat.num.sign=1;

		rat.den.digit[0] = '1';
		rat.den.size=1;
		rat.den.sign=1;
		return rat;
	}

	//checking if the den is 0:
	if (d.digit[0]=='0')
	{
		printf("ERROR : Zero in denominator\n");
		exit(1);
	}	

	//to reduce the rational number to its smallest form:
	l1=n.size;
	l2=d.size;
    
	for(I=0;I<l1;I++)
	{
		i1=(10*i1)+(n.digit[I]-'0');
	}
	
	for(I=0;I<l2;I++)
	{
		i2=(10*i2)+(d.digit[I]-'0');
	}

	I=(i1>=i2)?i2:i1;
        
	if ((i1>1)||(i2>1))
	{
		for(i=I; i>=1; i--)
		{
			R1=num_div(n,i);
			R2=num_div(d,i);
			r1=R1.r;
			r2=R2.r;
			if ((r1==0)&&(r2==0))
			{
				n = R1.d;
				d = R2.d;
			}
		}
	}
	
	rat.num=n;
	rat.den=d;
	return (rat);
}

//function to print any rational number:
void printRat(Rational R)
{
	print_num(R.num);
	printf("/");
	print_num(R.den);
}

//function to add two rational number:
Rational addRat( Rational R1, Rational R2)
{
	return redRat((num_add((num_mult(R1.num,R2.den)),(num_mult(R2.num,R1.den)))),(num_mult(R1.den,R2.den)));
}

//function to subtract two rational number:
Rational subRat( Rational R1, Rational R2)
{
	return redRat((num_diff((num_mult(R1.num,R2.den)),(num_mult(R2.num,R1.den)))),(num_mult(R1.den,R2.den)));
}

//function to multiply two rational number:
Rational mutRat( Rational R1, Rational R2)
{
	return redRat((num_mult(R1.num,R2.num)),(num_mult(R1.den,R2.den)));
}

//function to divide two rational number:
Rational divRat( Rational R1, Rational R2)
{
	return redRat((num_mult(R1.num,R2.den)),(num_mult(R1.den,R2.num)));
}

//function to enter rational numbers in a matrix:
int readMatrix(Rational **mat, int size)
{
	int i,j;
	printf("\n");
	printf("Enter %dx%d matrix : \n", size, size);
	for(i=0; i<size; i++)
	{
		for(j=0;j<size;j++)
		{
			nstrng n1,n2;
			printf("-------- Enter Element[%d,%d]\n",(i+1),(j+1));
			printf("Num = ");
			n1=read_num();
			printf("Den = ");
			n2=read_num();
			mat[i][j] = redRat(n1,n2);
		}
	}
	printf("\n============================================");
	printf("\n============================================\n\n");
	return 0;
}

//function to display a matrix:
int displayMatric(Rational **mat,int size)
{
	int i,j;
	for(i=0; i<size; i++)
	{
		for(j=0;j<size;j++)
		{
			printRat(mat[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n============================================");
	printf("\n============================================\n\n");
	return 0;
}

//function to create a sub matrix by removing the specific row and column:
Rational** subMatrix( Rational **mat, int size, int row, int column)
{
	int i, j, I=0, J=0;
	Rational **subMat;
	Rational det;

	subMat = (Rational **) malloc((size-1)*(sizeof(Rational *)));

	for(i=0; i<(size-1); i++)
	{
		subMat[i] = (Rational *) malloc((size-1)*(sizeof(Rational)));
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
	
}

//function to calculate the determinant of a matrix:
Rational determinant(Rational **mat, int size)
{
	int i=0, j, I;
	nstrng n,d;
	Rational det;

	n.digit=(char*)malloc(1*sizeof(char));
	d.digit=(char*)malloc(1*sizeof(char));

	//initialising det by giving it +0 or +1 value:
	n.size=1;
	n.sign=1;
	n.digit[0]='0';
	det.num = n;
	
	d.size=1;
	d.sign=1;	
	d.digit[0]='1';
	det.den = d;

	if(size==2)
	{
		return(subRat((mutRat(mat[0][0],mat[1][1])),(mutRat(mat[0][1],mat[1][0]))));
	}

	else if(size==1)
	{
		return(mat[0][0]);
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
			
			if(I==-1)
			{
				det = subRat(det,(mutRat((mat[i][j]),(determinant((subMatrix(mat,size,i,j)),(size-1))))));
			}
			else
			{
				det = addRat(det,(mutRat((mat[i][j]),(determinant((subMatrix(mat,size,i,j)),(size-1))))));
			}
			
		}
		return (det);
	}
}

//function to create the inverse of a matrix(if it exists):
Rational** inverse(Rational **mat, int size)
{
	int i, j, I;
	Rational det, value; 
	Rational **inv;

	det = determinant(mat,size);

	inv = (Rational **) malloc(size*(sizeof(Rational *)));
	for(i=0; i<size; i++)
	{
		inv[i] = (Rational *) malloc(size*(sizeof(Rational)));
	}
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			I = ((i+j)%2==0)?1 : (-1);
			
			value = determinant((subMatrix(mat,size,j,i)),(size-1));
			
			if (I==-1)
			{
				value.num.sign = (-1)*value.num.sign;
			}
			
			value = divRat(value,det);
			inv[i][j] = redRat(value.num,value.den);
		}
	}
	return (inv);
}