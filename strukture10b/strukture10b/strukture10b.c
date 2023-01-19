#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024

struct _cityList;
typedef struct _cityList* CityPosition;
typedef struct _cityList {
	char name[MAX_SIZE];
	int population;
	CityPosition next;
}CityList;

struct _countryTree;
typedef struct _countryTree* CountryPosition;
typedef struct _countryTree {
	char name[MAX_SIZE];
	CountryPosition left;
	CountryPosition right;
	CityPosition rootCity;
}CountryTree;

CountryPosition InicializeCountry(CountryPosition newCountry);
int ReadCountriesFromFile(char* filename, CountryPosition root);
CityPosition ReadCitiesFromFile(char* filename, CityPosition head);
CountryPosition InsertSortedCountriesToTree(CountryPosition root, CountryPosition newCountry);
//int InsertSortedCountriesToTree(CountryPosition root, char* name);
int InsertSortedCitiesToList(CityPosition head, CityPosition newCity);
int InsertAfter(CityPosition head, CityPosition newElement);
CityPosition CreateNewCity(char* name, int population);
int PrintList(CityPosition head);
int PrintTreeInOrder(CountryPosition current);

int main()
{
	//CityList head = { .name = {0},.next = NULL };
	//CityPosition headPointer = &head;
	CountryTree root = { .name = {0},.left = NULL,.right = NULL,.rootCity = NULL };

	char chosenCountry[MAX_SIZE] = { 0 };
	int populationInput = 0;
	CountryPosition country = NULL;
	char filename[MAX_SIZE] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", filename);

	/*while (ReadCountriesFromFile(filename,&root) == EXIT_FAILURE)
	{
		printf("Wrong input! Please try again: ");
		scanf(" %s", filename);
	}*/
	ReadCountriesFromFile(filename,&root);
	PrintTreeInOrder(&root);


	return 0;
}

CountryPosition InicializeCountry(CountryPosition root)
{
	CountryPosition newCountry = NULL;
	newCountry = (CountryPosition)malloc(sizeof(CountryTree));
	if (!newCountry)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(newCountry->name, "");
	newCountry->left = NULL;
	newCountry->right = NULL;
	newCountry->rootCity = NULL;

	return newCountry;
}
int ReadCountriesFromFile(char* filename,CountryPosition root)
{
	char buffer[MAX_SIZE] = { 0 };
	char name[MAX_SIZE] = { 0 };
	char dat[MAX_SIZE] = { 0 };
	CountryPosition newCountry = NULL;

	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp)
	{
		perror("Couldn't open file!\n");
		return EXIT_FAILURE;
	}
	while (!feof(fp))
	{
		fgets(buffer, MAX_SIZE, fp);
		if (sscanf(buffer, " %s %s", name, dat) == 2)
		{
			newCountry = InicializeCountry(newCountry);
			strcpy(newCountry->name, name);
			ReadCitiesFromFile(dat, newCountry->rootCity);
			InsertSortedCountriesToTree(root, newCountry);
		}
	}
	fclose(fp);
	return 0;
}

CountryPosition InsertSortedCountriesToTree(CountryPosition root, CountryPosition newCountry)
{
	if (root == NULL)
	{
		return newCountry;
	}
	if (strcmp(root->name, newCountry->name) < 0)
		root->right = InsertSortedCountriesToTree(root->right, newCountry);
	else if (strcmp(root->name, newCountry->name) > 0)
		root->left = InsertSortedCountriesToTree(root->left, newCountry);
	else
		free(root);

	return root;
}

CityPosition ReadCitiesFromFile(char* filename, CityPosition head)
{
	char buffer[MAX_SIZE] = { 0 };
	char name[MAX_SIZE] = { 0 };
	int population = 0;
	//CityPosition head=NULL; 

	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp)
	{
		perror("Couldn't open file!\n");
		return NULL;
	}
	while (!feof(fp))
	{
		fgets(buffer, MAX_SIZE, fp);
		if (sscanf(buffer, " %s %d", name, &population) == 2)
		{
			CityPosition newCity = NULL;
			newCity = CreateNewCity(name, population);
			InsertSortedCitiesToList(head, newCity);
		}
	}
	fclose(fp);
	return NULL;
}
int InsertSortedCitiesToList(CityPosition head,CityPosition newCity)
{
	CityPosition temp = head;
	if (!temp)
		return newCity;

	while (temp)
	{
		if (temp->next != NULL && (temp->next->population < newCity->population || temp->next->population == newCity->population && strcmp(temp->next->name, newCity->name) < 0))
			temp = temp->next;
	}
	if (temp->next == NULL)
		temp->next = newCity;

	else if (strcmp(temp->next->name,newCity->name) == 0)
	{
		free(newCity);
		return 0;
	}
	else
		InsertAfter(temp, newCity);

	return EXIT_SUCCESS;
}
int InsertAfter(CityPosition head, CityPosition newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
CityPosition CreateNewCity(char* name, int population)
{
	CityPosition newCity = NULL;
	newCity = (CityPosition)malloc(sizeof(CityList));
	if (!newCity)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(newCity->name, name);
	newCity->population = population;
	newCity->next = 0;
	
	return newCity;
}
int PrintList(CityPosition head)
{
	CityPosition temp = head;
	while (temp != NULL)
	{
		printf(" %s %d", temp->name,temp->population);
		//printf(" City  Population\n");
		//printf("---------------------\n");
		//PrintTreeInOrder(temp->rootCity);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}
int PrintTreeInOrder(CountryPosition current)
{
	if (current == NULL)
		return 0;
	PrintTreeInOrder(current->left);
	printf(" %s\n", current->name);
	//PrintList(current->rootCity);
	PrintTreeInOrder(current->right);

	return EXIT_SUCCESS;
}