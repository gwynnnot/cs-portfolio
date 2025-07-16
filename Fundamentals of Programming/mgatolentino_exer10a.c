// MARY GWYNETH A. TOLENTINO
// CD-2L
// C program that implements a ticket reservation system using structures

#include <stdio.h>
#include <string.h>

/*
1 add event
2 view all events
3 edit
4 delete
*/

typedef struct event
{
	int ID;
	char eventTitle[30];
	char eventArtist[30];
	char dateANDtime[20];
	float price;
	int stock;
	
} eventDetails;


void addEvent(struct event *details, int index)
{
	printf("Enter event id: ");
	scanf("%d", &details[index].ID);
	
	printf("Enter event title: ");
	scanf("%s", details[index].eventTitle);
	
	printf("Enter event artist: ");
	scanf("%s", details[index].eventArtist);
	
	printf("Enter date and time: ");
	scanf("%s", details[index].dateANDtime);
	
	printf("Enter ticket price: ");
	scanf("%f", &details[index].price);
	
	printf("Enter stock: ");
	scanf("%d", &details[index].stock);

	printf("\nSuccessfully added event!\n");
	
} // End of void

void viewAll(struct event *details, int index) 
{
	for(int i=1; i < index; i++) 
	{
		printf("\nEvent ID: %d\n", details[i].ID);
		printf("Event Title: %s\n", details[i].eventTitle);
		printf("Artist: %s\n", details[i].eventArtist);
		printf("Date and Time: %s\n", details[i].dateANDtime);
		printf("Ticket Price: %f\n", details[i].price);
		printf("Stock: %d\n", details[i].stock);
	}
}

void buyTicket(struct event *details, int index) 
{
	for(int i=1; i < index; i++) 
	{
		printf("[%d] %s (%s) - %.2f\tStock: %d\n", i, details[i].eventTitle, details[i].eventArtist, details[i].price, details[i].stock);
	}
}

void editEvent(struct event *details, int i) 
{
	int id;
	
	printf("Enter event id: ");
	scanf("%d", &id);
	
	printf("Enter new date and time: ");
	scanf("%s", details[id].dateANDtime);

	printf("Enter new price: ");
	scanf("%f", &(details[id].price));
	
	printf("Enter new stock: ");
	scanf("%d", &(details[id].stock));
}

void saveEvents(struct event *details, int count) 
{
	FILE *fp = fopen("events.txt", "w");
	fprintf(fp, "Counter: %d\n", count);
	
	for(int i=1; i < (count); i++) 
	{
		fprintf(fp, "ID: %d\n", details[i].ID);
		fprintf(fp, "Title: %s\n", details[i].eventTitle);
		fprintf(fp, "Artist: %s\n", details[i].eventArtist);
		fprintf(fp, "D&T: %s\n", details[i].dateANDtime);
		fprintf(fp, "Price: %f\n", details[i].price);
		fprintf(fp, "Stock: %d\n\n", details[i].stock);
	}
	printf("Successfully saved data!\n");

	fclose(fp);
}

void loadEvents(struct event *details, int *count) 
{
	FILE *fp = fopen("events.txt", "r");
	if (fp==NULL) return;
	
	fscanf(fp, "Counter: %d\n", count);
	
	for(int i=1; i < (*count); i++) 
	{
		fscanf(fp, "ID: %d\n", &details[i].ID);
		fscanf(fp, "Title: %s\n", details[i].eventTitle);
		fscanf(fp, "Artist:%s\n", details[i].eventArtist);
		fscanf(fp, "D&T: %s\n", details[i].dateANDtime);
		fscanf(fp, "Price: %f\n", &details[i].price);
		fscanf(fp, "Stock: %d\n\n", &details[i].stock);
	}
	printf("Successfully loaded data!\n");

	fclose(fp);
}

int main() 
{
	struct event details[20];
	int choice;
	int index = 1;
	
	
	loadEvents(details,&index);
	
	while(1) 
	{
		printf("\n===============================\n");
		printf("   TICKET RESERVATION SYSTEM    \n");
		printf("===============================\n");
		printf("[1] Add Event Details\n");
		printf("[2] Buy Ticket\n");
		printf("[3] Edit Event Details\n");
		printf("[4] Delete Event\n");
		printf("[5] View All Events\n");
		printf("[6] View All Customers\n");
		printf("[7] Exit\n");

		printf("\nEnter choice: ");
		scanf("%d", &choice);

		printf("\n");

		if (choice == 1) 
		{
			addEvent(details,index);
			index++;
		}
		
		else if (choice == 2) 
		{
			printf("\n------- EVENTS AVAILABLE -------\n");
			buyTicket(details,index);
		}  
		
		else if (choice == 3) 
		{
			editEvent(details,index); 
		} 
		
		else if (choice == 4) 
		{
			break;
		}
		
		else if (choice == 5) 
		{
			printf("------- LIST OF EVENTS -------\n");
			viewAll(details,index);
		} 
		
		else if (choice == 6) 
		{
			break;
		}
		
		else if (choice == 7) 
		{
			break;
		}
		
		

		printf("\n");
	}
	saveEvents(details,index);
}
