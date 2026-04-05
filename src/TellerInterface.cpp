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
		cout << "│  1  │ Register New Customer                 │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  2  │ Serve Next Customer                   │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  3  │ Display Current Queue                 │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  4  │ Show Statistics                       │" << "\n";
		cout << "├─────┼───────────────────────────────────────┤" << "\n";
		cout << "│  5  │ Exit                                  │" << "\n";
		cout << "└─────┴───────────────────────────────────────┘" << "\n";

		choice = inputInteger("Choice: ", choiceMin, choiceMax);
		switch (choice)
		{
		case 1: registerCustomer(); break;
		case 2: serveCustomer(); break;
		case 3: clearScreen(); displayQueue(); break;
		case 4: showStatistics(); break;
		case 5: clearScreen(); return;
		}
	}
}

void TellerInterface::registerCustomer()
{
	clearScreen();

	string lastName = "", firstName = "", fullName = "", transaction = "", bankId;
	int age = 0, minAge = 18, maxAge = 99;
	int choiceTransaction = 0, choiceMin = 1, choiceMax = 5;
	double balance = 0, minBal = 500.0, maxBal = 10000000.0;
	bool isConfirmed = false;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║              Customer Details               ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";

	lastName = inputString("Enter Last Name: ");
	firstName = inputString("Enter First Name: ");

	fullName = firstName + " " + lastName;
	age = inputInteger("Enter Age: ", minAge, maxAge);
	balance = inputDouble("Enter Initial Deposit: ", minBal, maxBal);
	bankId = generateBankId();

	char choice = getYesNoChoice("Confirm adding customer? [Y - Yes | N - No]: ");

	if (choice == 'n') {
		clearScreen(); 
		return;
	}

	string nameToTxt = "customer_bank_id/ID_";

    for(char c : fullName)
    {
        nameToTxt += (isspace(c)) ? '_' : c;
    }
    nameToTxt += ".txt";

    // Write bank ID to receipt file
    ofstream getBankId(nameToTxt);
    getBankId << "Bank ID: " << bankId;
    getBankId.close();

    // Save customer info to RegisteredCustomers file 
    ofstream registered;
    registered.open("RegisteredCustomers.txt", ios::app);
    registered << bankId << "|"
               << fullName << "|"
               << age << "|"
               << balance << '\n';
    registered.close();
	
	clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "  🛈    Customer has been registered" << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";
}

void TellerInterface::serveCustomer()
{
	Customer customer;

	if (!queueManager.hasCustomers())
	{
		clearScreen();
		cout << "Queue is empty. Insert a customer first." << endl;
		return;
	}

	customer = queueManager.serveCustomer();
	customerUI.setWaitingForCompletion(customer);
	clearScreen();

	// Notify the customer that their id has been served
    g_announcements[customer.bank.bankId] = customer.id;
	
	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "   🛈       Now serving Customer ID " << customer.id << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
}

void TellerInterface::displayQueue()
{
	if (!queueManager.hasCustomers()) {
		cout << "\n╔═════════════════════════════════════════════╗" << "\n";
		cout <<   "               Queue is Empty" << "\n";
		cout <<   "╚═════════════════════════════════════════════╝" << "\n";
		return;
	}

	cout << "╔══════════════════════════ CURRENT QUEUE ══════════════════════════════╗" << endl;
	cout << "╠══════╦══════════════════════════════╦═══════╦═══════════════╦═════════╣" << endl;
	cout << "║  ID  ║             Name             ║  Age  ║  Transaction  ║   ETA   ║" << endl;
	cout << "╠══════╬══════════════════════════════╬═══════╬═══════════════╬═════════╣" << endl;
	queueManager.displayQueue();
	cout << "╚══════╩══════════════════════════════╩═══════╩═══════════════╩═════════╝\n";

	char choice = getYesNoChoice("Serve Customer [Y - Yes | N - No]: ");

	switch (choice) {
	case 'y':
		serveCustomer();
		if (queueManager.hasCustomers())
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
	int length;

	while (true)
	{
		length = queueManager.getCurrentQueueLength();
		stats.displayStatistics(queueManager.getPeakQueueLength(length));
		choice = getYesNoChoice("Do you want to exit [Y - Yes | N - No]: ");

		if (choice == 'y') {
			clearScreen();
			return;
		}
	}
}
