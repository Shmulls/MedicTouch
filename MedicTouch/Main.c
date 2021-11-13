#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct doctor
{
	char user_name[20];
	char password[20];
}doctor;

void create_user()
{
	int selection;
	printf("Choose:\n[1]Patient\n[2]Doctor\n");
	scanf("%d", &selection);

	switch (selection)
	{
	case 1:
	{
		FILE* p1 = fopen("Patient.csv", "r+");
		if (p1 == NULL)
			exit(1);

		doctor data;

		printf("enter user name: ");
		scanf("%s", data.user_name);

		printf("Enter password: ");
		scanf("%s", data.password);

		//int name = 0, age = 0;
		//fscanf(fic, "%d;%d", &name, &age);
		fseek(p1, 0, SEEK_END);
		fprintf(p1, "%s,%s\n", data.user_name, data.password);
		printf(">Welcome to MedicTouch %s<\n", data.user_name);

		fclose(p1);
		break;
	}
	
	case 2:
	{
		FILE* p2 = fopen("Doctor.csv", "r+");
		if (p2 == NULL)
			exit(1);

		doctor data;

		printf("enter user name: ");
		scanf("%s", data.user_name);

		printf("Enter password: ");
		scanf("%s", data.password);

		//int name = 0, age = 0;
		//fscanf(fic, "%d;%d", &name, &age);
		fseek(p2, 0, SEEK_END);
		fprintf(p2, "%s,%s\n", data.user_name, data.password);
		printf(">Welcome to MedicTouch Dr.%s<\n", data.user_name);

		fclose(p2);
		break;
	}
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
		}

	} while (menu != 0);

	return 0;
}