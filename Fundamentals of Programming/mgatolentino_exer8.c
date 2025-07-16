// MARY GWYNETH A. TOLENTINO
// CD-2L
// C program for a simple transposition cipher

#include <stdio.h>
#include <string.h>

void transpose(char *plaintext, char *ciphertext, int key)
{
    int i,j,n = strlen(plaintext);
    int rowsize = (n + key - 1) / key;

    char grid[rowsize][key];    // Create a 2D array

    // Start grid with empty spaces
    for (i = 0; i < rowsize; i++)
    {
        for (j = 0; j < key; j++)
        {
            grid[i][j] = ' ';
        }
    }

    // Fill grid with plaintext characters
    int counter = 0;
    for (i = 0; i < rowsize; i++)
    {
        for (j = 0; j < key; j++)
        {
            if (counter < n)
            {
                grid[i][j] = plaintext[counter];
                counter++;
            }
            else break;
        }
    }

    // Print grid
    printf("\nIllustration:\n");
	for (int i = 0; i < rowsize; i++) 
	{
		for (int j = 0; j < key; j++) 
		{
        	printf(" %c |", grid[i][j]);
        }
        	printf("\n");
    }
    
    // Read characters in the grid to form an encrypted text 
    counter = 0;
    for (j = 0; j < key; j++)
    {
        for (i = 0; i < rowsize; i++)
        {
            ciphertext[counter] = grid[i][j];
            counter++;
        }
    }
    ciphertext[counter] = '\0';

}// End of transposition

int main()
{
    char plain[50], cipher[50];
    int key;

    printf("Enter the plaintext: ");
    scanf("%[^\n]s", plain);

    printf("Enter the key (number of columns): ");
    scanf("%i", &key);

    // Call the transpose function
    transpose(plain, cipher, key);

    // Print the encrypted text/ciphertext
    printf("\nCiphertext: %s\n", cipher);

    return 0;
    
}// End of main
