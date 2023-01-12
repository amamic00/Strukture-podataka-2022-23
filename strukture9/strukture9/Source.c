#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct _tree;
typedef struct _tree* position;
typedef struct _tree
{
	int number;
	position left;
	position right;
} tree;

struct _list;
typedef struct _list* lposition;
typedef struct _list
{
	int number;
	lposition next;
}list;


position createNewElement(int);
position insert(position, position);
int inorder(position);
int replace(position);
int printinList(position, lposition);
lposition createNewListElement(int);
int appendList(lposition, int);
lposition findLast(lposition);
int insertAfter(lposition, lposition);
int fileEntry(lposition, char*);
position insertA(position, int*);
position randomC(position);


int main() {
	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	char dat[50] = { 0 };

	position root = NULL;
	lposition head=NULL;

	root = insertA(root, niz);
	inorder(root);
	printf("\n");

	//b
	root->number = replace(root);
	inorder(root);
	printf("\n");

	/*root = randomC(root);

	inorder(root);
	printf("\n");

	printf("Upisite ime datoteke u koju zelite pohraniti svoju listu: ");
	scanf(" %s", dat);
	printf("\n");*/


	//a)
	/*printinList(root, head->next);
	printf("\n");
	fileEntry(head->next, dat);
	printf("\n");
*/
	//b)
	root->number = replace(root);
	printinList(root, &head);
	printf("\n");
	fileEntry(&head, dat);




	return 0;
}

position randomC(position root) {

	srand(time(NULL));
	list head = { .next = NULL,.number = {0} };
	position newElement = NULL;
	int i = 0;

	root = (position)malloc(sizeof(tree));
	root->number = rand() % 80 + 10;
	root->left = NULL;
	root->right = NULL;

	for (i = 1; i < 10; i++)
	{
		newElement = createNewElement(rand() % 80 + 10);
		if (!newElement)
		{
			perror("Can't allocate memory!");
			return -1;
		}
		root = insert(root, newElement);
	}

	return root;
}

position insertA(position root, int* niz) {
	
	position newElement = NULL;
	int i = 0;

	root = (position)malloc(sizeof(tree));
	root->number = niz[0];
	root->left = NULL;
	root->right = NULL;

	for (i = 1; i < 10; i++)
	{
		newElement = createNewElement(niz[i]);
		if (!newElement)
		{
			perror("Can't allocate memory!");
			return -1;
		}
		root = insert(root, newElement);

	}
	return root;
}


position createNewElement(int number)
{
	position newElement = NULL;
	newElement = (position)malloc(sizeof(tree));
	if (!newElement)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

position insert(position current, position newElement)
{
	if (current == NULL)
		return newElement;
	if (current->number <= newElement->number)
		current->left = insert(current->left, newElement);
	else if (current->number > newElement->number)
		current->right = insert(current->right, newElement);
	return current;
}

int inorder(position current)
{
	if (current == NULL)
		return 0;
	inorder(current->left);
	printf("%d ", current->number);
	inorder(current->right);

	return 0;
}

int replace(position current)
{
	int temp;
	if (current == NULL)
		return 0;
	else {
		temp = current->number;
		current->number = replace(current->right) + replace(current->left);
	}

	return temp + current->number;
}
/*
int replace(position current)
{
	int temp = 0;
	if (!(current->left || current->right))
	{
		temp = current->number;
		current->number = 0;
		return temp;
	}
	else if (current->left&&current->right)
	{
		temp = current->number;
		current->number = replace(current->left) + replace(current->right);
		temp += current->number;
		return temp;
	}
	else if (current->left && !current->right)
	{
		temp = current->number;
		current->number = replace(current->left);
		temp += current->number;
		return temp;
	}
	else
	{
		temp = current->number;
		current->number = replace(current->right);
		temp += current->number;
		return temp;
	}
	return current->number;
}*/

int printinList(position current, lposition head)
{
	
	return 0;
}
int appendList(lposition head, int number)
{
	lposition newListElement = NULL;
	lposition last = NULL;

	newListElement = createNewListElement(number);
	if (!newListElement) {
		return -1;
	}
	last = findLast(head);
	insertAfter(last, newListElement);

	return EXIT_SUCCESS;


}
lposition findLast(lposition head)
{
	lposition temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}
lposition createNewListElement(int number)
{
	lposition newListElement = NULL;
	newListElement = (lposition)malloc(sizeof(list));
	if (!newListElement)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	newListElement->number = number;
	newListElement->next = NULL;

	return newListElement;
}
int insertAfter(lposition position, lposition newListElement)
{
	newListElement->next = position->next;
	position->next = newListElement;

	return EXIT_SUCCESS;
}
int fileEntry(lposition head, char* FileName)
{
	FILE* f = fopen(FileName, "w");
	lposition position = head->next;
	if (!f) {
		printf("Greska!");
	}
	while (position != NULL)
	{
		fprintf(f, " %d ", position->number);
		position = position->next;
	}
	fprintf(f, "\n");

	printf("Upis liste u datoteku uspjesno obavljen!");
	fclose(f);

	return EXIT_SUCCESS;
}

