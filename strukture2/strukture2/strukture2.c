#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 150

struct _student;
typedef struct _student* position;

typedef struct _student {
	char name[MAX];
	char surname[MAX];
	int birth_year;

	position next;
}student;

position CreatePerson(char*, char*, int);
int Prepend(position, char* name, char* surname, int birth_year);
int InsertAfter(position head, position new);
int print(position head);
position FindLast(position);
int Append(position, char* name, char* surname, int birth_year);
position FindBySurname(position, char*);
int delete(position, char*);
void AskInfo(char* name, char* surname, int* birth_year);
int menu(position);

int main() {
	student head = { .name = {0},.surname = {0},.birth_year = 0,.next = NULL };
	position pHead = &head;

	menu(pHead);

	return 0;
}
position CreatePerson(char* name, char* surname, int birth_year) {
	position new = NULL;
	new = (position)malloc(sizeof(student));

	if (new == NULL) {
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	strcpy(new->name, name);
	strcpy(new->surname, surname);
	new->birth_year = birth_year;
	new->next = NULL;

	return new;
}
int Prepend(position head, char* name, char* surname, int birth_year) {
	position new = CreatePerson(name, surname, birth_year);
	if (!new) {
		perror("error!\n");
		return -1;
	}
	InsertAfter(head, new);

	return 0;
}
int InsertAfter(position head, position new)
{
	new->next = head->next;
	head->next = new;

	return 0;
}
int print(position head) {
	position p = head;

	while (p != NULL) {
		printf("\n%s\t%s\t%d", p->name, p->surname, p->birth_year);
		p = p->next;
	}
	return 0;
}
position FindLast(position head) {
	while (head->next != NULL) {
		head = head->next;
	}

	return head;
}
int Append(position head, char* name, char* surname, int birth_year) {
	position new = CreatePerson(name, surname, birth_year);
	if (!new) {
		perror("error!\n");
		return -1;
	}

	position last = NULL;
	last = FindLast(head);

	InsertAfter(last, new);

	return 0;
}

position FindBySurname(position head, char* surname) {

	while (head != NULL) {
		if (strcmp(head->surname, surname) == 0)
			return head;
		head = head->next;
	}

	return NULL;
}

int delete(position head, char* surname) {
	position temp = head;
	position toDelete = NULL;

	while (temp->next != NULL) {
		if (strcmp(temp->next->surname, surname) == 0) {
			toDelete = temp->next;
			temp->next = toDelete->next;
			free(toDelete);
		}
		temp = temp->next;
	}
	return 0;
}

void AskInfo(char* name, char* surname, int* birth_year) {
	printf("\nUnesite ime: ");
	scanf(" %s", name);
	printf("\nUnesite prezime: ");
	scanf(" %s", surname);
	printf("\nUnesite godinu rodenja: ");
	scanf(" %d", birth_year);
}
int menu(position head) {

	position new = NULL;
	char name[MAX] = { 0 };
	char surname[MAX] = { 0 };
	int birth_year = 0;
	char surnameInput[MAX] = { 0 };
	int choice = 0;
	printf("\nOdaberite:\n1-UMETANJE NA POCETAK LISTE\n2-UMETANJE NA KRAJ LISTE\n"
		"3-ISPIS\n4-PRONADI ELEMENT U LISTI\n5-BRISI ELEMENT IZ LISTE"
		"\n6-KRAJ\n");
	scanf(" %d", &choice);
	switch (choice)
	{
	case (1):
		AskInfo(name, surname, &birth_year);
		Prepend(head, name, surname, birth_year);
		menu(head);
		break;
	case (2):
		AskInfo(name, surname, &birth_year);
		Append(head->next, name, surname, birth_year);
		menu(head);
		break;
	case (3):
		print(head->next);
		menu(head);
		break;
	case (4):
		printf("\nUnesite prezime: ");
		scanf(" %s", surnameInput);
		new = FindBySurname(head, surnameInput);
		printf("\n%s\t%s\t%d", new->name, new->surname, new->birth_year);
		menu(head);
		break;
	case (5):
		printf("\nUnesite prezime: ");
		scanf(" %s", surnameInput);
		delete(head, surnameInput);
		menu(head);
		break;
	case (6):
		printf(":)");
		break;
	default:
		printf("Greska!");
		break;
	}
	return 0;
}
