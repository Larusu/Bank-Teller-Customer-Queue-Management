#include "AppController.h"

using namespace std;
using namespace Utils;

void AppController::run()
{
	Customer customer;
	int choice = 0, choiceMin = 1, choiceMax = 5;

	while (true)
	{
		showMainMenu();
		choice = inputInteger("Enter Choice: ", choiceMin, choiceMax);
		cout << endl;
		switch (choice)
		{
		case 1: handleAddCustomer();	break;
		case 2: handleServeCustomer();	break;
		case 3: handleDisplayQueue();	break;
		case 4: handleShowStatistics(); break;
		case 5: return;
		default: cout << "Invalid choice!"; break;
		}
	}
}

void AppController::showMainMenu()
{
	cout << "======= BANK TELLER =======" << endl;
	cout << "1. Add Customer to Queue " << endl;
	cout << "2. Serve Next Customer" << endl;
	cout << "3. Display Current Queue" << endl;
	cout << "4. Show Statistics" << endl;
	cout << "5. Exit" << endl;
}

void AppController::handleAddCustomer()
{
	string name = "";
	int age = 0, minAge = 18, maxAge = 99;
	string transaction = "";
	string transactionTypes[] = { "Deposit", "Withdrawal", "Transfer", "Payment" };

	name = inputString("Enter Full Name: ");
	age = inputInteger("Enter Age: ", minAge, maxAge);
	transaction = inputString("Enter Transaction Type: ", transactionTypes, 4);

	Customer c = queueManager.createCustomer(name, age, transaction);
	queueManager.addCustomer(c);

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
	cout << "Now serving: " << customer.name << " (ID: " << customer.id << ")" << endl;
}

void AppController::handleDisplayQueue()
{
	queueManager.displayQueue();

	char choice = 'n';
	
	cout << "Close window (Y = yes)?: ";
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