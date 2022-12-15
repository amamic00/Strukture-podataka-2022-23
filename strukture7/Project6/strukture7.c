#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct _directory;
struct _stack;
typedef struct _directory* position;
typedef struct _stack* positionStack;

typedef struct _directory
{
	char name[MAX_LINE];
	position sibling;
	position child;
}directory;

typedef struct _stack
{
	position directory;
	positionStack next;
}stack;

int Menu(position root, positionStack head);
int MakeDirectory(position current);
position CreateNewDirectory(char* name);
position FindLastDirectory(position first);
int InsertAfter(position prev, position new);
position ChangeDirectory(position current);
int DeleteAfter(positionStack head);
int Push(positionStack head, position current);
position Pop(positionStack head);
int StackInsert(positionStack head, positionStack new);
int PrintDirectories(position first);
int NameCheck(position first, char* name);

int main() {
	directory root = { .name = ":C",.sibling = NULL,.child = NULL };
	stack head = { .directory = NULL,.next = NULL };

	int status = 0;

	Push(&head, &root);
	do
	{
		status = Menu(&root, &head);
	} while (status >= 0);

	return 0;
}

int Menu(position root, positionStack head)
{
	int choice = 0;
	position temp = NULL;
	position current = Pop(head);
	int status = 0;

	printf("Odaberite:\n1-md\n2-cd dir\n3-cd..\n4-dir\n5-exit\n");
	scanf(" %d", &choice);
	switch (choice) {
	case (1):
		status = MakeDirectory(current);
		return status;
		break;
	case (2):
		temp = ChangeDirectory(current);
		if (!temp)
			return 0;
		else
		{
			Push(head, temp);
			return status;
		}
		break;
	case (3):
		if (head->next->next == NULL)
			return 0;

		DeleteAfter(head);
		return 0;
		break;
	case (4):
		if (current->child == NULL)
		{
			printf("There aren't any directories.\n");
			return 0;
		}

		PrintDirectories(current->child);
		return 0;
		break;
	case(5):
		return -1;
		break;
	default:
		printf("Greska!");
		return 0;
		break;
	}
	
}

int MakeDirectory(position current)
{
	char name[MAX_LINE] = { 0 };
	position new = NULL;
	position prev = NULL;

	printf("Upisite ime nove datoteke: ");
	scanf(" %s", name);

	if (NameCheck(current->child, name))
	{
		printf("Datoteka s tim imenom vec postoji.\n");
		return 0;
	}

	new = CreateNewDirectory(name);
	if (!new)
		return -1;

	if (current->child == NULL)
	{
		current->child = new;
	}

	else
	{
		prev = FindLastDirectory(current->child);
		InsertAfter(prev, new);
	}

	return 0;
}

position CreateNewDirectory(char* name) {
	position new = (position)malloc(sizeof(directory));

	if (!new) {
		perror("Greska pri alokaciji memorije!");
		return NULL;
	}

	strcpy(new->name, name);
	new->sibling = NULL;
	new->child = NULL;

	return new;
}
position FindLastDirectory(position first)
{
	position temp = first;

	while (temp->sibling != NULL)
	{
		temp = temp->sibling;
	}

	return temp;
}

int InsertAfter(position prev, position new)
{
	new->sibling = prev->sibling;
	prev->sibling = new;

	return 0;
}

position ChangeDirectory(position current)
{
	char name[MAX_LINE] = { 0 };
	position temp = current->child;

	printf("What directory do you want to go to: ");
	scanf(" %s", name);

	while (temp != NULL && strcmp(name, temp->name) != 0)
	{
		temp = temp->sibling;
	}

	if (!temp)
	{
		printf("The system could not find the path specified.\n");
		return NULL;
	}

	return temp;
}

int DeleteAfter(positionStack head)
{
	positionStack temp = head->next;

	head->next = temp->next;
	free(temp);

	return 0;
}

int Push(positionStack head, position current)
{
	positionStack NewElement = (positionStack)malloc(sizeof(stack));
	if (!NewElement)
	{
		printf("Could not allocate memory!\n");
		return -1;
	}

	NewElement->directory = current;
	NewElement->next = NULL;

	StackInsert(head, NewElement);

	return 0;
}

int StackInsert(positionStack head, positionStack new_element)
{
	new_element->next = head->next;
	head->next = new_element;

	return 0;
}

int PrintDirectories(position first)
{
	while (first != NULL)
	{
		printf(" %s\n", first->name);
		first = first->sibling;
	}

	return 0;
}

position Pop(positionStack head)
{
	return head->next->directory;
}

int NameCheck(position first, char* name)
{
	position temp = first;

	while (temp != NULL)
	{
		if (strcmp(name, temp->name) == 0)
			return 1;
		temp = temp->sibling;
	}

	return 0;
}