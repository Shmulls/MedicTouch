//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* PERSON_FORMAT_OUT = "{\"name\": \"%s\", \"expertise\": \"%s\", \"age\":%d, \"gender\": \"%c\"}\n";
const char* PERSON_FORMAT_IN = "{\"name\": \"%[^\"]\",\"expertise\": \"%[^\"]\", \"age\":%d, \"gender\": \"%c\"}\n"; //%[^,] - read everthing excepet the ",";

typedef struct Doctor {
	char name[20];
	char expertise[30];
	int age;
	char gender;
}Doctor;

int main(int argc, char* argv[])
{
	Doctor p1 = {
		.name = "Andrew",
		.expertise = "family",
		.age = 22,
		.gender = 'M'
	};

	Doctor p2;

	FILE* file;
	fopen_s(&file, "doctor.dat", "w+");
	if (file == NULL)
	{
		return 1;
	}

	fprintf_s(file, PERSON_FORMAT_OUT, p1.name, p1.expertise, p1.age, p1.gender);
	fseek(file, 0, SEEK_SET); 
	fscanf_s(file, PERSON_FORMAT_IN, p2.name, 20, p2.expertise, 20, &p2.age, &p2.gender);

	printf("\"name\": \"%s\", \"expertise\": \"%s\", \"age\":%d, \"gender\": \"%c\"\n", p1.name, p1.expertise, p1.age, p1.gender);
	return 0;
}