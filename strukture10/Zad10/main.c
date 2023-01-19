#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "declarations.h"

int main()
{
	countryList head = { .name = {0},.rootCity = NULL,.next = NULL };
	CountryPosition headPointer = &head;
	UserInput(headPointer);

	DeleteAll(headPointer);
	printf("\n\nCongrats you are environmentally friendly!!!");
	return 0;
}