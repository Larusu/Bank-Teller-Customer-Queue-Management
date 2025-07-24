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

void AppController::showCustomerMainMenu()
{
	int choice = 0, choiceMin = 1, choiceMax = 6;

	clearScreen();

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
	int choice = 0, choiceMin = 1, choiceMax = 5;

	clearScreen();

	while (true)
	{
		cout << "┌─────────────────────────────────────────────┐" << "\n";
		cout << "│                BANK TELLER                  │" << "\n";
		cout << "├─────┬───────────────────────────────────────┤" << "\n";
		cout << "│  1  │ Add New Customer                      │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  2  │ Serve Next Customer                   │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  3  │ Display Current Queue                 │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  4  │ Show Statistics                       │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  5  │ Exit to Main Menu                     │" << "\n";
		cout << "└─────┴───────────────────────────────────────┘" << "\n";

		choice = inputInteger("Choice: ", choiceMin, choiceMax);
		switch (choice)
		{
		case 1: handleAddCustomer(); break;
		case 2: handleServeCustomer(); break;
		case 3: clearScreen(); handleDisplayQueue(); break;
		case 4: handleShowStatistics(); break;
		case 5: clearScreen(); return;
		}
	}
}

void AppController::handleAddCustomer()
{	
	clearScreen();

	string name = "", transaction = "";
	int age = 0, minAge = 18, maxAge = 99, choiceMin = 1, choiceMax = 5, choiceTransaction;
	bool isConfirmed = false;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "║              Customer Details               ║" << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";

	name = inputString("Enter Full Name: ");
	age = inputInteger("Enter Age: ", minAge, maxAge);

	cout << "┌─────┬─────── Transaction Types ─────────────┐" << "\n";
	cout << "│  1  │ Account                               │" << "\n";
	cout << "├─────┼───────────────────────────────────────┤" << "\n";
	cout << "│  2  │ Deposit                               │" << "\n";
	cout << "├─────┼───────────────────────────────────────┤" << "\n";
	cout << "│  3  │ Withdraw                              │" << "\n";
	cout << "├─────┼───────────────────────────────────────┤" << "\n";
	cout << "│  4  │ Transfer                              │" << "\n";
	cout << "├─────┼───────────────────────────────────────┤" << "\n";
	cout << "│  5  │ Payment                               │" << "\n";
	cout << "└─────┴───────────────────────────────────────┘" << "\n";

	choiceTransaction = inputInteger("Enter Transaction Type: ", choiceMin, choiceMax );

	switch(choiceTransaction)
	{
		case 1: transaction = "Account"; break;
		case 2: transaction = "Deposit"; break;
		case 3: transaction = "Withdraw"; break;
		case 4: transaction = "Transfer"; break;
		case 5: transaction = "Payment"; break;
	}

	Customer c = queueManager.createCustomer(name, age, transaction);
	queueManager.addCustomer(c);
	stats.recordService(c.estimatedServiceTime);

	clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "  🛈 Customer ID " << c.id << " has been added to the queue" << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";
}

void AppController::handleServeCustomer()
{
	Customer customer;

	if (queueManager.hasCustomers())
	{
		clearScreen();
		cout << "Queue is empty. Insert a customer first." << endl; 
		return;
	}

	customer = queueManager.serveCustomer();

	clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "   🛈       Now serving Customer ID " << customer.id << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";
}

void AppController::handleDisplayQueue()
{	
	queueManager.displayQueue();

	if(queueManager.hasCustomers()){
		return;
	}
	char choice = getYesNoChoice("Serve Customer [ Y - Yes | N - Exit ]: ");

	switch (choice) {
		case 'y': 
			handleServeCustomer();
			if(!queueManager.hasCustomers())
			{	
				handleDisplayQueue();
				break; 
			}
			cout << "You just emptied the queue!" << endl;
			break;
		case 'n': clearScreen(); return;
	}	
}

void AppController::handleShowStatistics()
{
	stats.displayStatistics(queueManager.getPeakQueueLength(queueManager.getCurrentQueueLength()));
}