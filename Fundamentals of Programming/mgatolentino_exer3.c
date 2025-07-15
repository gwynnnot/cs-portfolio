// MARY GWYNETH A. TOLENTINO
// CMSC 21 CD-2L
// C program that uses functions to create an ATM program

#include <stdio.h>

// function prototypes
float withdraw(float amount, float current_bal);
float deposit(float amount, float current_bal);
int pin_Check(int pin);

void balance_Check(float current_bal)
{
	printf("Current Balance: %.2f\n", current_bal);
}

int main()
{
	int pin = 1234,choice;	 		//variable declarations
	float current_bal = 0,amount;
	char name[20] = "savings";
	
	printf("\n*********************\n");
	printf("WELCOME TO MAZE BANK!\n");
	printf("*********************\n");
	
	do
	{	
		printf("\n=== MENU ===");	
		printf("\n[1] Check Balance");
		printf("\n[2] Deposit");
		printf("\n[3] Withdraw");
		printf("\n[4] Change PIN");
		printf("\n[5] Set Account Name");
		printf("\n[6] End Transaction");
		printf("\n\nPlease enter your choice: ");
		scanf("%i", &choice);
	
	switch (choice)
	{
	case 1:
		if (pin_Check(pin) == 1)	//checks if PIN is correct before proceeding
		{
			printf("\nAccount Name: %s\n", name);
			balance_Check(current_bal);	//checks balance
		}
		break;
	
	case 2:
		if (pin_Check(pin) == 1)
		{
			printf("\nDeposit amount: ");
			scanf("%f",&amount);
			current_bal = deposit(amount,current_bal); //calls deposit function
		}
		break;

	case 3:
		if (pin_Check(pin) == 1)
		{
			printf("\nWithdraw amount: ");
			scanf("%f",&amount);
    	    current_bal = withdraw(amount,current_bal); //calls withdraw function
		}
		break;

	case 4:
		if (pin_Check(pin) == 1)
		{
			printf("\nNew PIN: ");
			scanf("%i", &pin);
			printf("Your new PIN is %i.\n", pin);
		}
		break;

	case 5:
		if (pin_Check(pin) == 1)
		{
			printf("\nNew Account Name: ");
			scanf("%s", name);
			printf("Your new account name is %s.\n", name);
		}
		break;

	case 6:
		break;
		
	default:
		printf("Try again!\n");
		break;
	
	}// end of switch
	
	} while (choice!=6);
	printf("You ended this transaction. Goodbye!\n");
	
	return 0;
	
}// end of main

// check PIN function
int pin_Check(int pin)
{
    int attempt = 0,user;
    
    printf("\n=== Please enter your 4-digit PIN ===\n");

    while (attempt < 3) 	//allows only 3 attempts
    {
        printf("User: ");
        scanf("%d", &user);
        if (user == pin) {
            return 1;       //returns non-zero if PIN is correct 
        } else {
            attempt++;
            printf("Incorrect PIN. Please Try Again!\n");
        }
    }// end of while loop
    printf("\nToo many incorrect PIN attempts. Exiting...\n");

    return 0;

}// end of PIN check

// deposit function
float deposit(float amount, float current_bal)
{
	current_bal = current_bal + amount;
	printf("\nYour deposited amount is %.2f.\n", amount);
	return current_bal;
}

// withdraw function
float withdraw(float amount, float current_bal)
{
    if (amount <= current_bal)
    {
        current_bal = current_bal - amount;
        printf("\nYour withdrawn amount is %.2f.\n", amount);
    }
    else
    {
        printf("\nYou have exceeded the withdrawable amount. Please Try Again!\n");
    }
    return current_bal;
}