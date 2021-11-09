#include <stdio.h>

void main_menu();
void login();

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
