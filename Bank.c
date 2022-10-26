#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct Node Node;

struct Node{
	char name[50];
	char cardType[20];
	int priority;
	Node *next, *prev;
};

Node *front = NULL;
Node *rear = NULL;

Node* createNode(char* name, char* cardType, int priority){
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	strcpy(newNode->name, name);
	strcpy(newNode->cardType, cardType);
	newNode->priority = priority;
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

// Add new person to queue
void push(char* name, char* cardType, int priority){
	Node* temp = createNode(name, cardType, priority);
	
	if (front == NULL) {
		front = temp;
		rear = temp;
	} else {
		if (priority > front->priority) {
			temp->next = front;
			front->prev = temp;
			front = temp;
		} else if (priority <= rear->priority) {
			temp->prev = rear;
			rear->next = temp;
			rear = temp;
		} else {
			Node* curr = rear;
			while (curr->priority < priority) {
				curr = curr->prev;
			}
			
			temp->prev = curr;
			temp->next = curr->next;
			curr->next->prev = temp;
			curr->next = temp;
		}
	}
}

// Delete person from queue
void pop(){
	Node *temp = front;
	
	if (front == rear) {
		front = NULL;
		rear = NULL;
	} else {
		front = front->next;
		front->prev = NULL;
		free(temp);
	}
}

// Checks if queue is empty
bool isEmpty(){
	if (front == NULL) return true;
	else return false;
}

// Print menu display
void menu(){
	printf("Welcome to the Bank!\n");
	printf("1. Enter the queue\n");
	printf("2. View queue list\n");
	printf("3. Call the next person\n");
	printf("4. Exit\n");
}

// Checks if card type is valid or not
bool checkCardType(char* cardType) {
	if (strcmp(cardType, "Platinum") != 0 && strcmp(cardType, "Diamond") != 0 && strcmp(cardType, "Gold") != 0 && 
		strcmp(cardType, "Bronze") != 0 && strcmp(cardType, "Silver") != 0) {
			return false;
	}
	
	return true;
}

// Submenu for add
void add(){
	
	int priority;
	char name[50], cardType[20];
	
	printf("+---------------------------------------------+\n");
	printf("| Credit card type information                |\n");
	printf("+---------------------------------------------+\n");
	printf("| 1. Diamond                                  |\n");
	printf("| 2. Platinum                                 |\n");
	printf("| 3. Gold                                     |\n");
	printf("| 4. Silver                                   |\n");
	printf("| 5. Bronze                                   |\n");
	printf("+---------------------------------------------+\n");
	
	do {
		printf("Input name (min. 5 characters): ");
		scanf("%s", name);
		
		if (strlen(name) < 5) {
			printf("Name length must be more than 5 characters!\n\n");
		}
	} while (strlen(name) < 5);
	
	do {
		printf("Input credit card type: ");
		scanf("%s", cardType);
		
		if (!checkCardType(cardType)) {
			printf("Invalid card type!\n\n");
		}
	} while (!checkCardType(cardType));
	
	if (strcmp(cardType, "Diamond") == 0) priority = 4;
	else if (strcmp(cardType, "Platinum") == 0) priority = 3;
	else if (strcmp(cardType, "Gold") == 0) priority = 2;
	else priority = 1;
	
	push(name, cardType, priority);
	printf("\n\n%s has been added to the queue!\n", name);
	printf("Please wait for your name to be called...."); getch();
	
}

// Submenu for print
void print(){
	if (isEmpty()) {
		printf("Nobody's currently at the bank!\n");
	} else {
		int num = 1;
		char id = 'A';
		
		Node *curr = front;
		while (curr != NULL){
			printf("Queue No. %c%d\n", id, num);
			printf("Name\t: %s\n", curr->name);
			printf("Card\t: %s\n", curr->cardType);
			printf("\n");
			
			num++;
			if (num > 10) {
				id++;
				num = 1;
			}
			
			curr = curr->next;
		}
	}
	
	printf("\nPress enter to continue...");
	getch();
}

// Submenu for call
void call(){
	if (isEmpty()) {
		printf("Nobody's currently at the bank!\n");
	}
	else {
		printf("Calling %s...\n", front->name);
		printf("Thank you for coming!");
		
		pop();
	}
	
	printf("\nPress enter to continue...");
	getch();
}

int main(){
	
	int menuChoice;
	
	do {
		system("cls");
		menu();
		do{
			printf("Input: ");
			scanf("%d", &menuChoice); getchar();
		} while (menuChoice < 1 || menuChoice > 4);
		
		system("cls");
		switch(menuChoice) {
			case 1:
				add();
			 	break;
			case 2:
				print();
				break;
			case 3:
				call();
				break;
			case 4:
				break;
		}
	} while (menuChoice != 4);
	
	
	return 0;
}
