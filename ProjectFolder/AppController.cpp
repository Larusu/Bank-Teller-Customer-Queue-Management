#include "AppController.h"

using namespace std;
using namespace Utils;

void AppController::run()
{
	Customer customer;
	int choice = 0, choiceMin = 1, choiceMax = 3;

	while (true)
	{
		showMasterMainMenu();
		choice = inputInteger("Enter Choice: ", choiceMin, choiceMax);
		cout << endl;
		switch (choice)
		{
			case 1: customerUI.showCustomerMenu();	break;
			case 2: tellerUI.showTellerMenu();	break;
			case 3: return;
			default: cout << "Invalid choice!"; break;
		}
	}
}

void AppController::showMasterMainMenu()
{
		cout << "┌─────────────────────────────────────────────┐" << "\n";
		cout << "│                  CUSTOMER                   │" << "\n";
		cout << "├─────┬───────────────────────────────────────┤" << "\n";
		cout << "│  1  │ Enter Bank as Customer                │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  2  │ Enter Bank as Teller                  │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  3  │ Exit Bank                             │" << "\n";
		cout << "└─────┴───────────────────────────────────────┘" << "\n";
}