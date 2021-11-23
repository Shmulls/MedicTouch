#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DELIM ",\n"

//ddd

typedef struct doctor
{
	char user_name[20], password[20], expertise[20], email[50], date[50];
	int day, month, year;
	long phone_number;
	char gender;
}doctor;
typedef struct patient
{
	char user_name[20], password[20], email[50], date[50];
	int day, month, year;
	long phone_number;
	char gender;

}patient;

bool check_username(char username[20], int *counter);
bool check_password(char password[20], int counter);
bool check_usernamep(char username[20], int *counter);
bool check_passwordp(char password[20], int counter);
void create_user();
void login();
void doctor_menu();			// Hadar
void patient_menu();		// Ido
void nurse_appointment();	// Rita
void lab_appointment();		// Rita
void doctor_appointment();	// Lir
void editprofile(int select);
void doctorcalendar();
bool IsOccupied(char *time, char* date);
void setCalendar(char *time, char *date);

int main()
{
	int menu;

	do
	{
		printf("Choose operation:\n[1]Create user\n[2]Login\n[3]Password recovery\n[0]Exit\n");
		if (scanf("%d", &menu) != 1) {
			printf("\n");
		}
		fgetc(stdin);

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
bool check_username(char username[20], int *counter)
{
	doctor data;
	FILE* p2;
	int found = 0, rawcounter = 0;

	p2 = fopen("Doctor.csv", "r");

	if (p2 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	fseek(p2, 65, SEEK_SET);

	while (fgets(data.user_name, 20, p2))
	{
		char* temp;
		temp = strtok(data.user_name, ",");

		if (found == 1)
			break;

		while (temp != NULL)
		{
			rawcounter++;
			if (strcmp(temp, username) == 0)
			{
				found = 1;
				break;
			}
			temp = strtok(NULL, ",");
		}
	}
	*counter = rawcounter;
	fclose(p2);
	if (found == 1)
		return true;
	else
		return false;
}
bool check_password(char password[20], int counter)
{
	doctor data;
	FILE* p3;
	int found = 0, rawcounter = 0;

	p3 = fopen("Doctor.csv", "r");
	if (p3 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	fseek(p3, 65, SEEK_SET);

	while (fgets(data.password, 20, p3))
	{
		char* temp;
		temp = strtok(data.password, ",");

		if (found == 1)
			break;

		while (temp != NULL)
		{
			if (rawcounter > (counter + 5)) //this method used for search by line data of the user. if the search method finish to read user data raw the program will break;
			{
				break;
			}
			else
			{
				rawcounter++;
				if (strcmp(temp, password) == 0)
				{
					if (rawcounter < counter) //this method will ensure that the password check will be will search only in the correct raw.
						return false;
					else
					{
						found = 1;
						break;
					}
				}
				temp = strtok(NULL, ",");
			}
		}
	}
	fclose(p3);
	if (found == 1)
		return true;
	else
		return false;
}
bool check_usernamep(char username[20], int *counter)
{
	patient data;
	FILE* p2;
	int found = 0, rawcounter = 0;

	p2 = fopen("Patient.csv", "r");

	if (p2 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	fseek(p2, 54, SEEK_SET);

	while (fgets(data.user_name, 20, p2))
	{
		char* temp;
		temp = strtok(data.user_name, ",");

		if (found == 1)
		break;

		while (temp != NULL)
		{
			rawcounter++;
			if (strcmp(temp, username) == 0)
			{
				found = 1;
				break;
			}
			temp = strtok(NULL, ",");
		}
	}
	*counter = rawcounter;
	fclose(p2);
	if (found == 1)
		return true;
	else
		return false;
}
bool check_passwordp(char password[20], int counter)
{
	patient data;
	FILE* p3;
	int rawcounter = 0, found = 0;

	p3 = fopen("Patient.csv", "r");
	if (p3 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	fseek(p3, 54, SEEK_SET);

	while (fgets(data.password, 20, p3))
	{
		char* temp;
		temp = strtok(data.password, ",");

		while (temp != NULL)
		{
			if (found == 1)
				break;
			if (rawcounter > (counter + 5)) //this method used for search by line data of the user. if the search method finish to read user data raw the program will break;
			{
				break;
			}
			else
			{
				rawcounter++;
				if (strcmp(temp, password) == 0)
				{
					if (rawcounter < counter) //this method will ensure that the password check will be will search only in the correct raw.
						return false;
					else
					{
						found = 1;
						break;
					}
				}
				temp = strtok(NULL, ",");
			}
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
	if (scanf("%d", &selection) != 1) {
		printf("\n");
	}
	fgetc(stdin);

	switch (selection)
	{
	case 1:
	{
		doctor data;
		int counter = 0;
		FILE* p2 = fopen("Doctor.csv", "r+");
		if (p2 == NULL)
			exit(1);
		do
		{
			printf("Enter username:\n");
			fgets(data.user_name, 20, stdin);
			data.user_name[strlen(data.user_name) - 1] = 0;
			strcpy(temp_username, data.user_name);
			if (check_username(temp_username, &counter))
				printf("This username already exists, try again.\n\n");
		} while (check_username(temp_username, &counter));

		printf("Enter password:\n");
		fgets(data.password, 20, stdin);
		data.password[strlen(data.password) - 1] = 0;

		printf("Enter birthdate (in this template-->[day/month/year]):\n");
		fgets(data.date, 50, stdin);
		data.date[strlen(data.date) - 1] = 0;

		/*printf("Enter birthdate [day/month/year]:\n");
		if (scanf("%d%d%d", &data.day, &data.month, &data.year) != 1) {
			printf("\n");
		}
		fgetc(stdin);*/

		printf("Enter Expertise:\n");
		fgets(data.expertise, 20, stdin);
		data.expertise[strlen(data.expertise) - 1] = 0;

		printf("Enter email address:\n");
		fgets(data.email, 50, stdin);
		data.email[strlen(data.email) - 1] = 0;

		printf("Enter phone number:\n");
		if (scanf(" %ld", &data.phone_number) != 1) {
			printf("\n");
		}
		fgetc(stdin);

		printf("Enter gender:\n[M] Man / [W] Woman / [O] Other:\n");
		if (scanf(" %c", &data.gender) != 1) {
			printf("\n");
		}
		fgetc(stdin);

		fseek(p2, 0, SEEK_END);
		/*fprintf(p2, "%s,%s,\%d\/\%d\/\%d\,%s,%s,%ld,%c\n", data.user_name, data.password, data.day, data.month, data.year, data.expertise, data.email, data.phone_number, data.gender);*/
		fprintf(p2, "%s,%s,%s,%s,%s,%ld,%c\n", data.user_name, data.password, data.date, data.expertise, data.email, data.phone_number, data.gender);

		printf(">Welcome to MedicTouch Dr.%s<\n", data.user_name);

		fclose(p2);
		break;
	}
	case 2:
	{
		patient data;
		int counter = 0;
		FILE* p1 = fopen("Patient.csv", "r+");
		if (p1 == NULL)
			exit(1);

		do
		{
			printf("Enter username:\n");
			fgets(data.user_name, 20, stdin);
			data.user_name[strlen(data.user_name) - 1] = 0;
			strcpy(temp_username, data.user_name);
			if (check_usernamep(temp_username, &counter))
				printf("This username already exists, try again.\n\n");
		} while (check_usernamep(temp_username, &counter));
		
		printf("Enter password:\n");
		fgets(data.password, 20, stdin);
		data.password[strlen(data.password) - 1] = 0;

		/*printf("Enter birthdate [day/month/year]:\n");
		if (scanf(" %d%d%d", &data.day, &data.month, &data.year) != 1) {
			printf("\n");
		}
		fgetc(stdin);*/

		printf("Enter birthdate (in this template-->[day/month/year]):\n");
		fgets(data.date, 50, stdin);
		data.date[strlen(data.date) - 1] = 0;

		printf("Enter email address:\n");
		fgets(data.email, 50, stdin);
		data.email[strlen(data.email) - 1] = 0;
		
		printf("Enter phone number:\n");
		if (scanf("%ld", &data.phone_number) != 1) {
			printf("\n");
		}
		fgetc(stdin);

		printf("Enter gender:\n[M] Man / [W] Woman / [O] Other:\n");
		if (scanf(" %c", &data.gender) != 1) {
			printf("\n");
		}

		fseek(p1, 0, SEEK_END);
		/*fprintf(p1, "%s,%s,\%d\/\%d\/\%d\,%s,%ld,%c\n", data.user_name, data.password, data.day, data.month, data.year, data.email, data.phone_number, data.gender);*/
		fprintf(p1, "%s,%s,%s,%s,%ld,%c\n", data.user_name, data.password, data.date, data.email, data.phone_number, data.gender);
		printf(">Welcome to MedicTouch %s<\n", data.user_name);

		fclose(p1);
		break;
	}
	}
}
void login()
{
	char username[20] = { 0 }, password[20] = { 0 };
	int menu, counter = 0;
	printf("---->LOGIN AREA<----\n\n");
	printf("Enter username: ");
	fgets(username, 20, stdin);
	username[strlen(username) - 1] = 0;

	printf("Enter password: ");
	fgets(password, 20, stdin);
	password[strlen(password) - 1] = 0;

	printf("Choose:\n[1]Doctor\n[2]Patient\n");
	if (scanf("%d", &menu) != 1) {
		printf("\n");
	}

	switch (menu)
	{
	case 1:
	{
		if (check_username(username, &counter))
		{
			if (!check_password(password, counter))
			{
				printf("Invalid password\n\n");
			}
			else
			{
				printf("Welcome to MedicTouch Dr.%s!\n\n", username);
				doctor_menu();
			}
		}
		else
			printf("Invalid username\n\n");
		break;
	}

	case 2:
	{
		if (check_usernamep(username, &counter))
		{
			if (!check_passwordp(password, counter))
			{
				printf("Invalid password\n\n");
			}
			else
			{
				printf("Welcome to MedicTouch %s!\n\n", username);
				patient_menu();
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

	do 
	{
		
		printf("[1]Edit doctor profile\n[2]Doctor calendar\n[3]Return to main menu\n");
		if (scanf("%d", &select) != 1) {
			printf("\n");
		}
		switch (select)
		{
		case 1:
		{
			int select;
			printf("Choose section to update in your profile\n");
			printf("[1]City\n[2]Birthdate\n[3]Email\n[4]Expertise\n[5]Phone number\n");
			if (scanf("%d", &select) != 1) {
				printf("\n");
			}

			editprofile(select);
		}

		case 2:
		{
			doctorcalendar();
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

	do
	{
		printf("[1]Schedule an appointment to doctor\n[2]Schedule an appointment to nurse\n[3]Schedule an appointment to lab tests\n[4]Cancel an existing appointment\n[5]Choose the appointment\n[6]Choose another date for new appointment\n[7]View a list of future appointments\n[8]Return to main menu\n");
		if (scanf("%d", &select) != 1) {
			printf("\n");
		}

		switch (select)
		{
			case 1:
				doctor_appointment();	
				break;
			

			case 2:
				nurse_appointment();
				break;
			

			case 3:
				lab_appointment();
				break;
			

			case 4:
			
				break;
			

			case 5:
			
				break;
			

			case 6:
			
				break;
			

			case 7:
			
				break;
			

			case 8:
			
				break;
			

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
	
	char city[30], reason[200], doctortype[40], time[20], date[50], reminder[10];
	char *typeAP = malloc(100);
	int day, month, year, type, select;
	FILE* p4 = fopen("DoctorAppointment.csv", "r+");
	if (p4 == NULL)
		exit(1);

	printf("Please choose your preferred type of appointment:\n[1]Face to face appointment\n[2]Phone appointment\n");
	if (scanf("%d", &type) != 1) {
		printf("\n");
	}
	fgetc(stdin);

	if (type == 1)
	{
		strcpy(typeAP, "Face to face");
		printf("Please enter the name of the city where the clinic you want to go is located:\n");
		fgets(city, 30, stdin);
		city[strlen(city) - 1] = 0;
	}
	else
	{
		strcpy(typeAP, "Phone");
	}

	printf("Please enter the type of doctor you would like to make an appointment with:\n");
	fgets(doctortype, 40, stdin);
	doctortype[strlen(doctortype) - 1] = 0;

	do
	{
		/*printf("Please enter the date you want to make the appointment: [day/month/year]:\n");
		if (scanf("%d%d%d", &day, &month, &year) != 1) {
			printf("\n");
		}
		fgetc(stdin);*/

		printf("Enter date for the appoinetment (in this template-->[day/month/year]):\n");
		fgets(date, 50, stdin);
		date[strlen(date) - 1] = 0;

		/*if (IsOccupied) {
		printf("Sorry, this day is occupied, please try another one:\n")
		scanf("%d%d%d", &day, &month, &year);
		*/

		printf("Please enter the time you want to make the appointment:\n->Notice: the appointment are scheduled every half hour, so choose Round or half hour\n");
		fgets(time, 20, stdin);
		time[strlen(time) - 1] = 0;
	} while (IsOccupied(&time, &date) == false);


	printf("Do you want sumbit a reason for the appoinetment?\n[1]Yes\n[2]No\n");
	if (scanf("%d", &type) != 1) {
		printf("\n");
	}
	fgetc(stdin);
	
	if (type == 1)
	{
		printf("Please the reason for the appoinetment\n->Notice: you can sumbit only 200 charcters\n");
		fgets(reason, 200, stdin);
		reason[strlen(reason) - 1] = 0;
	}
	else
	{
		strcpy(reason, "N/A");
	}

	printf("Would you like to receive a phone reminder day before the appointment?\nPlease choose:\n[1]Yes\n[2]No\n");
	if (scanf("%d", &select) != 1) {
		printf("\n");
	}
	fgetc(stdin);

	if (select == 1)
		strcpy(reminder, "Yes");
	else
		strcpy(reminder, "No");

	fseek(p4, 0, SEEK_END);
	/*fprintf(p4, "%s,%s,%s,\%d\/\%d\/\%d\,%s,%s,%c\n", typeAP, city, doctortype, day, month, year, time, reason, reminder);*/
	fprintf(p4, "%s,%s,%s,%,%s,%s,%s\n", typeAP, city, doctortype, date, time, reason, reminder);
	setCalendar(&time, &date);
	printf(">The appoinetment is set!<\n\n");

	fclose(p4);
	free(typeAP);
}
void editprofile(int select)
{
	printf("[1]City\n[2]Birthdate\n[3]Email\n[4]Expertise\n[5]Phone number\n");

	switch (select)
	{
		case 1:	
		{
			doctor data;
			FILE* p3;
			int found = 0;
			char email[50];

			fgets(email, 50, stdin);
			email[strlen(email) - 1] = 0;

			p3 = fopen("Doctor.csv", "r");
			if (p3 == NULL)
			{
				printf("Error opening file\n");
				exit(1);
			}

			while (fgets(data.email, 50, p3))
			{
				char* temp;
				temp = strtok(data.email, ",");

				while (temp != NULL)
				{
					if (strcmp(temp, email) == 0)
					{
						found = 1;
						break;
					}
					temp = strtok(NULL, ",");
				}
			}
			fclose(p3);
		}
				
		break;
	}
}
void doctorcalendar()
{
	patient data;
	FILE* p3;

	char buffer[255] = { 0 };
	p3 = fopen("DoctorCalendar.csv","r");
	if (p3 == NULL)
	{
		printf("\n Failed to open file!");
	}
	else 
	{
		while ((fgets(buffer, 255, p3)) != NULL /*&& fgetc(p3) != EOF */ )
		{
			puts(buffer);
			/* Some processing */
		}
		fclose(p3);
	}
	//DoctorCalendar
}

bool IsOccupied(char *time, char* date)
{
	doctor data;
	int found = 0, found2 = 0;
	FILE* p6;
	
	p6 = fopen("DoctorCalendar.csv", "r");
	if (p6 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	/*fseek(p3, 54, SEEK_SET);*/

	fseek(p6, 0, SEEK_SET);

	while (fgets(date, 20, p6))
	{
		char* temp, *temp2;
		temp = strtok(date, ",");

		while(temp != NULL)
		{
			if (found2 == 1)
				break;
			if (strcmp(temp, date) == 0)
			{
						found = 1;
						temp2 = strtok(time, ",");
						while (temp2 != NULL)
						{
							if (strcmp(temp2, time) == 0)
							{
								found2 = 1;
								break;
							}
							temp2 = strtok(NULL, ",");
						}
			}
			temp = strtok(NULL, ",");
		}
	}

	fclose(p6);
	if (found == 1 && found2 == 1)
		printf("Time not avaibile\n");
		return false;
	if (found == 1 && found2 == 0)
		return true;
	if (found == 0 && found2 == 0)
		return true;
}

void setCalendar(char *time, char* date)
{
		FILE* p6 = fopen("DoctorCalendar.csv", "r+");
		if (p6 == NULL)
		{
			printf("Faild open DoctorCalendar.csv\n");
			exit(1);
		}

		fseek(p6, 0, SEEK_END);
		fprintf(p6, "%s,%s\n", date, time);
		fclose(p6);
}