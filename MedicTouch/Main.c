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
typedef struct appoinetment
{
	char date[20], time[10], id[20];
}appoinetment;

bool check_username(char username[20], int *counter);
bool check_password(char password[20], int counter);
bool check_usernamep(char username[20], int *counter);
bool check_passwordp(char password[20], int counter);
bool IsOccupied(char* time, char* date);
void create_user();
void login();
void doctor_menu();			// Hadar
void patient_menu();		// Ido
void nurse_appointment();	// Rita
void lab_appointment();		// Rita
void doctor_appointment();	// Lir
void editprofile(int select);
void AvailableAppoinetments();
void setCalendar(char* id, char* date, char* time);
int delete_product(char date[20], char time[10]);
void ViewDoc(char *id);

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

		do
		{
			printf("Enter password:\n");
			printf("notice->Password number contains 20 letters!");
			fgets(data.password, 20, stdin);
			data.password[strlen(data.password) - 1] = 0;
		} while (strlen(data.password) > 21);

		printf("Enter birthdate (in this template-->[day/month/year]):\n");
		fgets(data.date, 50, stdin);
		data.date[strlen(data.date) - 1] = 0;

		/*printf("Enter birthdate [day/month/year]:\n");
		if (scanf("%d%d%d", &data.day, &data.month, &data.year) != 1) {
			printf("\n");
		}
		fgetc(stdin);*/

		do
		{
			printf("Enter Expertise:\n");
			fgets(data.expertise, 20, stdin);
			printf("notice->Email number contains 20 letters!");
			data.expertise[strlen(data.expertise) - 1] = 0;
		} while (strlen(data.password) > 21);

		do
		{
			printf("Enter email address:\n");
			printf("notice->Email number contains 50 letters!");
			fgets(data.email, 50, stdin);
			data.email[strlen(data.email) - 1] = 0;
		} while (strlen(data.email) > 51);

		do
		{
			printf("Enter phone number:\n");
			printf("notice->Phone number contains 10 digits!");
			if (scanf(" %ld", &data.phone_number) != 1) {
				printf("\n");
			}
			fgetc(stdin);
		} while (!(data.phone_number > 9999999999 || data.phone_number < 1000000000));

		do
		{
			printf("Enter gender:\n[M] Man / [W] Woman / [O] Other:\n");
			if (scanf(" %c", &data.gender) != 1) {
			printf("\n");
			}
		fgetc(stdin);
		} while (!(data.gender == 'M' || data.gender == 'N' || data.gender == 'O'));

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

		do
		{
			printf("Enter password:\n");
			printf("notice->Password number contains 20 letters!");
			fgets(data.password, 20, stdin);
			data.password[strlen(data.password) - 1] = 0;
		} while(strlen(data.password) > 21);

		/*printf("Enter birthdate [day/month/year]:\n");
		if (scanf(" %d%d%d", &data.day, &data.month, &data.year) != 1) {
			printf("\n");
		}
		fgetc(stdin);*/

		printf("Enter birthdate (in this template-->[day/month/year]):\n");
		fgets(data.date, 50, stdin);
		data.date[strlen(data.date) - 1] = 0;

		do
		{
			printf("Enter email address:\n");
			fgets(data.email, 50, stdin);
			data.email[strlen(data.email) - 1] = 0;
		} while (strlen(data.email) > 51);
		
		do
		{
			printf("Enter phone number:\n");
			if (scanf("%ld", &data.phone_number) != 1) {
			printf("\n");
			}
			fgetc(stdin);
		} while (!(data.phone_number > 9999999999 || data.phone_number < 1000000000));


		do
		{
			printf("Enter gender:\n[M] Man / [W] Woman / [O] Other:\n");
			if (scanf(" %c", &data.gender) != 1) {
			printf("\n");
			}
		} while (!(data.gender == 'M' || data.gender == 'N' || data.gender == 'O'));

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
	fgetc(stdin);

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
		fgetc(stdin);

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
			AvailableAppoinetments();
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
	char id[20];

	do
	{
		printf("[1]Schedule an appointment to doctor\n[2]Schedule an appointment to nurse\n[3]Schedule an appointment to lab tests\n[4]Cancel an existing appointment\n[5]View a list of future appointments\n[6]Log out\n");
		if (scanf("%d", &select) != 1) {
			printf("\n");
		}
		fgetc(stdin);

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
				printf("Enter id:\n");
				fgets(id, 20, stdin);
				id[strlen(id) - 1] = 0;
				ViewDoc(&id);

				break;
			

			case 6:
			
				break;
		}
	} while (select != 6);
}
void doctor_appointment()
{
	
	char city[30], reason[200], doctortype[40], time[10], date[20], id[20];
	char *typeAP = malloc(100);
	int day, month, year, type, select;
	

	FILE* p4 = fopen("MakeAppointment.csv", "r+");
	if (p4 == NULL)
		exit(1);

	printf("Please enter ID:\n");
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = 0;

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

	/*do
	{*/
	
	AvailableAppoinetments();
	printf("Please enter date from the list:\n");
	fgets(date, 20, stdin);
	date[strlen(date) - 1] = 0;

	printf("Please enter time from the list:\n");
	fgets(time, 10, stdin);
	time[strlen(time) - 1] = 0;
	setCalendar(&id, &date, &time);

	/*printf("WORKING!!!!!! %d\n\n", delete_product(date, time));*/
	/*} while (IsOccupied(&time, &date) == false);*/


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

	fseek(p4, 0, SEEK_END);
	fprintf(p4, "%s,%s,%s,%s,%s,%s,%s\n", id, typeAP, city, doctortype, date, time, reason);
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
void AvailableAppoinetments()
{
	appoinetment data;
	FILE* p3, *p4;
	char date[20], time[10], id[20];

	char buffer[255] = { 0 };

	p3 = fopen("AvailableAppoinetments.csv","r");
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
	}
	fclose(p3);

	/*p4 = fopen("DoctorCalendar.csv", "r+");

	printf("Please enter ID:\n");
	fgets(data.id, 20, stdin);
	data.id[strlen(data.id) - 1] = 0;

	printf("Please enter date from the list:\n");
	fgets(data.date, 20, stdin);
	data.date[strlen(data.date) - 1] = 0;

	printf("Please enter time from the list:\n");
	fgets(data.time, 10, stdin);
	data.time[strlen(data.time) - 1] = 0;

	fseek(p4, 0, SEEK_END);
	fprintf(p4, "%s,%s,%s\n", data.id, data.date, data.time);

	fclose(p4);*/
}
bool IsOccupied(char *time, char *date)
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

		if (found == 1)
			break;

		while(temp != NULL)
		{
			if (found2 == 1)
				break;
			if (strcmp(temp, date) == 0)
			{
				if (found2 == 1)
					break;

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
void setCalendar(char *id, char *date, char *time)
{
	appoinetment data;
	FILE *p4;
	

	p4 = fopen("DoctorCalendar.csv", "r+"); 

	strcpy(data.id, id);
	strcpy(data.date, date);
	strcpy(data.time, time);

	fseek(p4, 0, SEEK_END);
	fprintf(p4, "%s,%s,%s\n", data.id, data.date, data.time);

	fclose(p4);
}
//int delete_product(char date[20], char time[10])
//{
//	FILE* fic = fopen("AvailableAppoinetments.csv", "r+");
//	if (fic == NULL)
//		exit(1);
//	char c = fgetc(fic), d = ' ';
//	int choice2 = atoi(date), choice3 = atoi(time);
//	int counter1 = 0, counter2 = 0;
//	appoinetment data;
//
//	FILE* fic2 = fopen("AvailableAppoinetmentsTest.csv", "w+");
//	while (counter1 != choice2)
//	{
//		putc(c, fic2);
//		c = fgetc(fic);
//		if (c == '\n')
//			counter1++;
//	}
//	while (counter2 != choice3)
//	{
//		putc(c, fic2);
//		c = fgetc(fic);
//		if (c == ';')
//			counter2++;
//	}
//	while (d != '\n' && d != ';' && d != EOF)
//	{
//		d = fgetc(fic);
//	}
//	while (!feof(fic))
//	{
//		putc(d, fic2);
//		d = fgetc(fic);
//	}
//	fclose(fic);
//	fic = fopen("AvailableAppoinetments.csv", "w");
//	fclose(fic);
//	fic = fopen("AvailableAppoinetments.csv", "r+");
//	fseek(fic2, 0, SEEK_SET);
//	c = fgetc(fic2);
//	while (!feof(fic2))
//	{
//		fputc(c, fic);
//		c = fgetc(fic2);
//	}
//	fclose(fic2);
//	fclose(fic);
//}
void nurse_appointment()
{
	char city[30], apptype[40], time[10], date[20], id[20];
	char* typeAP = malloc(100);
	int type;

	FILE* p6 = fopen("NurseAppointment.csv", "r+");
	if (p6 == NULL)
		exit(1);

	printf("Please enter ID:\n");
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = 0;

	printf("Please enter the name of the city where the clinic you want to go is located:\n");
	fgets(city, 30, stdin);
	city[strlen(city) - 1] = 0;

	printf("Please choose your preferred type of appointment:\n[1]Vaccine\n[2]Bandage change\n");
	scanf("%d", &type);
	if (type < 1 || type>2)
		printf("Error type\n");
	fgetc(stdin);

	if (type == 1)
	{
		strcpy(typeAP, "Vaccine");
	}
	if (type == 2)
	{
		strcpy(typeAP, "Bandage change");
	}

	/*AvailableAppoinetments();*/
	printf("Please enter date from the list:\n");
	fgets(date, 20, stdin);
	date[strlen(date) - 1] = 0;

	printf("Please enter time from the list:\n");
	fgets(time, 10, stdin);
	time[strlen(time) - 1] = 0;
	setCalendar(&id, &date, &time);

	fseek(p6, 0, SEEK_END);
	fprintf(p6, "%s,%s,%s,%s,%s\n", id, city, typeAP, date, time);
	printf(">The appoinetment to nurse is set!<\n\n");

	fclose(p6);
	free(typeAP);
}
void lab_appointment()
{
		char city[30], apptype[40], time[10], date[20], id[20];
		char* typeAP = malloc(100);
		int type;

		FILE* p6 = fopen("LabAppointment.csv", "r+");
		if (p6 == NULL)
			exit(1);

		printf("Please enter ID:\n");
		fgets(id, 20, stdin);
		id[strlen(id) - 1] = 0;

		printf("Please enter the name of the city where the clinic you want to go is located:\n");
		fgets(city, 30, stdin);
		city[strlen(city) - 1] = 0;

		printf("Please choose your preferred type of appointment:\n[1]Antibodies test\n[2]Urine test\n[3]Blood test\n");
		scanf("%d", &type);
		if (type < 1 || type>3)
			printf("Error type\n");
		fgetc(stdin);

		if (type == 1)
		{
			strcpy(typeAP, "Antibodies test");
		}
		if (type == 2)
		{
			strcpy(typeAP, "Urine test");
		}
		if (type == 3)
		{
			strcpy(typeAP, "Blood test");
		}

		/*AvailableAppoinetments();*/
		printf("Please enter date from the list:\n");
		fgets(date, 20, stdin);
		date[strlen(date) - 1] = 0;

		printf("Please enter time from the list:\n");
		fgets(time, 10, stdin);
		time[strlen(time) - 1] = 0;
		setCalendar(&id, &date, &time);

		fseek(p6, 0, SEEK_END);
		fprintf(p6, "%s,%s,%s,%s,%s\n", id, city, typeAP, date, time);
		printf(">The appoinetment to nurse is set!<\n\n");

		fclose(p6);
		free(typeAP);
}
void ViewDoc(char *id)
{
	appoinetment data;
	FILE* p2;
	int flag = 0, counter = 0, line = 0;

	printf("\n");

	p2 = fopen("DoctorCalendar.csv", "r");

	if (p2 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	fseek(p2, 0, SEEK_SET);
	char* temp;
	while (fgets(data.id, 20, p2))
	{
		
		temp = strtok(data.id, ",");

		if (flag == 1)
			break;

		while (temp != NULL)
		{
			counter++;
			if (counter == 3)
			{
				counter = 0;
				line++;
			}
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
		}
	}
	fclose(p2);
	

	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;

		char buffer[255] = { 0 };

		p3 = fopen("DoctorCalendar.csv", "r");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		while (fscanf(p3, "%s", buffer))
		{
			if (foundit == 1)
				break;

			sscanf(buffer, "%s,%s\n", data.time, data.date);

			if (newline == line)
			{
				puts(buffer);
				foundit = 1;
				break;
			}
			else
				newline++;
		}
		fclose(p3);
	}
	if (flag == 0)
		printf("No doctor future appoinetments\n");
}

		

