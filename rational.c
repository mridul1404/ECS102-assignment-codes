/* 
Mridul Sharma
21176 
lab week 9
rational number arithmetic
*/

#include<stdio.h>

struct rational{
	int num, den;
};

struct rational r1, r2;
int hcf(int x, int y){
		int i, hcf;
		for(i = 1; i <= x || i <= y;i++){
			if (x % i == 0 && y % i == 0)
				hcf = i;
		}
		return hcf;    
}
int sim(struct rational x){
			int a, b, c;
			a = hcf(x.num, x.den);
			b = x.num/a;
			c = x.den/a;
			x.num = b;
			x.den = c;
		printf("%d/%d\n", x.num, x.den);
}
			
	
void my_sum(struct rational r1, struct rational r2){
		struct rational sum;
		sum.num = (r1.num * r2.den) + (r2.num * r1.den);
		sum.den = (r1.den * r2.den);
		printf("sum = ");
		sim(sum);
		return ;
}
void my_diff(struct rational r1, struct rational r2){
		struct rational diff;
		if ((r1.num * r2.den) >= (r2.num * r1.den))
			diff.num = (r1.num * r2.den) - (r2.num * r1.den);
		else 
			diff.num = (r2.num * r1.den) - (r1.num * r2.den);
		diff.den = (r1.den * r2.den);
		printf("difference = ");
		sim(diff);
		return;
}
void my_prod(struct rational r1, struct rational r2){
		struct rational prod;
		prod.num = r1.num * r2.num;
		prod.den = r1.den * r2.den;
		printf("product = ");
		sim(prod);
		return;
}
void my_quot(struct rational r1, struct rational r2){
		struct rational quot;
		quot.num = r1.num * r2.den;
		quot.den = r2.num * r1.den;
		printf("quotient = ");
		sim(quot);
		return;
}

int main(){
	
	printf("Please enter the rational numbers in the form a/b c/d:\n");
	scanf("%d/%d %d/%d", &r1.num, &r1.den, &r2.num, &r2.den);
	printf("the rational numbers are %d/%d %d/%d\n", r1.num, r1.den, r2.num, r2.den);
	my_sum(r1, r2);
	my_diff(r1, r2);
	my_prod(r1, r2);
	my_quot(r1, r2);
	return 0;
}