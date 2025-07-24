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
		case 1: showCustomerMainMenu();	break;
		case 2: showTellerMainMenu();	break;
		case 3: return;
		default: cout << "Invalid choice!"; break;
		}
	}
}
void AppController::showMasterMainMenu()
{
	cout << "╔═════════════════════════════════════════════╗" << "\n";
    cout << "║                 MAIN MENU                   ║" << "\n";
    cout << "╠═════╦═══════════════════════════════════════╣" << "\n";
    cout << "║  1  ║ Enter Bank as Customer                ║" << "\n";
    cout << "╠═════╬═══════════════════════════════════════╣" << "\n";
	cout << "║  2  ║ Enter Bank as Teller                  ║" << "\n";
    cout << "╠═════╬═══════════════════════════════════════╣" << "\n";
    cout << "║  3  ║ Exit Bank                             ║" << "\n";
    cout << "╚═════╩═══════════════════════════════════════╝" << "\n";
}

void AppController::showCustomerMainMenu()
{
	int choice = 0, choiceMin = 1, choiceMax = 6;

	while (true)
	{
		cout << "┌─────────────────────────────────────────────┐" << "\n";
		cout << "│                  CUSTOMER                   │" << "\n";
		cout << "├─────┬───────────────────────────────────────┤" << "\n";
		cout << "│  1  │ Account                               │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  2  │ Deposit                               │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  3  │ Withdraw                              │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  4  │ Transfer                              │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  5  │ Payment                               │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  6  │ Exit to Main Menu                     │" << "\n";
		cout << "└─────┴───────────────────────────────────────┘" << "\n";

		choice = inputInteger("Choice: ", choiceMin, choiceMax);
		switch (choice)
		{
		case 1: cout << "asda"; break;
		case 2: cout << "asda"; break;
		case 3: cout << "asda"; break;
		case 4: cout << "asda"; break;
		case 5: cout << "asda"; break;
		case 6: cout << "asda"; break;
		}
	}
}

void AppController::showTellerMainMenu()
{
	int choice = 0, choiceMin = 1, choiceMax = 4;

	while (true)
	{
		cout << "╔═════════════════════════════════════════════╗" << "\n";
		cout << "║                BANK TELLER                  ║" << "\n";
		cout << "╠═════╦═══════════════════════════════════════╣" << "\n";
		cout << "║  1  ║ Serve Next Customer                   ║" << "\n";
		cout << "╠═════╬═══════════════════════════════════════╣" << "\n";
		cout << "║  2  ║ Display Current Queue                 ║" << "\n";
		cout << "╠═════╬═══════════════════════════════════════╣" << "\n";
		cout << "║  3  ║ Show Statistics                       ║" << "\n";
		cout << "╠═════╬═══════════════════════════════════════╣" << "\n";
		cout << "║  4  ║ Exit to Main Menu                     ║" << "\n";
		cout << "╚═════╩═══════════════════════════════════════╝" << "\n";

		choice = inputInteger("Choice: ", choiceMin, choiceMax);
		switch (choice)
		{
		case 1: handleServeCustomer(); break;
		case 2: handleDisplayQueue(); break;
		case 3: handleShowStatistics(); break;
		case 4: handleAddCustomer(); break;
		}
	}
}

void AppController::handleAddCustomer()
{
	string name = "";
	int age = 0, minAge = 18, maxAge = 99;
	string transaction = "";
	string transactionTypes[] = { "Deposit", "Withdrawal", "Transfer", "Payment" };
	bool isConfirmed = false;

	name = inputString("Enter Full Name: ");
	age = inputInteger("Enter Age: ", minAge, maxAge);
	transaction = inputString("Enter Transaction Type: ", transactionTypes, 4);
	
	//After confirmation

	Customer c = queueManager.createCustomer(name, age, transaction);
	queueManager.addCustomer(c);


	int currentQueueLength = queueManager.getCurrentQueueLength();
	queueManager.getPeakQueueLength(currentQueueLength);
	

	clearScreen();
}

void AppController::handleServeCustomer()
{
	Customer customer;

	if (queueManager.hasCustomers())
	{
		cout << "Queue is empty. Insert a customer first." << endl; 
		return;
	}

	customer = queueManager.serveCustomer();

	clearScreen();

	cout << "Now serving: " << customer.name << " (ID: " << customer.id << ")" << endl;
}

void AppController::handleDisplayQueue()
{
	queueManager.displayQueue();

	char choice = 'n';
	
	cout << "Close window [Y = yes]?: ";
	while (tolower(choice) != 'y')
	{
		cin >> choice;
		choice = tolower(choice);
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please try again: ";
			continue;
		}
		cin.ignore(1000, '\n');

		switch (choice)
		{
		case 'y': clearScreen(); return;
		default: cout << "Invalid input. Please try again: "; continue;
		}
	}
}

void AppController::handleShowStatistics()
{

}