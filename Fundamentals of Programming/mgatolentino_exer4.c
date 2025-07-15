// MARY GWYNETH A. TOLENTINO
// CD-2L
// C program that uses a recursive function to compute how much a population of n with an annual growth rate of r% grows after x years

#include <stdio.h>

float pop_Growth(float n, float r, int x) 
{
//	printf("%f,%f,%d\n",n,r,x);
	
	if (x==0)
	{
		return n;				//base case
	}
	else
	{
		return (pop_Growth(n+(n*r),r, x-1));	//recursive case
	}
}


/*

TESTING
x=4
n + (n*r) = n(4-1)

x=3
n(3) + ((n(1)*r)) = n(3-1)

x=2
n(2) + ((n(2)*r)) = n(3-1)

x=1
n(1) + ((n(3)*r)) = n(1-1)

x=0
return n

*/


int main()
{
	float n,y;
	int x;
	
	printf("Population (n): \n");
	scanf("%f", &n);
	
	printf("Growth Rate (y): \n");
	scanf("%f", &y);
	float r = y / 100.0;

	printf("Years (x): \n");
	scanf("%d", &x);
	
	printf("\nResult: \nAfter %d years at growth rate of %.2f, the population will be %f\n",x,r,pop_Growth(n,r,x));
	
	return 0;	
	
}// end of main
