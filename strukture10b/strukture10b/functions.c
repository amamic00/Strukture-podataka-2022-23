#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"

#define MAX_SIZE 1024

int UserInput(CountryPosition country)
{
	char chosenCountry[MAX_SIZE] = { 0 };
	int populationInput = 0;
	char filename[MAX_SIZE] = { 0 };
	CountryPosition foundCountry = NULL;

	printf("Enter the name of the file:");
	scanf(" %s", filename);

	country = ReadCountriesFromFile(filename, country);
	PrintTreeInOrder(country);

	printf("\nPlease enter the name of the country you want to filter:");
	scanf("%s", chosenCountry);
	foundCountry = FindCountry(country, chosenCountry);
	if (!foundCountry)
	{
		printf("\nCountry you choose is not located in file! Please try again!");
		scanf("%s", chosenCountry);
		foundCountry = FindCountry(country, chosenCountry);
	}
	printf("\nEnter the population number you want to check:");
	populationInput = CheckNumber();

	printf("List of cities more populated:\n");
	if (CheckPopulation(foundCountry->rootCity, populationInput) == EXIT_FAILURE)
		printf("There is no city more populated than %d", populationInput);
	return EXIT_SUCCESS;
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
CountryPosition ReadCountriesFromFile(char* filename, CountryPosition root)
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
			newCountry->rootCity = ReadCitiesFromFile(dat);
			root = InsertSortedCountriesToTree(root, newCountry);
		}
	}
	fclose(fp);
	return root;
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
CityPosition ReadCitiesFromFile(char* filename)
{
	char buffer[MAX_SIZE] = { 0 };
	char name[MAX_SIZE] = { 0 };
	int population = 0;
	CityPosition head = NULL;

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
			if (head == NULL)
				head = newCity;
			else
				InsertSortedCitiesToList(head, newCity);
		}
	}
	fclose(fp);
	return head;
}
int CityCompare(CityPosition city1, CityPosition city2)
{
	int result = 0;
	result = city1->population - city2->population;
	if (result == 0)
		result = strcmp(city1->name, city2->name);
	return result;
}

int InsertSortedCitiesToList(CityPosition head, CityPosition newCity)
{
	CityPosition temp = head;
	if (temp == NULL)
		return EXIT_SUCCESS;

	int result = 0;
	result = CityCompare(head, newCity);
	while (temp->next != NULL && result > 0)
		temp = temp->next;

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

	printf(" City  Population\n");
	printf("---------------------\n");
	while (temp != NULL)
	{
		printf(" %s %d\n", temp->name, temp->population);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintTreeInOrder(CountryPosition current)
{
	if (current == NULL)
		return 0;
	PrintTreeInOrder(current->left);
	printf(" \n\n%s\n", current->name);
	PrintList(current->rootCity);
	PrintTreeInOrder(current->right);

	return EXIT_SUCCESS;
}
CountryPosition FindCountry(CountryPosition current, char* countryName)
{
	if (current == NULL)
		return NULL;
	if (strcmp(current->name, countryName) > 0)
		current->left = FindCountry(current->left, countryName);
	else if (strcmp(current->name, countryName) < 0)
		current->right = FindCountry(current->right, countryName);
	else if (strcmp(current->name, countryName) == 0)
		return current;
}
int CheckPopulation(CityPosition head, int number)
{
	if (head->next == NULL)
	{
		printf("Empty list!\n");
		return;
	}

	while (head->next != NULL)
	{
		if (head->next->population > number)
			printf(" %s %d\n", head->next->name, head->next->population);
		else if (head->next->population < number)
			return EXIT_FAILURE;
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int CheckNumber()
{
	int userInput = 0;
	scanf(" %d", &userInput);
	if (!userInput)
	{
		perror("Incorrect number input!");
		return EXIT_FAILURE;
	}
	return userInput;
}