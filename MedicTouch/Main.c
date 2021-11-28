#define _CRT_SECURE_NO_WARNINGS
#define ROWS 5
#define COLS 18
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
	long phone_number;
	char gender;

}patient;
typedef struct appoinetment
{
	char date[20], id[20];
	char **time;

}appoinetment;

appoinetment *globaldata = NULL;

//Visitor
void create_user();
void login();
void RebootAppoinetmentsDoc();
//void PasswordRecovery(char username[]);

//Patient
bool check_usernamep(char username[20], int* counter);
bool check_passwordp(char password[20], int counter);
bool OccupiedApp(char date[], char time[]);
bool IsOccupied(char* time, char* date);
bool findtime(appoinetment globalobj, char time[], int* index);
char** Loadtime();
void UpdateAPfile();
void SortimeArray(char** timez);
void UpdateAppoinetments();
void patient_menu();
void doctor_appointment();
void setCalendar(char id[], char date[], char time[]);
void printfAvailableAppoinetments();

//Doctor
bool check_username(char username[20], int* counter);
bool check_password(char password[20], int counter);
void doctor_menu();
void printfCalendar();
void ViewDoc(char* id);
void editprofile(int select);
void CancelDoctor(char* id);

//Nurse
void nurse_appointment();
void RebootAppoinetmentsNurse();
void printfAvailableAppoinetmentsNurse();
void setCalendarNurse(char id[], char date[], char time[]);
void ViewNurse(char* id);
void CancelNurse(char id[]);

//Lab
void lab_appointment();
void RebootAppoinetmentsLab();
void printfAvailableAppoinetmentsLab();
void setCalendarLab(char id[], char date[], char time[]);
void CancelLab(char* id);
void ViewLab(char* id);

//Main
int main()
{
	int menu;
	/*RebootAppoinetmentsDoc();*/
	UpdateAppoinetments();
	char newuser[20];

	do
	{
		printf("\nChoose operation:\n[1]Create user\n[2]Login\n[0]Exit\n");
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

//Visitor
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
			printf("notice->Password number contains 20 letters!\n");
			fgets(data.password, 20, stdin);
			data.password[strlen(data.password) - 1] = 0;
		} while (strlen(data.password) > 21);

		printf("Enter birthdate (in this template-->[XX/XX/XXXX]):\n");
		fgets(data.date, 50, stdin);
		data.date[strlen(data.date) - 1] = 0;

		do
		{
			printf("Enter Expertise:\n");
			printf("notice->Expertise number contains 20 letters!\n");
			fgets(data.expertise, 20, stdin);
			data.expertise[strlen(data.expertise) - 1] = 0;
		} while (strlen(data.password) > 21);

		do
		{
			printf("Enter email address:\n");
			printf("notice->Email contains 50 letters!\n");
			fgets(data.email, 50, stdin);
			data.email[strlen(data.email) - 1] = 0;
		} while (strlen(data.email) > 51);

		do
		{
			printf("Enter phone number:\n");
			printf("notice->Phone number contains 10 digits!\n");
			if (scanf(" %ld", &data.phone_number) != 1) {
				printf("\n");
			}
			fgetc(stdin);
		} while (!(data.phone_number > 9999999999 || data.phone_number < 1000000000));

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

		do
		{
			printf("Enter password:\n");
			printf("notice->Password number contains 20 letters!\n");
			fgets(data.password, 20, stdin);
			data.password[strlen(data.password) - 1] = 0;
		} while (strlen(data.password) > 21);

		/*printf("Enter birthdate [day/month/year]:\n");
		if (scanf(" %d%d%d", &data.day, &data.month, &data.year) != 1) {
			printf("\n");
		}
		fgetc(stdin);*/

		printf("Enter birthdate (in this template-->[XX/XX/XXXX]):\n");
		fgets(data.date, 50, stdin);
		data.date[strlen(data.date) - 1] = 0;

		do
		{
			printf("Enter email address:\n");
			printf("notice->Email contains 50 letters!\n");
			fgets(data.email, 50, stdin);
			data.email[strlen(data.email) - 1] = 0;
		} while (strlen(data.email) > 51);

		do
		{
			printf("Enter phone number:\n");
			printf("notice->phone number contains 10 digits!\n");
			if (scanf("%ld", &data.phone_number) != 1) {
				printf("\n");
			}
			fgetc(stdin);
		} while (!(data.phone_number > 9999999999 || data.phone_number < 1000000000));


		
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
void RebootAppoinetmentsDoc()
{
	FILE* p3;
	const char* date0, * date1, * date2, * date3, * date4;
	int counter = 1, max = 0;
	char* dates[5] = { "05/12/21" ,"06/12/21" ,"07/12/21" ,"08/12/21" ,"09/12/21" };

	p3 = fopen("AvailableAppoinetments.csv", "w");
	if (p3 == NULL)
	{
		printf("\nAvailableAppoinetments.csv failed.\n");
		exit(1);
	}

	globaldata = (appoinetment*)malloc(5 * sizeof(appoinetment));

	char** temp = Loadtime();
	SortimeArray(temp);

	for (int i = 0; i < ROWS; i++)
	{
		if (max == 1)
			fprintf(p3, "\n", globaldata[i].time[counter]);

		counter = 0;
		strcpy(globaldata[i].date, dates[i]);
		fprintf(p3, "%s,", globaldata[i].date);

		while (counter < 17)
		{
			if (counter == 16)
			{
				fprintf(p3, "%s", globaldata[i].time[counter]);
				max = 1;
			}
			else
				fprintf(p3, "%s,", globaldata[i].time[counter]);
			counter++;
		}
	}
	fclose(p3);
}
void PasswordRecovery(char username[])
{
	FILE* p1, *p2;
	int found = 0;
	int Counter = 0;
	char tempword[20], newuser[20];

	char buffer[255] = { 0 };

	p1 = fopen("Patient.csv", "r");
	if (p1 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	p2 = fopen("Temp.csv", "w");
	if (p2 == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	while (fgets(buffer, sizeof(buffer), p1))
	{
		char* temp;
		temp = strtok(buffer, ",");

		while (temp != NULL)
		{

			if (strcmp(temp, username) == 0)
			{
					printf("Enter username:\n");
					fgets(newuser, 20, stdin);
					newuser[strlen(newuser) - 1] = 0;
					fprintf(p2, "%s,", newuser);
					temp = strtok(NULL, ",");
			}
			fprintf(p2, "%s,", temp);
			Counter++;
			temp = strtok(NULL, ",");
		}
	}
	fclose(p1);
	fclose(p2);
	
}

//Patient
bool check_usernamep(char username[20], int* counter)
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
bool IsOccupied(char* time, char* date)
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
		char* temp, * temp2;
		temp = strtok(date, ",");

		if (found == 1)
			break;

		while (temp != NULL)
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
bool OccupiedApp(char date[], char time[])
{
	FILE* fic = fopen("AvailableAppoinetments.csv", "r");
	if (fic == NULL)
		exit(1);
	int index = -1;
	int counter;

	for (int i = 0; i < 5; i++)
	{
		if (strcmp(globaldata[i].date, date) == 0)
		{
			if (findtime(globaldata[i], time, &index))
			{
				UpdateAPfile();
				break;
			}
		}
	}
}
bool findtime(appoinetment globalobj, char time[], int* index)
{
	int counter = 0;

	while (counter < 17)
	{
		if (strcmp(globalobj.time[counter], time) == 0)
		{
			index = 1;
			strcpy(globalobj.time[counter], "N/A");
			return true;
		}
		counter++;
	}

	return false;
}
char** Loadtime()
{
	int numcols;
	char timz[8];
	FILE* p1 = fopen("time.txt", "r");
	if (!p1)
	{
		printf("\nError, can't open your file");
		return;
	}
	fscanf(p1, "%d", &numcols);
	char** insertime = (char**)malloc(sizeof(char*) * numcols);

	for (int i = 0; i < numcols; i++)
	{
		fscanf(p1, "%s", timz);
		insertime[i] = (char*)malloc(sizeof(char) * (strlen(timz) + 1));
		strcpy(insertime[i], timz);

	}
	fclose(p1);

	return insertime;
}
void UpdateAPfile()
{
	FILE* p3;
	int counter = 0;

	p3 = fopen("AvailableAppoinetments.csv", "w");
	if (p3 == NULL)
	{
		printf("\nAvailableAppoinetments.csv failed.\n");
		exit(1);
	}

	for (int i = 0; i < ROWS; i++)
	{
		counter = 0;
		fprintf(p3, "%s,", globaldata[i].date);

		while (counter < 17)
		{
			if (counter == 16)
			{
				fprintf(p3, "%s", globaldata[i].time[counter]);
			}
			else
				fprintf(p3, "%s,", globaldata[i].time[counter]);
			counter++;
		}
	}
	fclose(p3);
}
void SortimeArray(char** timez)
{
	for (int i = 0; i < 5; i++)
	{
		globaldata[i].time = (char**)malloc(sizeof(char*) * 18);
		for (int j = 0; j < 18; j++)
		{
			globaldata[i].time[j] = (char*)malloc(sizeof(char) * (strlen(timez[j]) + 1));
			strcpy(globaldata[i].time[j], timez[j]);
		}
	}
}
void UpdateAppoinetments()
{
	int counter = 1;
	char timz[10], date[20], buffer[3000];
	int size = 0, found = 0, seccount = 0;
	FILE* p3 = fopen("AvailableAppoinetments.csv", "r");
	if (!p3)
	{
		printf("\nAvailableAppoinetments.csv - Error, cant open the file\n");
		printf("Rebooting AvailableAppoinetments.csv...\n");
		RebootAppoinetmentsDoc();
		return;
	}

	globaldata = (appoinetment*)malloc(sizeof(appoinetment) * ROWS);

	for (int i = 0; i < 5; i++)
	{
		globaldata[i].time = (char**)malloc(sizeof(char*) * 17);
	}


	while (fgets(buffer, sizeof(buffer), p3))
	{
		if (seccount == 90)
			break;

		char* temp;
		temp = strtok(buffer, ",");

		while (temp != NULL)
		{
			if (seccount == 90)
				break;
			found = 0;

			for (int i = size; i < ROWS; i++)
			{
				if (found == 1)
					break;
				counter = 0;

				strcpy(globaldata[i].date, temp);
				seccount++;
				temp = strtok(NULL, ",");

				while (counter < 17)
				{
					if (counter == 16)
					{
						globaldata[i].time[counter] = (char*)malloc(sizeof(char) * (strlen(timz) + 1));
						strcpy(globaldata[i].time[counter], temp);
						size++;
						found = 1;
						seccount++;
						temp = strtok(NULL, ",");
					}
					else
					{
						globaldata[i].time[counter] = (char*)malloc(sizeof(char) * (strlen(timz) + 1));
						strcpy(globaldata[i].time[counter], temp);
						seccount++;
						temp = strtok(NULL, ",");
					}
					counter++;
				}

			}
		}
	}
	fclose(p3);


	//for (int i = 0; i < ROWS; i++)
	//{

	//	counter = 0;
	//	printf("%s,", globaldata[i].date);

	//	while (counter < 17)
	//	{
	//		if (counter == 16)
	//		{
	//			printf("%s", globaldata[i].time[counter]);
	//		}
	//		else
	//		{
	//			printf("%s,", globaldata[i].time[counter]);
	//		}
	//		counter++;
	//	}

	//}

	FILE* p4;
	int countmax = 1;


	p4 = fopen("AvailableAppoinetmentsTest.csv", "w");
	if (p4 == NULL)
	{
		printf("\nAvailableAppoinetmentsTest.csv failed.\n");
		exit(1);
	}

	for (int i = 0; i < ROWS; i++)
	{
		countmax = 0;
		fprintf(p4, "%s,", globaldata[i].date);

		while (countmax < 17)
		{
			if (countmax == 16)
			{
				fprintf(p4, "%s", globaldata[i].time[countmax]);
			}
			else
				fprintf(p4, "%s,", globaldata[i].time[countmax]);
			countmax++;
		}
	}
	fclose(p3);
}
void patient_menu()	
{
	int select, choice;
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
			printf("\nPlease enter which appoinetment to cancel:\n[1]Doctor\n[2]Nurse\n[3]Lab\n");
			scanf("%d", &choice);
			fgetc(stdin);

			printf("\nEnter id:\n");
			fgets(id, 20, stdin);
			id[strlen(id) - 1] = 0;

			if(choice == 1)
				CancelDoctor(&id);
			if (choice == 2)
				CancelNurse(&id);
			if (choice == 3)
				CancelLab(&id);
			break;


		case 5:
			printf("\nEnter id:\n");
			fgets(id, 20, stdin);
			id[strlen(id) - 1] = 0;
			printf("\n---------------------------\n");
			ViewDoc(&id);
			ViewNurse(&id);
			ViewLab(&id);
			printf("---------------------------\n");

			break;
		case 6:
			break;
		}
	} while (select != 6);
}
void doctor_appointment()
{

	char city[30], reason[200], doctortype[40], time[10], date[20], id[20];
	char* typeAP = malloc(100);
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
		strcpy(city, "N/A");
	}

	printf("Please enter the type of doctor you would like to make an appointment with:\n");
	fgets(doctortype, 40, stdin);
	doctortype[strlen(doctortype) - 1] = 0;

	printfAvailableAppoinetments();
	printf("Please enter date from the list:\n");
	printf("notice->Template for date is: STRING->[XX/XX/XX]\n");
	fgets(date, 20, stdin);
	date[strlen(date) - 1] = 0;

	printf("Please enter time from the list:\n");
	printf("notice->Template for time is: STRING->[XX:XX]\n");
	fgets(time, 10, stdin);
	time[strlen(time) - 1] = 0;

	if (OccupiedApp(date, time))
		printf("Date\Time not avaible!\n");
	setCalendar(id, date, time);

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
void setCalendar(char id[], char date[], char time[])
{
	appoinetment data;
	FILE* p4;

	p4 = fopen("DoctorCalendar.csv", "r+");

	fseek(p4, 0, SEEK_END);
	fprintf(p4, "%s,%s,%s\n", id, date, time);

	fclose(p4);
}
void printfAvailableAppoinetments()
{
	appoinetment data;
	FILE* p3;

	char buffer[255] = { 0 };

	p3 = fopen("AvailableAppoinetments.csv", "r");
	if (p3 == NULL)
	{
		printf("\n Failed to open file!");
	}
	else
	{
		printf("\n");
		while ((fgets(buffer, 255, p3)) != NULL /*&& fgetc(p3) != EOF */)
		{
			puts(buffer);
			/* Some processing */
		}
	}
	fclose(p3);
}

//Doctor
bool check_username(char username[20], int* counter)
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
void doctor_menu()
{
	int select;

	do
	{
		printf("\n");
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
			printfCalendar();
			/*RebootAppoinetments();*/
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
void printfCalendar()
{
	appoinetment data;
	FILE* p3;

	char buffer[255] = { 0 };

	p3 = fopen("DoctorCalendar.csv", "r");
	if (p3 == NULL)
	{
		printf("\n Failed to open file!");
	}
	else
	{
		printf("\n");

		while ((fgets(buffer, 255, p3)) != NULL)
		{
			puts(buffer);
			
		}
	}
	fclose(p3);
}
void ViewDoc(char* id)
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
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
			counter++;
		}
	}
	fclose(p2);


	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;
		int newCounter = 0;

		char buffer[255] = { 0 };

		p3 = fopen("DoctorCalendar.csv", "r");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		printf("Doctor Appoinetments are:\n");
		while (fgets(buffer, sizeof(buffer), p3))
		{
			if (foundit == 2)
				break;

			char* temp;
			temp = strtok(buffer, ",");

			while (temp != NULL)
			{
				if (foundit == 2)
					break;

				if (newCounter == (counter + 1))
				{
					puts(temp);
					foundit++;
				}
				if (newCounter == (counter + 2))
				{
					puts(temp);
					foundit++;
				}
				newCounter++;
				temp = strtok(NULL, ",");
			}
		}
		fclose(p3);
	}
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

		p3 = fopen("Doctor.csv", "r+");
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
void CancelDoctor(char* id)
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
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
			counter++;
		}
	}
	fclose(p2);


	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;
		int newCounter = 0;
		char* remove;
		remove = " ";

		char buffer[255] = { 0 };

		p3 = fopen("DoctorCalendar.csv", "w");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		fseek(p3, 13, SEEK_SET);
		while (fgets(buffer, sizeof(buffer), p3))
		{
			if (foundit == 3)
				break;

			char* temp;
			temp = strtok(buffer, ",");

			while (temp != NULL)
			{
				if (foundit == 2)
					break;

				if (newCounter == (counter))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				if (newCounter == (counter + 1))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				if (newCounter == (counter + 2))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				newCounter++;
				temp = strtok(NULL, ",");
			}
		}
		fclose(p3);
	}
}

//Nurse
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

	printfAvailableAppoinetmentsNurse();
	printf("Please enter date from the list:\n");
	printf("notice->Template for date is: STRING->[XX/XX/XXXX]\n");
	fgets(date, 20, stdin);
	date[strlen(date) - 1] = 0;

	printf("Please enter time from the list:\n");
	printf("notice->Template for time is: STRING->[XX:XX]\n");
	fgets(time, 10, stdin);
	time[strlen(time) - 1] = 0;

	setCalendarNurse(id, date, time);

	fseek(p6, 0, SEEK_END);
	fprintf(p6, "%s,%s,%s,%s,%s\n", id, city, typeAP, date, time);
	printf(">The appoinetment to nurse is set!<\n\n");

	fclose(p6);
	free(typeAP);
}
void RebootAppoinetmentsNurse()
{
	FILE* p3;
	const char* date0, * date1, * date2, * date3, * date4;
	int counter = 1, max = 0;
	char* dates[5] = { "05/12/21" ,"06/12/21" ,"07/12/21" ,"08/12/21" ,"09/12/21" };

	p3 = fopen("NurseAppointment.csv", "w");
	if (p3 == NULL)
	{
		printf("\nNurseAppointment.csv failed.\n");
		exit(1);
	}

	globaldata = (appoinetment*)malloc(5 * sizeof(appoinetment));

	char** temp = Loadtime();
	SortimeArray(temp);

	for (int i = 0; i < ROWS; i++)
	{
		if (max == 1)
			fprintf(p3, "\n", globaldata[i].time[counter]);

		counter = 0;
		strcpy(globaldata[i].date, dates[i]);
		fprintf(p3, "%s,", globaldata[i].date);

		while (counter < 17)
		{
			if (counter == 16)
			{
				fprintf(p3, "%s", globaldata[i].time[counter]);
				max = 1;
			}
			else
				fprintf(p3, "%s,", globaldata[i].time[counter]);
			counter++;
		}
	}
	fclose(p3);
}
void printfAvailableAppoinetmentsNurse()
{
	appoinetment data;
	FILE* p3;

	char buffer[255] = { 0 };

	p3 = fopen("NurseAppointment.csv", "r");
	if (p3 == NULL)
	{
		printf("\n Failed to open file!");
	}
	else
	{
		printf("\n");
		while ((fgets(buffer, 255, p3)) != NULL /*&& fgetc(p3) != EOF */)
		{
			puts(buffer);
			/* Some processing */
		}
	}
	fclose(p3);
}
void setCalendarNurse(char id[], char date[], char time[])
{
	appoinetment data;
	FILE* p4;

	p4 = fopen("CalendarNurse.csv", "r+");

	fseek(p4, 0, SEEK_END);
	fprintf(p4, "%s,%s,%s\n", id, date, time);

	fclose(p4);
}
void ViewNurse(char* id)
{
	appoinetment data;
	FILE* p2;
	int flag = 0, counter = 0, line = 0;

	printf("\n");

	p2 = fopen("CalendarNurse.csv", "r");

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
		/*	if (counter == 3)
			{
				counter = 0;
				line++;
			}*/
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
			counter++;
		}
	}
	fclose(p2);


	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;
		int newCounter = 0;

		char buffer[255] = { 0 };

		p3 = fopen("CalendarNurse.csv", "r");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		printf("Nurse Appoinetments are:\n");
		while (fgets(buffer, sizeof(buffer), p3))
		{
			if (foundit == 2)
				break;

			char* temp;
			temp = strtok(buffer, ",");

			while (temp != NULL)
			{
				if (foundit == 2)
					break;

				if (newCounter == (counter + 1))
				{
					puts(temp);
					foundit++;
				}
				if (newCounter == (counter + 2))
				{
					puts(temp);
					foundit++;
				}
				newCounter++;
				temp = strtok(NULL, ",");
			}
		}
		fclose(p3);
	}
}
void CancelNurse(char id[])
{
	appoinetment data;
	FILE* p2;
	int flag = 0, counter = 0, line = 0;

	printf("\n");

	p2 = fopen("CalendarNurse.csv", "r");

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
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
			counter++;
		}
	}
	fclose(p2);


	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;
		int newCounter = 0;
		char* remove;
		remove = " ";

		char buffer[255] = { 0 };

		p3 = fopen("CalendarNurse.csv", "w");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		fseek(p3, 13, SEEK_SET);
		while (fgets(buffer, sizeof(buffer), p3))
		{
			if (foundit == 3)
				break;

			char* temp;
			temp = strtok(buffer, ",");

			while (temp != NULL)
			{
				if (foundit == 2)
					break;

				if (newCounter == (counter))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				if (newCounter == (counter + 1))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				if (newCounter == (counter + 2))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				newCounter++;
				temp = strtok(NULL, ",");
			}
		}
		fclose(p3);
	}

}

//Lab
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

	printfAvailableAppoinetmentsLab();
	printf("Please enter date from the list:\n");
	printf("notice->Template for date is: STRING->[XX/XX/XXXX]\n");
	fgets(date, 20, stdin);
	date[strlen(date) - 1] = 0;

	printf("Please enter time from the list:\n");
	printf("notice->Template for time is: STRING->[XX:XX]\n");
	fgets(time, 10, stdin);
	time[strlen(time) - 1] = 0;

	setCalendarLab(id, date, time);


	fseek(p6, 0, SEEK_END);
	fprintf(p6, "%s,%s,%s,%s,%s\n", id, city, typeAP, date, time);
	printf(">The appoinetment to nurse is set!<\n\n");

	fclose(p6);
	free(typeAP);
}
void RebootAppoinetmentsLab()
{
	FILE* p3;
	const char* date0, * date1, * date2, * date3, * date4;
	int counter = 1, max = 0;
	char* dates[5] = { "05/12/21" ,"06/12/21" ,"07/12/21" ,"08/12/21" ,"09/12/21" };

	p3 = fopen("LabAppointment.csv", "w");
	if (p3 == NULL)
	{
		printf("\nLabAppointment.csv failed.\n");
		exit(1);
	}

	globaldata = (appoinetment*)malloc(5 * sizeof(appoinetment));

	char** temp = Loadtime();
	SortimeArray(temp);

	for (int i = 0; i < ROWS; i++)
	{
		if (max == 1)
			fprintf(p3, "\n", globaldata[i].time[counter]);

		counter = 0;
		strcpy(globaldata[i].date, dates[i]);
		fprintf(p3, "%s,", globaldata[i].date);

		while (counter < 17)
		{
			if (counter == 16)
			{
				fprintf(p3, "%s", globaldata[i].time[counter]);
				max = 1;
			}
			else
				fprintf(p3, "%s,", globaldata[i].time[counter]);
			counter++;
		}
	}
	fclose(p3);
}
void printfAvailableAppoinetmentsLab()
{
	appoinetment data;
	FILE* p3;

	char buffer[255] = { 0 };

	p3 = fopen("LabAppointment.csv", "r");
	if (p3 == NULL)
	{
		printf("\n Failed to open file!");
	}
	else
	{
		printf("\n");
		while ((fgets(buffer, 255, p3)) != NULL /*&& fgetc(p3) != EOF */)
		{
			puts(buffer);
			/* Some processing */
		}
	}
	fclose(p3);
}
void setCalendarLab(char id[], char date[], char time[])
{
	appoinetment data;
	FILE* p4;

	p4 = fopen("CalendarLab.csv", "r+");

	fseek(p4, 0, SEEK_END);
	fprintf(p4, "%s,%s,%s\n", id, date, time);

	fclose(p4);
}
void ViewLab(char* id)
{
	appoinetment data;
	FILE* p2;
	int flag = 0, counter = 0, line = 0;

	printf("\n");

	p2 = fopen("CalendarLab.csv", "r");

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
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
			counter++;
		}
	}
	fclose(p2);


	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;
		int newCounter = 0;

		char buffer[255] = { 0 };

		p3 = fopen("CalendarLab.csv", "r");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		printf("Lab Appoinetments are:\n");
		while (fgets(buffer, sizeof(buffer), p3))
		{
			if (foundit == 2)
				break;

			char* temp;
			temp = strtok(buffer, ",");

			while (temp != NULL)
			{
				if (foundit == 2)
					break;

				if (newCounter == (counter + 1))
				{
					puts(temp);
					foundit++;
				}
				if (newCounter == (counter + 2))
				{
					puts(temp);
					foundit++;
				}
				newCounter++;
				temp = strtok(NULL, ",");
			}
		}
		fclose(p3);
	}
}
void CancelLab(char* id)
{
	appoinetment data;
	FILE* p2;
	int flag = 0, counter = 0, line = 0;

	printf("\n");

	p2 = fopen("CalendarLab.csv", "r");

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
			if (strcmp(temp, id) == 0)
			{
				flag = 1;
				break;
			}
			temp = strtok(NULL, ",");
			counter++;
		}
	}
	fclose(p2);


	if (flag == 1)
	{
		appoinetment data;
		FILE* p3;
		int foundit = 0;
		int newline = 0;
		int newCounter = 0;
		char* remove;
		remove = " ";

		char buffer[255] = { 0 };

		p3 = fopen("CalendarLab.csv", "w");
		if (p3 == NULL)
		{
			printf("Error opening file\n");
			exit(1);
		}

		fseek(p3, 13, SEEK_SET);
		while (fgets(buffer, sizeof(buffer), p3))
		{
			if (foundit == 3)
				break;

			char* temp;
			temp = strtok(buffer, ",");

			while (temp != NULL)
			{
				if (foundit == 2)
					break;

				if (newCounter == (counter))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				if (newCounter == (counter + 1))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				if (newCounter == (counter + 2))
				{
					fprintf(p3, "%s,", remove);
					foundit++;
				}
				newCounter++;
				temp = strtok(NULL, ",");
			}
		}
		fclose(p3);
	}
}