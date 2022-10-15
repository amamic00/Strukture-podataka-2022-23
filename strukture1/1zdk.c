#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

struct _Student;
typedef struct _Students {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Student;

int CountStudentsFromFile(char* fileName);
int AddStudents(char* fileName, int numberOfStudents,Student** student);
int PrintStudents(int numberOfStudents,Student* students);

int main()
{
	char file[MAX_SIZE] = { 0 };
	int numerOfStudents = 0;
	Student* student = NULL;

	printf("please enter the name of the file: ");
	scanf(" %s", file);

	numerOfStudents= CountStudentsFromFile(file);
	printf("there is %d students ", numerOfStudents);

	if (numerOfStudents != 0) {
		AddStudents(file, numerOfStudents, &student);
		PrintStudents(numerOfStudents, student);
	}

	return 0;
}
int CountStudentsFromFile(char* fileName)
{
	FILE* f;
	char buffer[MAX_SIZE] = { 0 };
	int br = 0;

	f = fopen(fileName, "r");
	if (!f) {
		perror("couldn't open file!\n");
		return -1;
	}
	while (!feof(f)) {
		fgets(buffer, MAX_SIZE, f);
		if (strcmp(buffer,"\n")!=0) {
			br++;
		}

	}
	fclose(f);
	if (br == 0) {
		printf("file has no students!\n");
		return 0;
	}
	else
		return br;
}
int PrintStudents(int numberOfStudents, Student* student)
{
	double relativePoint = 0, numberOfPoints = 0, maxPoints = 0;
	int i = 0;

	for (i = 0;i < numberOfStudents;i++) {
		if ((student + i)->points > maxPoints) {
			maxPoints = (student + i)->points;
		}
	}
	printf("\n");
	printf("  NAME  SURNAME  APSOLUTE POINTS  RELATIVE POINTS\n");

	for (i = 0;i < numberOfStudents;i++) {
		printf("  %s    %s         %.2lf\t      %.2lf\n", 
			(student + i)->name,
			(student + i)->surname,
			(student + i)->points, 
			(student + i)->points / maxPoints * 100);
	}
	return 0;
}
int AddStudents(char* fileName,int numberOfStudents, Student** student)
{
	FILE* f;
	int i = 0;

	f = fopen(fileName, "r");
	if (!f) {
		perror("couldn't open file!\n");
		return -1;
	}
	*student = (Student*)malloc(numberOfStudents * sizeof(Student));

	for (i = 0;i < numberOfStudents;i++) {
		fscanf(f, " %s %s %lf",
			(*student + i)->name,
			(*student + i)->surname,
			&(*student + i)->points);
	}
	fclose(f);
	return 0;
}