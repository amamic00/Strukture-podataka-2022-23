#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 150

struct _Polinom;
typedef struct _Polinom* position;
typedef struct _Polinom {
	int coef;
	int exp;
	position next;
}Polinom;

int zbrajanje(position, position, position);
int mnozenje(position, position, position);
int readFile(char*, position, position);
int sortiraniUnos(position, position);
position createEl(int, int);
int AskFileName(position, position);
int printPolinom(position);

int main() {
	Polinom head1 = { .coef = 0,.exp = 0,.next = NULL };
	Polinom head2 = { .coef = 0,.exp = 0,.next = NULL };
	Polinom headSuma = { .coef = 0,.exp = 0,.next = NULL };
	Polinom headProdukt = { .coef = 0,.exp = 0,.next = NULL };

	position pHead1 = &head1;
	position pHead2 = &head2;
	position pHeadSuma = &headSuma;
	position pHeadProdukt = &headProdukt;

	AskFileName(pHead1, pHead2);

	printf("\nPrvi polinom:");
	printPolinom(pHead1->next);

	printf("\nDrugi polinom:");
	printPolinom(pHead2->next);

	zbrajanje(pHead1->next, pHead2->next, pHeadSuma);

	printf("\nSuma:");
	printPolinom(pHeadSuma->next);

	mnozenje(pHead1->next, pHead2->next, pHeadProdukt);

	printf("\nProdukt:");
	printPolinom(pHeadProdukt->next);

	return 0;
}

position createEl(int coef, int exp) {

	position newEl = NULL;
	newEl = (position)malloc(sizeof(Polinom));
	if (!newEl) {
		printf("Greska pri alokaciji memorije!");
		return -1;
	}

	newEl->coef = coef;
	newEl->exp = exp;
	newEl->next = NULL;

	return newEl;
}
int AskFileName(position head1, position head2) {
	char dat[MAX] = { 0 };
	printf("Unesite ime datoteke: ");
	scanf(" %s", dat);

	readFile(dat, head1, head2);

	return 0;
}
int readFile(char* filename, position head1, position head2) {
	char buffer[MAX] = { 0 };
	char* pBuff = buffer;
	int status = 0;
	int coef = 0;
	int exp = 0;
	int n = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (!fp) {
		printf("Neuspjelo otvaranje datoteke!");
		printf("\nPokusajte ponovo.\n");
		AskFileName(head1, head2);
	}

	fgets(buffer, MAX, fp);

	while (strlen(pBuff) != 0) {
		status = sscanf(pBuff, " %d %d %n", &coef, &exp, &n);
		if (status == 2) {
			position newEl = createEl(coef, exp);
			sortiraniUnos(head1, newEl);
		}
		else {
			printf("Greska u datoteci!");
		}

		pBuff += n;
	}

	fgets(buffer, MAX, fp);
	pBuff = &buffer;

	while (strlen(pBuff) != 0) {
		status = sscanf(pBuff, " %d %d %n", &coef, &exp, &n);
		if (status == 2) {
			position newElem = createEl(coef, exp);
			sortiraniUnos(head2, newElem);
		}
		else {
			printf("Greska u datoteci!");
		}

		pBuff += n;
	}

	fclose(fp);

	return 0;
}

int sortiraniUnos(position head, position novi) {

	position pret = head;
	position temp = head->next;

	while (temp != NULL && temp->exp < novi->exp) {
		pret = temp;
		temp = temp->next;
	}
	if (temp != NULL && novi->exp == temp->exp) {
		temp->coef += novi->coef;
		if (temp->coef == 0) {
			pret->next = temp->next;
			free(temp);
		}
	}
	else {
		novi->next = temp;
		pret->next = novi;
	}

	return 0;
}

int zbrajanje(position head1, position head2, position suma) {
	position temp = NULL;

	while (head1 != NULL && head2 != NULL) {
		if (head1->exp == head2->exp) {
			position newEl = createEl(head1->coef + head2->coef, head1->exp);
			sortiraniUnos(suma, newEl);
			head1 = head1->next;
			head2 = head2->next;
		}
		else if (head1->exp > head2->exp) {
			position new = createEl(head2->coef, head2->exp);
			sortiraniUnos(suma, new);
			head2 = head2->next;
		}
		else if (head1->exp < head2->exp) {
			position new = createEl(head1->coef, head1->exp);
			sortiraniUnos(suma, new);
			head1 = head1->next;
		}
	}

	if (head2 == NULL) {
		temp = head1;
	}
	else if (head1 == NULL) {
		temp = head2;
	}

	while (temp != NULL) {
		position new = createEl(temp->coef, temp->exp);
		sortiraniUnos(suma, new);
		temp = temp->next;
	}
	return 0;
}
int mnozenje(position head1, position head2, position produkt) {
	position temp2 = head2;
	while (head1 != NULL) {
		head2 = temp2;
		while (head2 != NULL) {
			position newEl = createEl(head1->coef * head2->coef, head1->exp + head2->exp);
			sortiraniUnos(produkt, newEl);
			head2 = head2->next;
		}
		head1 = head1->next;
	}

	return 0;
}
int printPolinom(position first) {

	printf("\n");
	while (first != NULL) {
		if (first->coef == 1) {
			printf("x^%d", first->exp);
		}
		else if (first->exp == 1) {
			printf("%dx", first->coef);
		}
		else {
			printf("%dx^%d", first->coef, first->exp);
		}
		if (first->next != NULL && first->next->coef > 0) {
			printf("+");
		}
		first = first->next;
	}
	printf("\n");

	return 0;
}