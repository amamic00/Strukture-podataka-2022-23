#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 150

struct _stack;
typedef struct _stack* position;
typedef struct _stack {
	float number;
	position next;
}stack;

position create(float);
int askFilename(char*);
int ReadFromFile(char*, position);
int Pop(position, float*);
int Push(position, position);
int performOperation(char*, position);
int Ispis(position);

int main() {
	stack head = { .number = 0.0,.next = NULL };
	position pHead = &head;

	char filename[MAX] = { 0 };

	askFilename(filename);

	ReadFromFile(filename, pHead);

	printf("\nResult = ");
	Ispis(pHead->next);

	return 0;
}

int askFilename(char* filename) {

	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);

	return 0;
}

position create(float number) {

	position newEl = (position)malloc(sizeof(stack));
	if (!newEl) {
		perror("couldn't allocate memory!\n");
		return NULL;
	}
	newEl->number = number;
	newEl->next = NULL;

	return newEl;
}
int ReadFromFile(char* filename, position head)
{
	float number = 0;
	char buffer[MAX] = { 0 };
	char* p_buffer = buffer;
	int status = 0;
	int n = 0;
	char operation[MAX] = { 0 };

	FILE* fp;
	fp = fopen(filename, "r");

	if (!fp) {
		perror("Couldn't open file!\n");
		return -1;
	}

	fgets(buffer, MAX, fp);

	if (strlen(p_buffer) == 0) {
		printf("Datoteka je prazna!\n");
		return -1;
	}
	printf("postfix: ");
	while (strlen(p_buffer) > 0) {
		if ((status = sscanf(p_buffer, " %f %n", &number, &n)) == 1) {
			position newEl = create(number);
			Push(head, newEl);
			printf("%.2f ", number);
		}
		else if ((status = sscanf(p_buffer, " %s %n", operation, &n)) == 1) {
			performOperation(operation, head);
			printf("%s ", operation);
		}
		p_buffer += n;
	}

	fclose(fp);
	return 0;
}
int Push(position head, position new) {
	new->next = head->next;
	head->next = new;

	return 0;
}
int Pop(position head, float* number)
{
	position toDelete = NULL;
	if (head->next == NULL) {
		printf("Postfix is incorrect! Check again!");
		return -1;
	}

	*number = head->next->number;
	toDelete = head->next;
	head->next = toDelete->next;

	free(toDelete);

	return 0;
}
int performOperation(char* operand, position head) {

	float number1 = 0;
	float number2 = 0;
	int status1 = 0, status2 = 0;
	position result = NULL;
	result = (position)malloc(sizeof(stack));

	status1 = Pop(head, &number1);
	if (status1 == -1) {
		printf("Greska(1)!");
		return -1;
	}
	status2 = Pop(head, &number2);
	if (status2 == -1) {
		printf("Greska(2)!");
		return -1;
	}

	switch (*operand) {
	case '+':
		result = create(number1 + number2);
		Push(head, result);
		break;
	case '-':
		result = create(number1 - number2);
		Push(head, result);
		break;
	case '*':
		result = create(number1 * number2);
		Push(head, result);
		break;
	case '/':
		if (number2 == 0) {
			printf("Ne dijeli s nulom!\n");
			return -2;
		}
		result = create(number1 / number2);
		Push(head, result);
		break;

	default:
		break;
	}

	return 0;
}
int Ispis(position head)
{
	while (head != NULL) {
		printf("%.2f ", head->number);
		head = head->next;
	}
	printf("\n");
	return 0;
}