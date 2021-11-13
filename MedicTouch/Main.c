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
	FILE* fic = fopen("Doctor.csv", "r+");
	if (fic == NULL)
	exit(1);

	doctor data;

	printf("enter user name: ");
	scanf("%s", data.user_name);

	printf("Enter password: ");
	scanf("%s", data.password);

	//int name = 0, age = 0;
	//fscanf(fic, "%d;%d", &name, &age);
	fseek(fic, 0, SEEK_END);
	fprintf(fic, "%s,%s\n", data.user_name, data.password);
	printf("username: %s\npassword: %s\n", data.user_name, data.password);

	fclose(fic);
}

int main()
{
	int menu;

	do
	{
		printf("choose operation: ");
		scanf("%d", &menu);

		switch (menu)
		{
			case 1: 
				create_user();
		}

	} while (menu != 0);

	return 0;
}