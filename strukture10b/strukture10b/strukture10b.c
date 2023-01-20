#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"
#define MAX_SIZE 1024

int main()
{
	CountryPosition root = NULL;
	root = InicializeCountry(root);
	CountryPosition country = &root;

	UserInput(country);

	return 0;
}