// MARY GWYNETH A. TOLENTINO
// CD-2L
// C program that emulates an extended calculator

#include <stdio.h>

// function prototypes
void getAB(int *x, int *y);
void addAB(int *sum, int *x, int *y);
void subtractAB(int *diff, int *x, int *y);
void multiplyAB(int *prod, int *x, int *y);
void divideAB(int *div, int *x, int *y);
void moduloAB(int *mod, int *x, int *y);
void powerAB(int *pow, int *x, int *y);

int main()
{
	int a,b,option;
	int sum,diff,prod,div,mod,pow;
	
	printf("\nWelcome to the Good Calculator!\n");	
	
	do
	{
		printf("\n===============");
		printf("\n    OPTIONS    ");
		printf("\n===============");	
		printf("\n[1] Add");
		printf("\n[2] Subtract");
		printf("\n[3] Multiply");
		printf("\n[4] Divide");
		printf("\n[5] Modulo");
		printf("\n[6] Power");
		printf("\n[7] Exit");
		printf("\n\nPlease enter an option: ");
		scanf("%i", &option);
	
	switch (option)
	{
		case 1:
		getAB(&a,&b);
		addAB(&sum,&a,&b);
		printf("\nThe sum of the two numbers A and B is %d\n", sum);
		break;
			
		case 2:
		getAB(&a,&b);
		subtractAB(&diff,&a,&b);
		printf("\nThe difference of the two numbers A and B is %d\n", diff);
		break;
			
		case 3:
		getAB(&a,&b);
		multiplyAB(&prod,&a,&b);
		printf("\nThe product of the two numbers A and B is %d\n", prod);	
		break;
		
		case 4:
		getAB(&a,&b);
		divideAB(&div,&a,&b);	
		printf("\nThe quotient of the two numbers A and B is %d\n", div);	
		break;
			
		case 5:
		getAB(&a,&b);
		moduloAB(&mod,&a,&b);	
		printf("\nThe remainder of dividing A and B is %d\n", mod);	
		break;
		
		case 6:
		getAB(&a,&b);
		powerAB(&pow,&a,&b);	
		printf("\nThe answer of A raised to the power of B is %d\n", pow);	
		break;
		
		case 7:
	       	break;
	       	
	       	default:
	       	printf("That's not an option!\n");
		
	}// end of switch
	
	} while (option!= 7);
	printf("Goodbye!\n");
	
	return 0;
	
}// end of main


void getAB(int *x, int *y)
{
	printf("Enter number A: ");
	scanf("%d", x);
	printf("Enter number B: ");
	scanf("%d", y);
}

void addAB(int *sum, int *x, int *y)
{
	
	*sum = *x + *y;
}

void subtractAB(int *diff, int *x, int *y)
{
	*diff = *x - *y;
}

void multiplyAB(int *prod, int *x, int *y)
{
	*prod = *x * *y;	
}

void divideAB(int *div, int *x, int *y)
{
	*div = *x / *y;
}

void moduloAB(int *mod, int *x, int *y)
{
	*mod = *x % *y;
}

void powerAB(int *pow, int *x, int *y)
{
	int i;
	*pow = 1;
	
	for (i=1; i<=*y; i++)
	{
		*pow = *pow * *x;
	}
}
