#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct doctor
{
	char user_name[20], password[20], expertise[20], email[50];
	int day, month, year;
	char gender;
}doctor;

typedef struct patient
{
	char user_name[20];
	char password[20];
}patient;

void create_user()
{
	int selection;
	printf("Choose:\n[1]Doctor\n[2]Patient\n");
	scanf("%d", &selection);

	switch (selection)
	{
	case 1:
	{
		FILE* p2 = fopen("Doctor.csv", "r+");
		if (p2 == NULL)
			exit(1);

		doctor data;

		printf("Enter username:\n");
		scanf("%s", data.user_name);

		printf("Enter password:\n");
		printf(">Must contain at least 6 letters or digits (without characters)<\n");
		scanf("%s", data.password);

		printf("Enter birthdate [day/month/year]:\n");
		scanf("%d%d%d", &data.day, &data.month, &data.year);

		printf("Enter Expertise: ");
		printf("(without characters)\n");
		scanf("%s", data.expertise);

		printf("Enter email address:\n");
		scanf("%s", data.email);

		printf("Enter gender:\n [M] Man / [W] Woman / [O] Other:\n");
		scanf(" %c", &data.gender);

		fseek(p2, 0, SEEK_END);
		fprintf(p2, "%s, %s, \%d\/\%d\/\%d\, %s, %s, %c\n", data.user_name, data.password, data.day, data.month, data.year, data.expertise, data.email, data.gender);

		printf(">Welcome to MedicTouch Dr.%s<\n", data.user_name);

		fclose(p2);
		break;
	}

	case 2:
	{
		FILE* p1 = fopen("Patient.csv", "r+");
		if (p1 == NULL)
			exit(1);

		patient data;

		printf("enter user name: ");
		scanf("%s", data.user_name);

		printf("Enter password: ");
		scanf("%s", data.password);

		fseek(p1, 0, SEEK_END);
		fprintf(p1, "%s,%s\n", data.user_name, data.password);
		printf(">Welcome to MedicTouch %s<\n", data.user_name);

		fclose(p1);
		break;
	}
	}
}

bool check_username(char username[20])
{
	doctor data;
	FILE* p2;
	int m, n, i, j, found = 0;

	p2 = fopen("Doctor.csv", "r");

	if (p2 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	while (fgets(data.user_name, sizeof(doctor), p2))
	{
		char* temp;
		temp = strtok(data.user_name, ",");

		while (temp != NULL)
		{
			if (strcmp(temp, username) == 0)
			{
				found = 1;
				break;
			}
			temp = strtok(NULL, ",");
		}
	}
	fclose(p2);
	if (found == 1)
		return true;
	else
		return false;
}

bool check_password(char password[20])
{
	doctor data;
	FILE* p3;
	int m, n, i, j, found = 0;

	p3 = fopen("Doctor.csv", "r");
	if (p3 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	while (fgets(data.password, sizeof(doctor), p3))
	{
		char* temp;
		temp = strtok(data.password, ",");

		while (temp != NULL)
		{
			if (strcmp(temp, password) == 0)
			{
				found = 1;
				break;
			}
			temp = strtok(NULL, ",");
		}
	}
	fclose(p3);
	if (found == 1)
		return true;
	else
		return false;
}

void login()
{
	char username[20] = { 0 }, password[20] = { 0 };
	int menu;
	printf("Enter username: ");
	getchar();
	gets(username);

	printf("Enter password: ");
	gets(password);

	printf("Choose:\n[1]Doctor\n[2]Patient\n");
	scanf("%d", &menu);

	

	switch (menu)
	{
		case 1:
		{
		if (check_username(username))
		{
			if (!check_password(password))
			{
				printf("Invalid password\n");
			}
		}
		else
			printf("Invalid username\n");
		}
		case 2:


	}

}

int main()
{
	int menu;

	do
	{
		printf("Choose operation:\n[1]Create user\n[2]Login\n[3]Password recovery\n[0]Exit\n");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			create_user();
			break;
		case 2:
			login();
			break;
		}

	} while (menu != 0);

	return 0;
}