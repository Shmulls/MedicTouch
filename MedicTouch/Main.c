#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct doctor
{
	char user_name[20], password[20], expertise[20], email[50];
	int day, month, year;
	long phone_number;
	char gender;
}doctor;
typedef struct patient
{
	char user_name[20], password[20], email[50];
	int day, month, year;
	long phone_number;
	char gender;

}patient;

bool check_username(char username[20]);
bool check_password(char password[20]);
bool check_usernamep(char username[20]);
bool check_passwordp(char password[20]);
void create_user();
void login();
void doctor_menu();		// Hadar
void patient_menu();	// Ido
void nurse_appointment();		// Rita
void lab_appointment();		// Rita
void doctor_appointment();	// Lir

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
bool check_usernamep(char username[20])
{
	patient data;
	FILE* p2;
	int m, n, i, j, found = 0;

	p2 = fopen("Patient.csv", "r");

	if (p2 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	while (fgets(data.user_name, sizeof(patient), p2))
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
bool check_passwordp(char password[20])
{
	patient data;
	FILE* p3;
	int m, n, i, j, found = 0;

	p3 = fopen("Patient.csv", "r");
	if (p3 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	while (fgets(data.password, sizeof(patient), p3))
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
void create_user()
{
	int selection;
	char temp_username[20];
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

		do
		{
			printf("Enter username:\n");
			scanf("%s", data.user_name);
			strcpy(temp_username, data.user_name);
			if (check_username(temp_username))
				printf("This username already exists, try again.\n\n");
		} while (check_username(temp_username));

		printf("Enter password:\n");
		scanf("%s", data.password);

		printf("Enter birthdate [day/month/year]:\n");
		scanf("%d%d%d", &data.day, &data.month, &data.year);

		printf("Enter Expertise:\n");
		scanf("%s", data.expertise);

		printf("Enter email address:\n");
		scanf("%s", data.email);

		printf("Enter phone number:\n");
		scanf(" %ld", &data.phone_number);

		printf("Enter gender:\n [M] Man / [W] Woman / [O] Other:\n");
		scanf(" %c", &data.gender);

		fseek(p2, 0, SEEK_END);
		fprintf(p2, "%s, %s, \%d\/\%d\/\%d\, %s, %s, %ld, %c\n", data.user_name, data.password, data.day, data.month, data.year, data.expertise, data.email, data.phone_number, data.gender);

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

		do
		{
			printf("Enter username:\n");
			scanf("%s", data.user_name);
			strcpy(temp_username, data.user_name);
			if (check_usernamep(temp_username))
				printf("This username already exists, try again.\n\n");
		} while (check_usernamep(temp_username));
		

		printf("Enter password: ");
		scanf("%s", data.password);

		printf("Enter birthdate [day/month/year]:\n");
		scanf("%d%d%d", &data.day, &data.month, &data.year);

		printf("Enter email address:\n");
		scanf("%s", data.email);

		printf("Enter phone number:\n");
		scanf("%ld", &data.phone_number);

		printf("Enter gender:\n [M] Man / [W] Woman / [O] Other:\n");
		scanf(" %c", &data.gender);

		fseek(p1, 0, SEEK_END);
		fprintf(p1, "% s, % s, \%d\/\% d\/\%d\, % s, % ld, % c", data.user_name, data.password, data.day, data.month, data.year, data.email, data.phone_number, data.gender);
		printf(">Welcome to MedicTouch %s<\n", data.user_name);

		fclose(p1);
		break;
	}
	}
}
void login()
{
	char username[20] = { 0 }, password[20] = { 0 };
	int menu;
	printf("---->LOGIN AREA<----\n\n");
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
				printf("Invalid password\n\n");
			}
			else
			{
				printf("Welcome to MedicTouch Dr.%s!\n\n", username);
				void doctor_menu();
			}
		}
		else
			printf("Invalid username\n\n");
		break;
	}

	case 2:
	{
		if (check_usernamep(username))
		{
			if (!check_passwordp(password))
			{
				printf("Invalid password\n\n");
			}
			else
			{
				printf("Welcome to MedicTouch %s!\n\n", username);
				void patient_menu();
			}
		}
		else
			printf("Invalid username\n\n");
		break;
	}
	}
}
void doctor_menu()
{
	//Hadar

	int select;
	printf("[1]Edit doctor profile\n[2]Doctor calendar\n[3]Return to main menu\n");

	scanf("%d", &select);

	do 
	{
		switch (select)
		{
		case 1:
		{
			break;
		}

		case 2:
		{
			break;
		}

		case 3:
		{
			return;
			break;
		}

		}
	} while (select != 3);
}
void patient_menu()
{
	//Ido
	//Call lir requirements functions (4) 
	//Call Rita requirements functions (5,6) 
	int select;
	printf("[1]Schedule an appointment to doctor\n[2]Schedule an appointment to nurse\n[3]Schedule an appointment to lab tests\n[4]Cancel an existing appointment\n[5]Choose the appointment\n[6]Choose another date for new appointment\n[7]View a list of future appointments\n[8]Return to main menu\n");

	scanf("%d", &select);

	do
	{
		switch (select)
		{
			case 1:
			{	
				doctor_appointment();	
				break;
			}

			case 2:
			{
				nurse_appointment();
				break;
			}

			case 3:
			{
				lab_appointment();
				break;
			}

			case 4:
			{
				break;
			}

			case 5:
			{
				break;
			}

			case 6:
			{
				break;
			}

			case 7:
			{
				break;
			}

			case 8:
			{
				return;
				break;
			}

		}
	} while (select != 8);
}
void nurse_appointment() 
{

}
void lab_appointment()
{

}
void doctor_appointment()
{

}