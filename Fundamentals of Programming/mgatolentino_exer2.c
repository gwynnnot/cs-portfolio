// MARY GWYNETH A. TOLENTINO
// CD-2L
// C program that will compute the BMI of a given height and weight

#include <stdio.h>

int main() {
	int choice;
	float kg,cm,m,bmi,lbs,ft,in,height;
	char ans;				//variable declarations
	
	do
	{
		printf("\nBMI CALCULATOR");	//start menu
		printf("\n[1] Measure in metric");
		printf("\n[2] Measure in standard");
		printf("\n[3] Exit\n");
		printf("\nPlease enter your choice: ");
		scanf("%i", &choice);
	
	switch (choice) {//start
	case 1:
		printf("\n=== METRIC SYSTEM ===");
		printf("\nEnter weight in kilograms: ");
		scanf("%f", &kg);
		printf("Enter height in centimeters: ");
		scanf("%f", &cm);
		
		m = cm/100;	//convert centimeters to meters
		bmi = kg/(m*m);	
		
		if (bmi < 18.5)
		printf("\nYour BMI is: %.2f\nBMI Category: Underweight\n", bmi);
		else if (bmi >= 18.5 && bmi < 25)
		printf("\nYour BMI is: %.2f\nBMI Category: Normal weight\n", bmi);
		else if (bmi >= 25 && bmi < 30)
		printf("\nYour BMI is: %.2f\nBMI Category: Overweight\n", bmi);
		else
		printf("\nYour BMI is: %.2f\nBMI Category: Obesity\n", bmi);
		break;

	case 2:
		printf("\n=== STANDARD SYSTEM ===");
		printf("\nEnter weight in pounds: ");
		scanf("%f", &lbs);
		printf("Enter height in feet: ");
		scanf("%f", &ft);
		printf("Enter height in inches: ");
		scanf("%f", &in);
		
		height = (ft*12)+in;
		bmi = (lbs/(height*height))*703;
		
		
		if (bmi < 18.5)
		printf("\nYour BMI is: %.2f\nBMI Category: Underweight\n", bmi);
		else if (bmi >= 18.5 && bmi < 25)
		printf("\nYour BMI is: %.2f\nBMI Category: Normal weight\n", bmi);
		else if (bmi >= 25 && bmi < 30)
		printf("\nYour BMI is: %.2f\nBMI Category: Overweight\n", bmi);
		else
		printf("\nYour BMI is: %.2f\nBMI Category: Obesity\n", bmi);
		break;
	
	case 3:
		printf("\n=== EXITING ===\nAre you sure? [y/n] ");
		scanf(" %c", &ans);
		break;
		
	default:
		printf("Try again!\n");
		break;
	
	}// end of switch
	
	
	} while (ans != 'y');
	printf("\nI'm off. Good bye!\n");
	
	return 0;
}
		
