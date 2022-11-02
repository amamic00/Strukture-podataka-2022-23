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
int Print(position head);
position FindLast(position);
int Append(position, char* name, char* surname, int birth_year);
position FindBySurname(position, char*);
int DeleteSurname(position, char*);
void AskInfo(char* name, char* surname, int* birth_year);
int menu(position);

int AddBefore(position, char*, char*, int);
int AddAfter(position, char*, char*, int);
position FindBefore(position head, char* surname);
int Sort(position head);
int ReadFromFile(position, char*);
int PrintInFile(position, char*);
int DeleteAll(position head);
int DeleteAfter(position head);
int AddSorted(position head, char* name, char* surname, int birthyear);



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
int Print(position head) {
	position p = head;

	while (p != NULL) {
		printf("\n%s %s %d", p->name, p->surname, p->birth_year);
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

int DeleteSurname(position head, char* surname) {
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

position FindBefore(position head, char* surname) {
	while (head->next != NULL) {
		if (strcmp(head->next->surname, surname) == 0) {
			return head;
		}
		head = head->next;
	}
	return NULL;
}

int AddBefore(position head, char* name, char* surname, int birth_year) {
	position new = NULL;
	position before = NULL;
	char surnameInput[MAX] = { 0 };

	new = CreatePerson(name, surname, birth_year);
	if (!new) {
		printf("Greska pri alokaciji! ");
		return -1;
	}

	printf("Unesi zeljeno prezime: ");
	scanf(" %s", surnameInput);

	before = FindBefore(head, surnameInput);
	InsertAfter(before, new);

	return 0;
}

int AddAfter(position head, char* name, char* surname, int birth_year) {

	position new = NULL;
	position current = NULL;
	char surnameInput[MAX] = { 0 };

	new = CreatePerson(name, surname, birth_year);
	if (!new) {
		printf("Greska pri alokaciji! ");
		return -1;
	}

	printf("Unesi zeljeno prezime: ");
	scanf(" %s", surnameInput);

	current = FindBySurname(head, surnameInput);
	InsertAfter(current, new);

	return 0;
}

int Sort(position head)
{
	position p = head;
	position q = NULL;
	position beforeQ = NULL;
	position last = NULL;

	while (p->next != last)
	{
		beforeQ = p;
		q = beforeQ->next;

		while (q->next != last)
		{
			if (strcmp(q->surname, q->next->surname) > 0)
			{
				beforeQ->next = q->next;
				q->next = q->next->next;
				beforeQ->next->next = q;
				q = beforeQ->next;
			}
			beforeQ = q;
			q = q->next;
		}
		last = q;
	}

	return 0;
}

int PrintInFile(position head, char* filename) {

	FILE* fp = fopen(filename, "w");
	if (!fp) {
		printf("Neuspjesno otvaranje datoteke! \n");
		return -1;
	}

	while (head != NULL) {

		fprintf(fp, " %s %s %d\n", head->name, head->surname, head->birth_year);
		head = head->next;
	}
	fclose(fp);
	return 0;
}

int ReadFromFile(position head, char* filename) {

	char name[MAX] = { 0 };
	char surname[MAX] = { 0 };
	int birth_year = 0;
	position newPerson = NULL;

	FILE* fp = fopen(filename, "r");

	if (!fp) {
		printf("Neuspjesno otvaranje datoteke! \n");
		return -1;
	}

	while (!feof(fp)) {

		fscanf(fp, " %s %s %d", name, surname, &birth_year);
		AddSorted(head, name, surname, birth_year);

		//newPerson = CreatePerson(name, surname, birth_year);
		//InsertAfter(head, newPerson);
	}

	fclose(fp);
	return 0;
}

int DeleteAfter(position head)
{
	position toDelete = head->next;

	head->next = toDelete->next;
	free(toDelete);

	return 0;
}

int DeleteAll(position head)
{
	while (head != NULL) {
		DeleteAfter(head);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int AddSorted(position head, char* name, char* surname, int birth_year)
{
	position NewPerson = NULL;
	position temp = head;

	//for (temp;temp->next;temp = temp->next)
	while (temp->next != NULL)
	{
		if (strcmp(temp->next->surname, surname) == 0)
		{
			if (strcmp(temp->next->name, name) > 0)
				break;
			if (strcmp(temp->next->name, name) == 0)
			{
				if (temp->next->birth_year > birth_year)
					break;
			}
		}
		if (strcmp(temp->next->surname, surname) > 0)
			break;

		temp = temp->next;
	}

	NewPerson = CreatePerson(name, surname, birth_year);
	if (!NewPerson)
		return -1;

	InsertAfter(temp, NewPerson);

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
	char filename[MAX] = { 0 };
	char surnameInput[MAX] = { 0 };
	int choice = 0;

	do
	{
		printf("\n\nOdaberite:\n1-UMETANJE NA POCETAK LISTE\n2-UMETANJE NA KRAJ LISTE\n"
			"3-ISPIS\n4-PRONADI ELEMENT U LISTI\n5-BRISI ELEMENT IZ LISTE"
			"\n6-DODAJ IZA ODREDENOG ELEMENTA\n7-DODAJ ISPRED ODREDENOG ELEMENTA\n8-SORTIRAJ\n9-UPISI U LISTU\n10-U DATOTEKU\n11-IZBRISI SVE\n12-KRAJ\n");
		scanf(" %d", &choice);
		switch (choice)
		{
		case (1):
			AskInfo(name, surname, &birth_year);
			Prepend(head, name, surname, birth_year);
			break;
		case (2):
			AskInfo(name, surname, &birth_year);
			Append(head->next, name, surname, birth_year);
			break;
		case (3):
			Print(head->next);
			break;
		case (4):
			printf("\nUnesite prezime: ");
			scanf(" %s", surnameInput);
			new = FindBySurname(head, surnameInput);
			printf("\n%s\t%s\t%d", new->name, new->surname, new->birth_year);
			break;
		case (5):
			printf("\nUnesite prezime: ");
			scanf(" %s", surnameInput);
			DeleteSurname(head, surnameInput);
			break;
		case (6):
			AskInfo(name, surname, &birth_year);
			AddAfter(head, name, surname, birth_year);
			break;
		case (7):
			AskInfo(name, surname, &birth_year);
			AddBefore(head, name, surname, birth_year);
			break;
		case (8):
			Sort(head);
			break;
		case (9):
			printf("Unesite ime datoteke: ");
			scanf(" %s", filename);
			ReadFromFile(head, filename);
			Print(head->next);
			break;
		case (10):
			printf("Unesite ime datoteke: ");
			scanf(" %s", filename);
			PrintInFile(head->next, filename);
			break;
		case (11):
			DeleteAll(head);
			printf(":)");
			break;
		case (12):
			break;
		default:
			printf("Greska!");
			break;
		}
	} while (choice != 12);

	return 0;
}
