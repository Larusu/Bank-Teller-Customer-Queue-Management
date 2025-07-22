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
	string transaction = "", transactionTypes[] = { "Deposit", "Withdrawal", "Transfer", "Payment" };

	name = inputString("Enter Full Name: ");
	age = inputInteger("Enter Age: ", minAge, maxAge);
	transaction = inputString("Enter Transaction Type: ", transactionTypes);

	Customer c = queueManager.createCustomer(name, age, transaction);
	queueManager.addCustomer(c);
}

void AppController::handleServeCustomer()
{

}

void AppController::handleDisplayQueue()
{

}

void AppController::handleShowStatistics()
{

}