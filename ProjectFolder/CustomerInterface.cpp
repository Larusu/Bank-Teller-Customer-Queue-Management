#include "CustomerInterface.h"

using namespace std;
using namespace Utils;

void CustomerInterface::showCustomerMenu()
{
	clearScreen();

	double balance = 0.0, minBal = 500.0, maxBal = 10000000.0;
	string firstName = "", lastName = "", fullName = "", transaction = "";
	int age = 0, minAge = 18, maxAge = 99;
	int choiceTransaction = 0, choiceMin = 1, choiceMax = 5;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║             Enter Your Details              ║" << "\n";
	cout << "╠═════════════════════════════════════════════╣" << "\n";
	cout << "║    If your name is already in the queue,    ║" << "\n";
	cout << "║      you will automatically proceed to      ║" << "\n";
	cout << "║          the transaction process.           ║" << "\n";
	cout << "║      Please enter your name correctly.      ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
	lastName = inputString("Enter you Last Name: ");
	firstName = inputString("Enter you First Name: ");
	fullName = firstName + " " + lastName;

	// If the customer was served using their name, check their transaction type
	int index = findServedCustomerIndex(fullName);
	if (index > -1)
	{
		Customer getCustomer = queueManager.getServedCustomers()[index];

		if (getCustomer.transactionType == "Account")		account(getCustomer);
		else if (getCustomer.transactionType == "Deposit")	deposit(getCustomer);
		else if (getCustomer.transactionType == "Withdraw")	withdraw(getCustomer);
		else if (getCustomer.transactionType == "Transfer")	transfer(getCustomer);
		else if (getCustomer.transactionType == "Payment")	payment(getCustomer);

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
	cout << "  🛈 Added to the queue! Wait for turn." << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";

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

void CustomerInterface::account(Customer& servedCustomer)
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

void CustomerInterface::deposit(Customer& servedCustomer)
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

void CustomerInterface::withdraw(Customer& servedCustomer)
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

void CustomerInterface::transfer(Customer& servedCustomer)
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

void CustomerInterface::payment(Customer& servedCustomer)
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

string CustomerInterface::getFirstName(const std::string& name)
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

int CustomerInterface::findServedCustomerIndex(const std::string& name)
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