// MARY GWYNETH A. TOLENTINO
// CMSC 21 CD-2L
// C program that computes GWA and total units taken by a student

#include <stdio.h>

int main() {
	int U1, U2, U3, U4, U5, total_units;
	float G1, G2, G3, G4, G5, GWA;		//variable declarations
	
	printf("\nGWA Calculator\n");
	
	printf("Enter units: ");
	scanf("%d", &U1);
	printf("Enter grade: ");
	scanf("%f", &G1);
;	
	printf("Enter units: ");
	scanf("%d", &U2);
	printf("Enter grade: ");
	scanf("%f", &G2);
	
	printf("Enter units: ");
	scanf("%d", &U3);
	printf("Enter grade: ");
	scanf("%f", &G3);
	
	printf("Enter units: ");
	scanf("%d", &U4);
	printf("Enter grade: ");
	scanf("%f", &G4);
	
	printf("Enter units: ");
	scanf("%d", &U5);
	printf("Enter grade: ");
	scanf("%f", &G5);
	
	total_units = (U1 + U2 + U3 + U4 + U5);

	GWA = ((G1*U1) + (G2*U2) + (G3*U3) + (G4*U4) + (G5*U5))/ total_units;
	
	
	printf("\nYour GWA is: %f \n", GWA);
	printf("Total units: %d \n", total_units);
	
	printf("\nCongrats! You survived the sem :)\n");
	
	
	
	return 0;
}
 
