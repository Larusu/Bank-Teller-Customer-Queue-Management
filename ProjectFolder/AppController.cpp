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
	clearScreen();

	double balance = 0.0, minBal = 500.0, maxBal = 10000000.0;
	string firstName = "", lastName = "", fullName = "", transaction = "";
	int age = 0, minAge = 18, maxAge = 99;
	int choiceTransaction = 0, choiceMin = 1, choiceMax = 5;
	
	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "║             Enter Your Details              ║" << "\n";
	cout <<   "╠═════════════════════════════════════════════╣" << "\n";
	cout <<   "║    If your name is already in the queue,    ║" << "\n";
	cout <<   "║      you will automatically proceed to      ║" << "\n";
	cout <<   "║          the transaction process.           ║" << "\n";
	cout <<   "║      Please enter your name correctly.      ║" << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";
	lastName = inputString("Enter you Last Name: ");
	firstName = inputString("Enter you First Name: ");
	fullName = firstName + " " + lastName;

	// If the customer was served using their name, check their transaction type
	int index = findServedCustomerIndex(fullName);
	if (index > -1)
	{
		Customer getCustomer = queueManager.getServedCustomers()[index];

		if (getCustomer.transactionType == "Account") customerAccount(getCustomer);
		else if (getCustomer.transactionType == "Deposit") customerDeposit(getCustomer);
		else if (getCustomer.transactionType == "Withdraw") customerWithdraw(getCustomer);
		else if (getCustomer.transactionType == "Transfer") customerTransfer(getCustomer);
		else if (getCustomer.transactionType == "Payment") customerPayment(getCustomer);

		return;
	}

	if (queueManager.isExistingName(fullName))
	{
		cout << "You already have a pending transaction. Please wait for your turn." << endl;
		return;
	}

	age = inputInteger("Enter you age: ", minAge, maxAge);
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

	Customer c = queueManager.createCustomer(fullName, age, transaction, balance);
	queueManager.addCustomer(c);
	stats.recordService(c.estimatedServiceTime);

	clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "  🛈 Added to the queue! Wait for turn." << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";

	/*cout << "┌─────────────────────────────────────────────┐" << "\n";
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
	cout << "└─────┴───────────────────────────────────────┘" << "\n";*/
}

void AppController::customerAccount(Customer& servedCustomer)
{
	string firstName = getFirstName(servedCustomer.name);
	char choice;

	while (true)
	{
		cout << "\n╔═════════════════════════════════════════════╗" << "\n";
		cout << "║        " << firstName << "'s Details             ║" << "\n";
		cout << "╠═════════════════════════════════════════════╣" << "\n";
		cout << "║ Full Name: " << servedCustomer.name << "║" << '\n';
		cout << "║ Age:        " << servedCustomer.age << "        ║" << '\n';
		cout << "║ Balance:    " << servedCustomer.bank.balance << "         ║" << '\n';
		cout << "║ Bank ID:    " << servedCustomer.bank.bankId << "          ║" << '\n';
		cout << "╚═════════════════════════════════════════════╝" << "\n";

		choice = getYesNoChoice("Do you want to exit [ Y - Yes ]: ");

		if (choice == 'y') {
			clearScreen();
			return;
		}
		if (choice == 'n')
		{
			clearScreen();
			continue;
		}
	}
}

void AppController::customerDeposit(Customer& servedCustomer)
{
	string firstName = getFirstName(servedCustomer.name);
	string bankId = servedCustomer.bank.bankId;
	double depositAmount, minDeposit = 500.0, maxDeposit = 10000000.0;
	char choice;

	while (true)
	{
		cout << "\n╔═════════════════════════════════════════════╗" << "\n";
		cout << "║        " << firstName << "'s Depositing             ║" << "\n";
		cout << "╚═════════════════════════════════════════════╝" << "\n";
		depositAmount = inputDouble("Deposit Amount: ", minDeposit, maxDeposit);

		queueManager.depositMoney(depositAmount, bankId);

		choice = getYesNoChoice("Do you want to exit [ Y - Yes ]: ");

		if (choice == 'y') {
			clearScreen();
			return;
		}
		if (choice == 'n')
		{
			clearScreen();
			continue;
		}
	}
}

void AppController::customerWithdraw(Customer& servedCustomer)
{
	string firstName = getFirstName(servedCustomer.name);
	string bankId = servedCustomer.bank.bankId;
	double withdrawAmount, minWithdraw = 0, maxWithdraw = servedCustomer.bank.balance;
	char choice;

	while (true)
	{
		cout << "\n╔═════════════════════════════════════════════╗" << "\n";
		cout << "║     " << firstName << "'s Withdrawing Money       ║" << "\n";
		cout << "╚═════════════════════════════════════════════╝" << "\n";
		cout << " Available balance: " << maxWithdraw << endl;
		withdrawAmount = inputDouble("Withdraw Amount: ", minWithdraw, maxWithdraw);

		queueManager.deductFromBalance(withdrawAmount, bankId);

		choice = getYesNoChoice("Do you want to exit [ Y - Yes ]: ");

		if (choice == 'y') {
			clearScreen();
			return;
		}
		if (choice == 'n')
		{
			clearScreen();
			continue;
		}
	}
	
}

void AppController::customerTransfer(Customer& servedCustomer)
{
	string firstName = getFirstName(servedCustomer.name);
	string bankId = servedCustomer.bank.bankId;
	string recipientId;
	double transferAmount, minTransfer = 0, maxTransfer = servedCustomer.bank.balance;
	char choice;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║     " << firstName << "'s Transferring Money       ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
	cout << " Available balance: " << maxTransfer << endl;

	// Checking for recipient's id if exist
	while (true)
	{
		cout << "Enter recipient's Bank ID: ";
		cin >> recipientId;

		recipientId = trim(recipientId);
		if (recipientId.length() != 7)
		{
			cout << "ID must be 000-000. Please try again.\n";
			continue;
		}

		bool isValid = false;

		// Check in served customers
		vector<Customer> served = queueManager.getServedCustomers();
		for (const Customer& c : served)
		{
			if (c.bank.bankId == recipientId && recipientId != bankId)
			{
				isValid = true;
				break;
			}
		}

		// Check in pending customers
		queue<Customer> pending = queueManager.getPendingCustomers();
		while (!pending.empty())
		{
			Customer temp = pending.front();
			pending.pop();

			if (temp.bank.bankId == recipientId && recipientId != bankId)
			{
				isValid = true;
				break;
			}
		}

		if (isValid)
		{
			break;
		}

		cout << "Bank ID doesn't exist. Please try again.\n";
	}

	transferAmount = inputDouble("Withdraw Amount: ", minTransfer, maxTransfer);

	queueManager.transferMoney(transferAmount, bankId, recipientId);

	choice = getYesNoChoice("Do you want to exit [ Y - Yes ]: ");

	if (choice == 'y') {
		clearScreen();
		return;
	}
}

void AppController::customerPayment(Customer& servedCustomer)
{
	string firstName = getFirstName(servedCustomer.name);
	string bankId = servedCustomer.bank.bankId;
	string paymentPurpose = "";
	double paymentAmount, minPayment = 0, maxPayment = servedCustomer.bank.balance;
	char choice;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║     " << firstName << "'s Paying       ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
	cout << " Available balance: " << maxPayment << endl;
	paymentPurpose = inputString("Enter purpose of payment: ");
	paymentAmount = inputDouble("Payment Amount: ", minPayment, maxPayment);

	queueManager.deductFromBalance(paymentAmount, bankId);

	choice = getYesNoChoice("Do you want to exit [ Y - Yes ]: ");

	if (choice == 'y') {
		clearScreen();
		return;
	}
	if (choice == 'n')
	{
		clearScreen();

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
	int age = 0, minAge = 18, maxAge = 99;
	int choiceTransaction = 0, choiceMin = 1, choiceMax = 5;
	double balance = 0, minBal = 500.0, maxBal = 10000000.0;
	bool isConfirmed = false;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "║              Customer Details               ║" << "\n";
	cout <<   "╚═════════════════════════════════════════════╝" << "\n";

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

	choiceTransaction = inputInteger("Enter Transaction Type: ", choiceMin, choiceMax );

	switch(choiceTransaction)
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
	stats.setTotalServed();

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

int AppController::findServedCustomerIndex(const std::string& name)
{
	/*vector<Customer> alreadyServe = queueManager.getServedCustomers();

	for (Customer& c : alreadyServe)
	{
		if (trim(toUpper(name)) == trim(toUpper(c.name)))
		{
			return -1;
		}
	}*/

	vector<Customer> tempServeCustomer = queueManager.getServedCustomers();

	for (int i = 0; i < tempServeCustomer.size(); i++)
	{
		if (trim(toUpper(name)) == trim(toUpper(tempServeCustomer[i].name)))
		{
			return i;
		}
	}
	return -1;
}

string AppController::getFirstName(const std::string& name)
{
	string firstName = "";

	for (char c : name)
	{
		if (isspace(c))
		{
			break;
		}
		firstName += c;
	}
	return firstName;
}