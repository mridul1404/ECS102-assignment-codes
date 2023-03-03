/* 
Mridul Sharma
21176 
lab week 9
inverse of rational number matrix
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct rational{
	int num, den;
};
int hcf(int x, int y){
		int i, hcf;
		for(i = 1; i <= x || i <= y;i++){
			if (x % i == 0 && y % i == 0)
				hcf = i;
		}
		return hcf;    
}
struct rational sim(struct rational x){
			int a, b, c;
			a = hcf(x.num, x.den);
			b = x.num/a;
			c = x.den/a;
			x.num = b;
			x.den = c;
		return x;
}
			
	
struct rational my_sum(struct rational r1, struct rational r2){
		struct rational sum;
		sum.num = (r1.num * r2.den) + (r2.num * r1.den);
		sum.den = (r1.den * r2.den);
		sim(sum);
		return sum ;
}

struct rational my_prod(struct rational r1, struct rational r2){
		struct rational prod;
		prod.num = r1.num * r2.num;
		prod.den = r1.den * r2.den;
		sim(prod);
		return prod;
}
void printmat(struct rational **, int);
void createsubmat(struct rational **mat, struct rational **submat, int n , int ii, int jj){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i < ii && j < jj)
				submat[i][j] = mat[i][j];
			else if(i > ii && j < jj)
				submat [i-1][j] = mat[i][j];
			else if(i < ii && j > jj)
				submat [i][j-1] = mat[i][j];
			else if(i > ii && j > jj)
				submat [i-1][j-1] = mat[i][j];
		}
	}
}

void freemat(struct rational **mat, int n){
	for (int i = 0; i < n; i++){ free(mat[i]);}
	free(mat);
}
struct rational determinant(struct rational **mat, int n){
	struct rational det;
	det.num = 0, det.den = 1;
	struct rational **submat;
	int i, j;
	if (n == 1){return mat[0][0];}
	else if (n > 1){
	for(i = 0; i < n; i++){
		submat = (struct rational **) malloc((n-1)*sizeof(struct rational *));
		for (j = 0; j < n-1; j++)
			submat[j] = (struct rational *) malloc((n-1)* sizeof(struct rational));
		createsubmat(mat, submat, n, i, 0);
		printmat(submat, n-1);
		struct rational k[i][0];
		struct rational pw;
		pw.num = pow(-1,i); pw.den = 1;
		k[i][0] = my_prod(mat[i][0], pw);	
		det = my_sum(det, my_prod(k[i][0], determinant(submat, n-1)));
		freemat(submat, n-1);
		}
	}
	else{
		printf("\nnegative n\n");
	}
	return det;
}

void printmat(struct rational ** mat, int n){
	printf("\t\t\t\n");
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%d/%d\t", mat[i][j].num, mat[i][j].den);
		}
	printf("\n");
	}
	printf("\t\t\t\n");
}
