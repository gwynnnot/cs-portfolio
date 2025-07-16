// MARY GWYNETH A. TOLENTINO
// CD-2L
// C program that implements a ticket reservation system using structures

#include <stdio.h>
#include <string.h>	
#include <stdlib.h>	// for malloc functions

/*
1 add event
2 print all
3 save
4 load
*/

typedef struct event
{
	int eventID;
	char eventTitle[30];
	char eventArtist[30];
	char dateANDtime[20];
	float price;
	int stock;
	
	struct event *next;
	
} eventDETAILS;


// Adds new instance of event
void addEvent(eventDETAILS **head)
{
	eventDETAILS *old = *head;
	eventDETAILS *new = NULL;
	
	new = (eventDETAILS*) malloc(sizeof(eventDETAILS));	
	
	printf("Enter event id: ");
	scanf("%d", &new->eventID);
	
	while (old != NULL)
	{
		while (new->eventID == old->eventID)
		{
			printf("\nEvent ID already exists.\nEnter another ID: ");
			scanf("%d", &new->eventID);
		}
		old = old->next;
	} 
	
	printf("Enter event title: ");
	scanf("%s", new->eventTitle);
	
	printf("Enter event artist: ");
	scanf("%s", new->eventArtist);
	
	printf("Enter date and time: ");
	scanf("%s", new->dateANDtime);
	
	printf("Enter ticket price: ");
	scanf("%f", &new->price);
	
	printf("Enter stock: ");
	scanf("%d", &new->stock);
	
	// Sorted by eventID in ascending order
	if ((*head) == NULL || ((*head) != NULL && new->eventID < (*head)->eventID)) // insert at head
	{
		new->next = (*head);
		(*head) = new;
	}
	else // insert at the middle or end
	{
		eventDETAILS *temp = (*head);
		while(temp->next != NULL && temp->next->eventID < new->eventID)
		{
			temp = temp->next;
		}
		
		new->next = temp->next;
		temp->next = new;
	}
	
	printf("\nSuccessfully added event!\n");
	
} // End of adding event


// Prints all event details
void printAll(eventDETAILS *head, int count) 
{
	for(eventDETAILS *temp = head; temp != NULL; temp = temp->next)
	{
		printf("\nEvent ID: %d\n", temp->eventID);
		printf("Event Title: %s\n", temp->eventTitle);
		printf("Artist: %s\n", temp->eventArtist);
		printf("Date and Time: %s\n", temp->dateANDtime);
		printf("Ticket Price: %.2f\n", temp->price);
		printf("Stock: %d\n", temp->stock);
	}
}

// Saves event details to events.txt
void saveEvents(eventDETAILS *head, int count)
{
	FILE *fp = fopen("events.txt", "w");
	eventDETAILS *temp = (eventDETAILS*) malloc (sizeof(eventDETAILS));	
	
	fprintf(fp, "N Counter: %d\n\n", count);
	
	for(eventDETAILS *temp = head; temp != NULL; temp = temp->next)
	{
		fprintf(fp, "ID: %d\n", temp->eventID);
		fprintf(fp, "Title: %s\n", temp->eventTitle);
		fprintf(fp, "Artist: %s\n", temp->eventArtist);
		fprintf(fp, "D&T: %s\n", temp->dateANDtime);
		fprintf(fp, "Price: %.2f\n", temp->price);
		fprintf(fp, "Stock: %d\n\n", temp->stock);
	}
	
	printf("Successfully saved data!\n");

	fclose(fp);
}

// Loads data from events.txt
void loadEvents(eventDETAILS **head, int *count)
{
	int i;
	
	FILE *fp = fopen("events.txt", "r");
	if (fp == NULL) return;
	
	fscanf(fp, "N Counter: %d\n\n", count);
	/*
	for (i = 0; i < *count; i++)
	{
		eventDETAILS *temp = NULL;
		temp = (eventDETAILS *) malloc(sizeof(eventDETAILS));
		
		fscanf(fp, "ID: %d\n", &temp->eventID);
		fscanf(fp, "Title: %s\n", temp->eventTitle);
		fscanf(fp, "Artist: %s\n", temp->eventArtist);
		fscanf(fp, "D&T: %s\n", temp->dateANDtime);
		fscanf(fp, "Price: %f\n", &temp->price);
		fscanf(fp, "Stock: %d\n\n", &temp->stock);
			
		temp->next = *head;
		*head = temp;		
	*/	
		// Load file in ascending order	
	for (i = 0; i < *count-1; i++)
		{	
			eventDETAILS *temp = NULL;
			temp = (eventDETAILS *) malloc(sizeof(eventDETAILS));	
			
			//temp->next = (eventDETAILS *) malloc(sizeof(eventDETAILS));
			//temp = temp->next;
			
			fscanf(fp, "ID: %d\n", &temp->eventID);
			fscanf(fp, "Title: %s\n", temp->eventTitle);
			fscanf(fp, "Artist: %s\n", temp->eventArtist);
			fscanf(fp, "D&T: %s\n", temp->dateANDtime);
			fscanf(fp, "Price: %f\n", &temp->price);
			fscanf(fp, "Stock: %d\n\n", &temp->stock);
		}
	}
	
	printf("Successfully loaded data!\n");
	
	fclose(fp);
}

int main() 
{
	struct event *head = NULL;
	int choice;
	int eventCount = 0;

	loadEvents(&head,&eventCount);
	
	while(1) 
	{
		printf("\n=======================\n");
		printf("   TICKET RESERVATION     \n");
		printf("=======================\n");
		printf("[1] Add Event Details\n");
		printf("[2] View All Events\n");
		printf("[3] Exit\n");

		printf("\nEnter choice: ");
		scanf("%d", &choice);

		printf("\n");

		if (choice == 1) 
		{
			if (eventCount == 10 || eventCount > 10)
				printf("Can only store up to 10 events.\n");
			else 
			{	
				addEvent(&head);
				eventCount++;
			}
		}		
		else if (choice == 2) 
		{
			if (eventCount < 1) 
				printf("Nothing to print! There are no events available.\n");
			else printAll(head,eventCount);
		} 
		else if (choice == 3) 
		{
			if (eventCount < 1)
			{
				printf("There are no events to be saved.\n");
				break;
			}
			else
			{
				saveEvents(head,eventCount);
				break;
			}
		}
		else
		{
			printf("Invalid choice. Please try again!\n");
		}

		printf("\n");
	}
}
