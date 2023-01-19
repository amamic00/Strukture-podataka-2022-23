#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

#include "declarations.h"

CountryPosition InicializeCountry(CountryPosition head)
{
	CountryPosition newCountry = NULL;
	newCountry = (CountryPosition)malloc(sizeof(countryList));
	if (!newCountry)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(newCountry->name, "");
	newCountry->next = 0;
	newCountry->rootCity = NULL;

	return newCountry;
}
CityPosition AddCityNode(CityPosition root, char* name, int population)
{
	CityPosition newCity = NULL;
	newCity = (CityPosition)malloc(sizeof(cityTree));
	if (!newCity)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(newCity->name, name);
	newCity->population = population;
	newCity->left = 0;
	newCity->right = 0;

	return newCity;
}
int ReadCountriesFromFile(char* filename, CountryPosition head)
{
	char countryFilename[MAX_SIZE] = { 0 };
	char buffer[MAX_SIZE] = { 0 };
	CountryPosition temp = NULL;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!");
		return EXIT_FAILURE;
	}
	printf("Content of the file:\n");
	while (!feof(f))
	{
		temp = InicializeCountry(temp);
		fgets(buffer, MAX_SIZE, f);
		if (sscanf(buffer, " %s %s", temp->name, countryFilename) == 2)
		{
			temp->rootCity = ReadCitiesFromFile(countryFilename);
			InsertSortedCountriesToList(head, temp);
		}
	}
	fclose(f);
	return 0;
}
CityPosition ReadCitiesFromFile(char* filename)
{
	char buffer[MAX_SIZE] = { 0 };
	char cityName[MAX_SIZE] = { 0 };
	int population = 0;
	CityPosition root = NULL;

	FILE* f;
	f = fopen(filename, "r");
	if (!f)
	{
		perror("Couldn't open file!");
		return 0;
	}
	while (!feof(f))
	{
		fgets(buffer, MAX_SIZE, f);
		if (sscanf(buffer, " %s %d", cityName, &population) == 2)
			root = InsertSortedCitiesToTree(root, cityName, population);
	}
	fclose(f);
	return root;
}
CityPosition InsertSortedCitiesToTree(CityPosition current, char* name, int population)//citycompare f-ja?
{
	if (current == NULL)
	{
		current = AddCityNode(current, name, population);
	}
	if (current->population > population)
		current->right = InsertSortedCitiesToTree(current->right, name, population);
	else if (current->population < population)
		current->left = InsertSortedCitiesToTree(current->left, name, population);
	else if (current->population == population)
	{
		if (strcmp(current->name, name) < 0)
			current->right = InsertSortedCitiesToTree(current->right, name, population);
		else if (strcmp(current->name, name) > 0)
			current->left = InsertSortedCitiesToTree(current->left, name, population);
		else
			return current;
	}
	else
		free(current);
	return current;
}
int InsertSortedCountriesToList(CountryPosition head, CountryPosition newCountry)
{
	CountryPosition temp = head;

	while (temp->next != NULL && strcmp(temp->next->name, newCountry->name) < 0)
		temp = temp->next;

	if (temp->next == NULL || strcmp(temp->next->name, newCountry->name))
		InsertAfter(temp, newCountry);

	return EXIT_SUCCESS;
}
int InsertAfter(CountryPosition head, CountryPosition newElement)
{
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
int PrintList(CountryPosition head)
{
	CountryPosition temp = head->next;
	while (temp != NULL)
	{
		printf("\n%s\n\n", temp->name);
		printf(" City  Population\n");
		printf("---------------------\n");
		PrintTreeInOrder(temp->rootCity);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintTreeInOrder(CityPosition current)
{
	if (current == NULL)
		return 0;
	PrintTreeInOrder(current->left);
	printf(" %s  %d\n", current->name, current->population);
	PrintTreeInOrder(current->right);

	return EXIT_SUCCESS;
}
CountryPosition FindCountry(CountryPosition head, char* countryName)
{
	CountryPosition temp = head->next;
	while (temp != NULL && strcmp(temp->name, countryName))
		temp = temp->next;
	return temp;
}
int FindMax(CityPosition current)
{
	int max = 0;
	if (current == NULL)
		return 0;
	if (current->right == NULL)
		return current->population;
	max = FindMax(current->right);
	return max;
}
int CheckPopulation(CountryPosition head, CountryPosition country, int number)
{
	int max = 0;
	max = FindMax(country->rootCity);
	if (number > max)
	{
		printf("There is no city with larger population!\n");
		return EXIT_FAILURE;
	}
	printf("\nList of cities in %s with larger population than %d:\n", country->name, number);

	printf("\nCity\tPopulation\n");
	printf("------------------------");
	FindCitiesWithLargerPopulation(country->rootCity, number);
	return EXIT_SUCCESS;
}
int FindCitiesWithLargerPopulation(CityPosition current, int number)
{
	if (current == NULL)
		return 0;

	FindCitiesWithLargerPopulation(current->left, number);
	if (current->population >= number)
		printf("\n %s %d", current->name, current->population);
	FindCitiesWithLargerPopulation(current->right, number);

	return EXIT_SUCCESS;
}

int UserInput(CountryPosition head)
{
	char chosenCountry[MAX_SIZE] = { 0 };
	int populationInput = 0;
	CountryPosition country = NULL;
	char filename[MAX_SIZE] = { 0 };

	printf("Enter the name of the file:");
	scanf(" %s", filename);

	while (ReadCountriesFromFile(filename, head) == EXIT_FAILURE)
	{
		printf("Wrong input! Please try again: ");
		scanf(" %s", filename);

	}
	PrintList(head);

	printf("\nPlease enter the name of the country you want to filter:");
	scanf("%s", chosenCountry);
	country = FindCountry(head, chosenCountry);
	if (!country)
	{
		printf("\nCountry you choose is not located in file! Please try again!");
		scanf("%s", chosenCountry);
		country = FindCountry(head, chosenCountry);
	}
	printf("\nEnter the population number you want to check:");
	populationInput = CheckNumber();

	CheckPopulation(head, country, populationInput);
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
int DeleteAll(CountryPosition head)
{
	while (head->next)
		DeleteCountry(head);

	return EXIT_SUCCESS;
}
int DeleteCountry(CountryPosition position)
{
	CountryPosition country = position->next;

	if (!country)
		return EXIT_SUCCESS;

	position->next = country->next;
	country->rootCity = DeleteCityTree(country->rootCity);
	country->next = NULL;
	free(country);

	return EXIT_SUCCESS;
}

CityPosition DeleteCityTree(CityPosition current)
{
	if (!current) {
		return NULL;
	}
	current->left = DeleteCityTree(current->left);
	current->right = DeleteCityTree(current->right);
	free(current);

	return NULL;
}