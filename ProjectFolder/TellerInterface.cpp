#include "TellerInterface.h"

using namespace std;
using namespace Utils;

void TellerInterface::showTellerMenu()
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
		case 1: addCustomer(); break;
		case 2: serveCustomer(); break;
		case 3: clearScreen(); displayQueue(); break;
		case 4: showStatistics(); break;
		case 5: clearScreen(); return;
		}
	}
}

void TellerInterface::addCustomer()
{
	clearScreen();

	string name = "", transaction = "";
	int age = 0, minAge = 18, maxAge = 99;
	int choiceTransaction = 0, choiceMin = 1, choiceMax = 5;
	double balance = 0, minBal = 500.0, maxBal = 10000000.0;
	bool isConfirmed = false;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║              Customer Details               ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";

	name = inputString("Enter Full Name: ");
	age = inputInteger("Enter Age: ", minAge, maxAge);
	balance = inputDouble("Enter Initial Deposit: ", minBal, maxBal);

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

	choiceTransaction = inputInteger("Enter Transaction Type: ", choiceMin, choiceMax);

	switch (choiceTransaction)
	{
	case 1: transaction = "Account"; break;
	case 2: transaction = "Deposit"; break;
	case 3: transaction = "Withdraw"; break;
	case 4: transaction = "Transfer"; break;
	case 5: transaction = "Payment"; break;
	}

	Customer c = queueManager.createCustomer(name, age, transaction, balance);
	queueManager.addCustomer(c);
	stats.recordService(c.estimatedServiceTime);

	clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "  🛈 Customer ID " << c.id << " has been added to the queue" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
}

void TellerInterface::serveCustomer()
{
	Customer customer;

	if (queueManager.hasCustomers())
	{
		clearScreen();
		cout << "Queue is empty. Insert a customer first." << endl;
		return;
	}

	customer = queueManager.serveCustomer();
	stats.setTotalServed();

	clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "   🛈       Now serving Customer ID " << customer.id << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
}

void TellerInterface::displayQueue()
{
	if (!queueManager.hasCustomers()) {
		return;
	}

	cout << "╔══════════════════════════ CURRENT QUEUE ══════════════════════════════╗" << endl;
	cout << "╠══════╦══════════════════════════════╦═══════╦═══════════════╦═════════╣" << endl;
	cout << "║  ID  ║             Name             ║  Age  ║  Transaction  ║   ETA   ║" << endl;
	cout << "╠══════╬══════════════════════════════╬═══════╬═══════════════╬═════════╣" << endl;
	queueManager.displayQueue();
	cout << "╚══════╩══════════════════════════════╩═══════╩═══════════════╩═════════╝\n";

	char choice = getYesNoChoice("Serve Customer [ Y - Yes | N - Exit ]: ");

	switch (choice) {
	case 'y':
		serveCustomer();
		if (!queueManager.hasCustomers())
		{
			displayQueue();
			break;
		}
		cout << "You just emptied the queue!" << endl;
		break;
	case 'n': clearScreen(); return;
	}
}

void TellerInterface::showStatistics()
{
	char choice;
	int length = queueManager.getCurrentQueueLength();

	while (true)
	{
		stats.displayStatistics(queueManager.getPeakQueueLength(length));
		choice = getYesNoChoice("Do you want to exit [ Y - Yes | N - No ]: ");

		if (choice == 'y') {
			clearScreen();
			return;
		}
	}
}
