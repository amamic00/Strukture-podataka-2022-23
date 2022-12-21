#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _tree;
typedef struct _tree* position;

typedef struct _tree {
	int number;
	position left;
	position right;
} tree;

position createNewElement(int);
position insert(position, position);
position delete(position, int);
position findMin(position);
position findMax(position);
position findElement(position, int);
int inorder(position);
int preorder(position);
int postorder(position);
int printLevel(position, int);
int printLevelOrder(position);

int main()
{
	position root = NULL;
	position newElement = NULL;
	
	int temp = 0;
	int num = 0;


	while (temp != 8) {

		printf("\nIzbornik:\n");
		printf("1 - unosenje novog elementa\n2 - inorder ispis\n3 - preorder ispis\n4 - postorder ispis\n5 - level order ispis\n6 - pronalazenje elementa\n7 - brisanje elementa\n8 - prekid programa\n");

		scanf(" %d", &temp);
		switch (temp)
		{
		case 1:
			printf("\nKoji broj zelite unijeti?\n");
			scanf(" %d", &num);
			newElement = createNewElement(num);
			if (!newElement)
				return -1;
			root = insert(root, newElement);
			break;
		case 2:
			inorder(root);
			printf("\n");
			break;
		case 3:
			preorder(root);
			printf("\n");
			break;
		case 4:
			postorder(root);
			printf("\n");
			break;
		case 5:
			printLevelOrder(root);
			printf("\n");
			break;
		case 6:
			printf("Koji element zelite pronaci? ");
			scanf("%d", &num);
			if (findElement(root, num))
				printf("Element %d postoji u stablu.", num);
			else
				printf("Element %d se ne nalazi u stablu.", num);
			printf("\n");
			break;
		case 7:
			printf("Koji element zelite izbrisati? ");
			scanf("%d", &num);
			delete(root, num);
			break;
		default:
			break;

		}
	} 

	return 0;
}

position createNewElement(int number)
{
	position newElement = NULL;
	newElement = (position)malloc(sizeof(tree));
	if (!newElement)
	{
		printf("Cant allocate memory!");
		return NULL;
	}

	newElement->number = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

position insert(position root, position newEl) {

	if (root == NULL) {
		return newEl;
	}

	if (root->number < newEl->number) {
		root->right = insert(root->right, newEl);
	}
	else if (root->number > newEl->number) {
		root->left = insert(root->left, newEl);
	}
	else {
		printf("Invalid");
		free(newEl);
	}

	return root;
}


position delete(position root, int num) {

	if (root == NULL)
		return NULL;
	if (root->number < num) {
		root->right = delete(root->right, num);
	}
	else if (root->number > num) {
		root->left = delete(root->left, num);
	}
	else {
		if (root->left) {
			position temp = findMax(root->left);
			root->number = temp->number;
			root->left = delete(root->left, temp->number);
		}
		else if (root->right) {
			position temp = findMin(root->right);
			root->number = temp->number;
			root->right = delete(root->right, temp->number);
		}
		else {
			free(root);
		}
		return NULL;
	}
	return root;
}

position findMin(position root) {

	if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;
	else
		return findMin(root->left);
}

position findMax(position root) {

	if (root == NULL)
		return NULL;
	else if (root->right == NULL)
		return root;
	else
		return findMax(root->right);
}

position findElement(position root, int element) {
	if (root == NULL)
		return NULL;
	else if (element < root->number)
		return findElement(root->left, element);
	else if (element > root->number)
		return findElement(root->right, element);
	else
		return root;
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

int preorder(position current)
{
	if (current == NULL)
		return 0;
	printf("%d ", current->number);
	preorder(current->left);
	preorder(current->right);

	return 0;
}

int postorder(position current)
{
	if (current == NULL)
		return 0;
	postorder(current->left);
	postorder(current->right);
	printf("%d ", current->number);

	return 0;
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



