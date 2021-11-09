#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct doctor
{
	char *user_name, *expertise, *password;
	int birth_year;
};

struct doctor *initializeDoc(int *dsize);
void main_menu();
void login();
void create_user();


int main()
{
	main_menu();
	return 0;
}

void main_menu()
{
	int menu_select;

	printf("Hello welcome to MedicTouch clinic appointment management system\n");
	printf("Please select the operation:\n");
	printf(" [1] Create user\n [2] Login to the system\n [3] Password recovery\n [4] Exit\n");
	scanf_s("%d", &menu_select);

	switch (menu_select)
	{
		case 1:
		{
		login();
		break;
		}
	}

}

void login()
{
	printf("Good work!\n");
}

struct doctor* initializeDoc(int *dsize)
{
	char temp[20], temp2[20], temp3[20];
	struct doctor* data = NULL; // add to doctors archive.

	printf("Please enter the username:\n");
	scanf("%s", temp);

	printf("Please enter the password:\n");
	scanf("%s", temp2);

	printf("Please enter the expertise:\n");
	scanf("%s", temp3);

	dsize = 1;


	data = (struct doctor*)realloc(*dsize, sizeof(struct doctor));

	if (data == NULL)
	{
		return NULL;
	}

	if (dsize > 0)
	{
		for (int i = 0; i < *dsize; i++)
		{
			data[i].user_name = (char*)malloc((strlen(temp)+1) * sizeof(char));

			if (data[i].user_name == NULL)
			{
				printf("Doc user name error\n");
				return NULL;
			}
			strcpy(data[i].user_name, temp);

			data[i].password = (char*)malloc((strlen(temp2) + 1) * sizeof(char));

			if (data[i].password == NULL)
			{
				printf("Doc user name error\n");
				return NULL;
			}
			strcpy(data[i].user_name, temp2);

			data[i].expertise = (char*)malloc((strlen(temp3) + 1) * sizeof(char));

			if (data[i].expertise == NULL)
			{
				printf("Doc user name error\n");
				return NULL;
			}
			strcpy(data[i].user_name, temp3);
		}



	}
	else
	{
		data[*dsize].user_name = (char*)malloc((strlen(temp) + 1) * sizeof(char));
		if (data[*dsize].user_name == NULL)
		{
			printf("Doc user name error\n");
			return NULL;
		}
		strcpy(data[*dsize].user_name, temp);
	}



}

void create_user()
{
	struct doctor *data = NULL;
	int choose, doctorSize, patientSize;

	printf("Welcome to user registration\n Please select the type of user you want to create\n [1] Doctor\n [2] Patient\n");
	scanf_s("%d", &choose);

	if (choose == 1)
	{
		data = initializeDoc(&doctorSize);

		if (data == NULL)
		{
			return 0;
		}
	}
	
}
