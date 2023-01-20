#ifndef declarations_h
#define declarations_h
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
CountryPosition ReadCountriesFromFile(char* filename, CountryPosition root);
CityPosition ReadCitiesFromFile(char* filename);
CountryPosition InsertSortedCountriesToTree(CountryPosition root, CountryPosition newCountry);
int InsertSortedCitiesToList(CityPosition head, CityPosition newCity);
int InsertAfter(CityPosition head, CityPosition newElement);
CityPosition CreateNewCity(char* name, int population);
int PrintList(CityPosition head);
int PrintTreeInOrder(CountryPosition current);
int CityCompare(CityPosition city1, CityPosition city2);
CountryPosition FindCountry(CountryPosition current, char* countryName);
int CheckPopulation(CityPosition head, int number);
int CheckNumber();
int UserInput(CountryPosition country);
#endif