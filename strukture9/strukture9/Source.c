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

int printLevel(position, int);
int printLevelOrder(position);
position createNewElement(int);
position insertA(position, int*);
position insert(position, int);
int replace(position);
position randomC(position);
int fileEntry(position, char*);
int treeEntry(position, FILE*);
int askFilename(char*);
int main() {
	position root = NULL;
	position rootC = NULL;
	
	int niz[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	char dat[50] = { 0 };

	printf("a) ");
	root = insertA(root, niz);
	printLevelOrder(root);

	askFilename(dat);
	fileEntry(root, dat);

	printf("\n\nb) ");
	root->number = replace(root->left) + replace(root->right);
	printLevelOrder(root);

	askFilename(dat);
	fileEntry(root, dat);

	printf("\n\nc)");
	rootC = randomC(rootC);
	printLevelOrder(rootC);

	return 0;
}

position insertA(position root, int* niz) {

	int i = 0;

	while(i<10)
	{
		root = insert(root, niz[i]);
		i++;
	}
	return root;
}

position insert(position root, int number)
{
	if (root == NULL) {
		root = createNewElement(number);
		return root;
	}

	else if (number >= root->number) {
		root->left = insert(root->left, number);
	}

	else if (number < root->number) {
		root->right = insert(root->right, number);
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
	int temp = 0;
	if (current == NULL)
		return 0;
	else {
		temp = current->number;
		current->number = replace(current->right) + replace(current->left);
	}

	return temp + current->number;
}
int printLevel(position root, int level)
{
	int left = 0, right = 0;
	if (root == NULL)
		return 0;
	if (level == 1)
	{
		printf("%d\n", root->number);
		return 1;
	}
	left = printLevel(root->left, level - 1);
	right = printLevel(root->right, level - 1);
	return left || right;
}
int printLevelOrder(position root)
{
	int level = 1;
	while (printLevel(root, level))
		level++;
	return 0;
}

position randomC(position root) {

	srand(time(NULL));
	int i = 0;

	for (i = 1; i < 10; i++)
	{
		root = insert(root, rand() % 80 + 10);
	}

	return root;
}

int askFilename(char* filename) {

	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);

	return 0;
}

int fileEntry(position root, char* FileName) {
	FILE* fp = NULL;
	fp = fopen(FileName, "w");
	if (!fp) {
		printf("Greska!");
	}
	treeEntry(root, fp);
	fprintf(fp, "\n");
	fclose(fp);
	return 0;
}
int treeEntry(position root, FILE* fp) {

	if (root)
	{
		treeEntry(root->left, fp);
		fprintf(fp, "%d ", root->number);
		treeEntry(root->right, fp);
	}

	return 0;
}
