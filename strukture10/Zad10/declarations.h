#ifndef declarations_h
#define declarations_h
#define MAX_SIZE 1024

struct _cityTree;
typedef struct _cityTree* CityPosition;
typedef struct _cityTree {
	char name[MAX_SIZE];
	int population;
	CityPosition left;
	CityPosition right;
}cityTree;

struct _countryList;
typedef struct _countryList* CountryPosition;
typedef struct _countryList {
	char name[MAX_SIZE];
	CountryPosition next;
	CityPosition rootCity;
}countryList;

CityPosition AddCityNode(CityPosition root, char* name, int population);
CountryPosition InicializeCountry(CountryPosition head);
int ReadCountriesFromFile(char* filename, CountryPosition head);
CityPosition ReadCitiesFromFile(char* filename);
int InsertSortedCountriesToList(CountryPosition head, CountryPosition newCountry);
CityPosition InsertSortedCitiesToTree(CityPosition current, char* name, int population);
int InsertAfter(CountryPosition head, CountryPosition newElement);
int PrintList(CountryPosition head);
int PrintTreeInOrder(CityPosition current);
CountryPosition FindCountry(CountryPosition head, char* countryName);
int FindMax(CityPosition current);
int CheckPopulation(CountryPosition head, CountryPosition country, int number);
int FindCitiesWithLargerPopulation(CityPosition current, int number);
int UserInput(CountryPosition head);
int DeleteAll(CountryPosition head);
int DeleteCountry(CountryPosition position);
CityPosition DeleteCityTree(CityPosition current);

#endif

