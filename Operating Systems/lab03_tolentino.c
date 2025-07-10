/**
 	lab03_tolentino.c
	MGATolentino, CMSC125 1st Sem 24-25
 **/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    while(1) 
    {
        pid_t pid1; //pid_t data type represents process IDs.
        int i = 0;
        char choice[100];
        char array[50][50];

        printf("\n");
        printf("matolentino@cmsc125b5l ~ ");
        scanf("%[^\n]%*c", choice); //https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/

        //split the string with " " as delimiter
        char *token = strtok(choice, " "); 

        while (token!= NULL)
        {
            strcpy(array[i], token);
            i++;
            token = strtok(NULL, " ");
        }

        // TEST
        // printf("index = %d\n", i); 
        // printf("command = %s", array[0]); 
        // printf("command = %s", array[1]); 

        // check if choice is exit
        if (strcmp(choice, "exit") == 0)
        {
            printf("Program terminated.\n");
            break;
        }

        else
        {
            pid1 = fork();
            
            if (pid1 == 0)
            {
                if(i == 1) 
                {
                    // check if the call to execlp is unsuccessful.
                    if(execlp(array[0], array[0], NULL) == -1)
                        printf("%s: command not found\n", array [0]);
                }
                else if (i == 2)
                { 
                    // execlp(array[0], array[0], array[1], NULL)
                    if(execlp(array[0], array[0], array[1], NULL) == -1)
                        printf("%s %s: command not found\n", array [0], array [1]);
                }
                else if (i == 3)
                { 
                    // execlp(array[0], array[0], array[1], array[2], NULL)
                    if(execlp(array[0], array[0], array[1], array[2], NULL) == -1)
                        printf("COMMAND NOT FOUND\n");
                }
                else printf("ERROR");
            }
            else if (pid1 > 0)
            {   // parent waits for the child(ren)
                wait(NULL);
            }
            else printf("ERROR");
        }
    }

    


    return 0;
}