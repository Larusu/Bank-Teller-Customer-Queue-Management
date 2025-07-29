#include "CustomerInterface.h"

using namespace std;
using namespace Utils;

void CustomerInterface::showCustomerMenu()
{
	clearScreen();

    int choice = 0, choiceMin = 1, choiceMax = 4;
    
    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout <<   "║            WELCOME / INSTRUCTIONS           ║" << "\n";
    cout <<   "╠═════════════════════════════════════════════╣" << "\n";
    cout <<   "║    Please register first before choosing    ║" << "\n";
    cout <<   "║       a transaction. If you're already      ║" << "\n";
    cout <<   "║     registered, you may proceed directly    ║" << "\n";
    cout <<   "║            using your Bank ID.              ║" << "\n";
    cout <<   "╚═════════════════════════════════════════════╝" << "\n";
    cout << "┌─────────────────────────────────────────────┐" << "\n";
    cout << "│             CUSTOMER INTERFACE              │" << "\n";
    cout << "├─────┬───────────────────────────────────────┤" << "\n";
    cout << "│  1  │ Register                              │" << "\n";
    cout << "├─────┼───────────────────────────────────────┤" << "\n";
    cout << "│  2  │ Choose a Transaction                  │" << "\n";
    cout << "├─────┼───────────────────────────────────────┤" << "\n";
    cout << "│  3  │ Complete the Transaction              │" << "\n";
    cout << "├─────┼───────────────────────────────────────┤" << "\n";
    cout << "│  4  │ Exit                                  │" << "\n";
    cout << "└─────┴───────────────────────────────────────┘" << "\n";

    choice = inputInteger("Choice: ", choiceMin, choiceMax);
    switch (choice)
    {
        case 1: registerCustomer(); break;
        case 2: choosingTransaction(); break;
        case 3: completeTransaction(); break;
        case 4: cout << "\n╔═════════════════════════════════════════════╗" << "\n";
                cout <<   "            Thank you for visiting.            " << "\n";
                cout <<   "╚═════════════════════════════════════════════╝" << "\n";
                return;
    }
}

void CustomerInterface::registerCustomer()
{
    clearScreen();

    // Declare customer details 
    double balance = 0.0, minBal = 500.0, maxBal = 10000000.0;
	string firstName = "", lastName = "", fullName = "", transaction = "";
	int age = 0, minAge = 18, maxAge = 99;
    string bankId;

    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout << "║              Enter Your Details             ║" << "\n";
    cout << "╠═════════════════════════════════════════════╣" << "\n";
    cout << "║   Please fill in all the required fields.   ║" << "\n";
    cout << "║   A receipt with your Bank ID will be       ║" << "\n";
    cout << "║   provided to you via a .txt file.          ║" << "\n";
    cout << "╚═════════════════════════════════════════════╝" << "\n";

    // Prompts user to enter their informatoion
    lastName = inputString("Enter your Last Name: ");
	firstName = inputString("Enter your First Name: ");
    age = inputInteger("Enter your age: ", minAge, maxAge);
    balance = inputDouble("Enter initial deposit: ", minBal, maxBal);

    // Proper formatting and generating ID
	fullName = firstName + " " + lastName;
    fullName = nameFormatter(fullName);
    bankId = generateBankId(); 

    // create receipt using full name
    string nameToTxt = "ID_";
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
    cout << "Please check your Bank ID through " << nameToTxt << " then go to transaction to complete the queue" << endl;
}

void CustomerInterface::choosingTransaction()
{
    clearScreen();

    // Declare customer details and Bank ID
    string name, transaction, userBankId;
    int age;
    double balance;

    // Display Header
    cout << "┌─────────────────────────────────────────────┐" << "\n";
    cout << "│            CHOOSE A TRANSACTION             │" << "\n";
    cout << "└─────────────────────────────────────────────┘" << "\n";

    while(true)
    {
        string line, storedBankId;

        // Prompt user to enter their Bank ID
        userBankId = inputBankId("Enter your BankID: ");

        // For tracking if found
        bool found = false;

        // Open the file containing registered customers
        ifstream checkRegistered("RegisteredCustomers.txt");
        while(getline(checkRegistered, line))
        {
            stringstream ss(line); 
            string tempName, ageStr, balanceStr;

            getline(ss, storedBankId, '|');
            getline(ss, tempName, '|');
            getline(ss, ageStr, '|');
            getline(ss, balanceStr, '|');

            // If the stored Bank ID matches the input, capture the user's details
            if (storedBankId == userBankId)
            {
                name = tempName;
                age = stoi(ageStr);
                balance = stod(balanceStr);
                found = true;
                break; // Stop searching
            }
        }
        checkRegistered.close();
        
        // If the Bank ID was found, proceed
        if (found)
        {
            cout << "Bank ID found. Proceeding with transaction...\n";
            break;
        }
        else
        {
            cout << "Bank ID Not Found.\n";
        }

        // If not found, ask if the user wants to exit
        char exit = getYesNoChoice("Do you want to exit? [y or n]: ");
        if(exit == 'y') return;
    } 

    // Define transaction range and display options
    int choiceTransaction = 0, choiceMin = 1, choiceMax = 5;
    cout << "\n┌─────┬─────── Transaction Types ─────────────┐" << "\n";
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

    // Create a new Customer object with the collected data
    Customer c = queueManager.createCustomer(name, age, transaction, balance, userBankId);
	// Add the customer to the queue for service
    queueManager.addCustomer(c);
    // Record service time statistics
	stats.recordService(c.estimatedServiceTime);

    clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "  🛈 Added to the queue! Wait for turn." << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
}

void CustomerInterface::completeTransaction()
{
    clearScreen();

    string userBankId;
    int attempts = 0;
    const int maxAttempts = 3;

    // Display Header
    cout << "┌─────────────────────────────────────────────┐" << "\n";
    cout << "│             COMPLETE TRANSACTION            │" << "\n";
    cout << "└─────────────────────────────────────────────┘" << "\n";

    while(attempts < maxAttempts)
    {
        // Prompt user to enter their Bank ID
        userBankId = inputBankId("Enter your BankID: ");

        // Validation to enter a valid Bank ID, allowing up to 3 attempts
        if(!isBankIdRegistered(userBankId))
        {
            attempts++;
            int remainingTries = maxAttempts - attempts - 1;

            cout << "\n╔═════════════════════════════════════════════╗" << "\n";
            cout <<   "   Bank ID does not exist. " << remainingTries << " attempt(s) left.\n";
            cout <<   "╚═════════════════════════════════════════════╝" << "\n";
            
            if (attempts == maxAttempts)
            {
                clearScreen();
                cout << "\nToo many failed attempts. Returning to menu.\n";
                return;
            }

            continue;
        }

        // Check if the user is still in the queue
        if(queueManager.isInTheQueue(userBankId))
        {
            cout << "\n╔═════════════════════════════════════════════╗" << "\n";
            cout <<   "  🛈 You are still in the queue. Please wait." << "\n";
            cout <<   "╚═════════════════════════════════════════════╝" << "\n";
            return;
        }

        // Check if the user has a completed transaction waiting
        if(!isInTheWaitingList(userBankId))
        {
            cout << "\n╔═════════════════════════════════════════════╗" << "\n";
            cout <<   "   ⚠️     No transaction found." << "\n";
            cout <<   "╚═════════════════════════════════════════════╝" << "\n";
            return;
        }

        break; // All checks passed, continue processing
    }

    Customer handleTransaction;

    for (size_t i = 0; i < waitingForCompletion.size(); ++i)
    {
        if (waitingForCompletion[i].bank.bankId == userBankId)
        {
            handleTransaction = waitingForCompletion[i];
            waitingForCompletion.erase(waitingForCompletion.begin() + i);
            break;
        }
    }

    string transactionType = handleTransaction.transactionType;

    if (transactionType == "Account")		account(handleTransaction);
	else if (transactionType == "Deposit")	deposit(handleTransaction);
	else if (transactionType == "Withdraw")	withdraw(handleTransaction);
	else if (transactionType == "Transfer")	transfer(handleTransaction);
	else if (transactionType == "Payment")	payment(handleTransaction);

    clearScreen();
    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout <<   "            Thank you for visiting.            " << "\n";
    cout <<   "╚═════════════════════════════════════════════╝" << "\n";
}

bool CustomerInterface::isInTheWaitingList(const string& currentBankId)
{
    for (const Customer& c : waitingForCompletion)
    {
        if (c.bank.bankId == currentBankId) return true;
    }
    return false;
}

void CustomerInterface::account(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);

    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout << "║               " << firstName << "'s Details             ║" << "\n";
    cout << "╠═════════════════════════════════════════════╣" << "\n";
    cout << "║ Full Name: " << left << setw(33) << customer.name << "║" << '\n';
    cout << "║ Age:        " << left << setw(32) << customer.age << "║" << '\n';
    cout << "║ Balance:    " << setw(32) << left << fixed << setprecision(2) << customer.bank.balance << "║" << '\n';
    cout << "║ Bank ID:    " << left << setw(32) << customer.bank.bankId << "║" << '\n';
    cout << "╚═════════════════════════════════════════════╝" << "\n";

    printTransactionReceipt(customer, "Account Info");

    if (handleExitPrompt()) return;
    showCustomerMenu();
}

void CustomerInterface::deposit(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	double depositAmount, minDeposit = 500.0, maxDeposit = 10000000.0;

    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout << "║        " << firstName << "'s Depositing             ║" << "\n";
    cout << "╚═════════════════════════════════════════════╝" << "\n";
    depositAmount = inputDouble("Deposit Amount: ", minDeposit, maxDeposit);

    queueManager.depositMoney(depositAmount, bankId);
    
    printTransactionReceipt(customer, "Deposit", {
        "Deposited: PHP " + formatMoney(depositAmount),
        "New Balance: PHP " + formatMoney(depositAmount + customer.bank.balance)
    });

    if (handleExitPrompt()) return;
    showCustomerMenu();
}

void CustomerInterface::withdraw(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	double withdrawAmount, minWithdraw = 0, maxWithdraw = customer.bank.balance;

    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout << "║     " << firstName << "'s Withdrawing Money       ║" << "\n";
    cout << "╚═════════════════════════════════════════════╝" << "\n";
    cout << " Available balance: " << maxWithdraw << endl;
    withdrawAmount = inputDouble("Withdraw Amount: ", minWithdraw, maxWithdraw);

    queueManager.deductFromBalance(withdrawAmount, bankId);

    printTransactionReceipt(customer, "Deposit", {
        "Withdrawn: PHP " + formatMoney(withdrawAmount),
        "Remaining Balance: PHP " + formatMoney(customer.bank.balance - withdrawAmount)
    });

    if (handleExitPrompt()) return;
    showCustomerMenu();
}

void CustomerInterface::transfer(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	string recipientId;
	double transferAmount, minTransfer = 0, maxTransfer = customer.bank.balance;
	char choice;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║     " << firstName << "'s Transferring Money       ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
	cout << " Available balance: " << maxTransfer << endl;

    // Ask for recipient's Bank ID, max 3 attempts
    int attempts = 0;
    const int maxAttempts = 3;
    while(attempts < maxAttempts)
    {
        recipientId = inputBankId("Enter recipient's Bank ID: ");
        
        // Prevent transferring to own account
        if(recipientId == bankId)
        {
            cout << "You cannot transfer into your own account. Please try again!\n";
            continue;
        }

        // Check if recipient's Bank ID exists
        if(!isBankIdRegistered(recipientId))
        {
            attempts++;
            int remainingTries = maxAttempts - attempts;

            cout << "Recipient's Bank ID doesn't exist. " << remainingTries << " attempt(s) left.\n";

            if (attempts == maxAttempts)
            {
                waitingForCompletion.push_back(customer);
                clearScreen();
                cout << "\nToo many failed attempts. Returning to menu.\n";
                return;
            }

            continue;
        }

        break; // Valid recipient ID
    }

    transferAmount = inputDouble("Transfer Amount: ", minTransfer, maxTransfer);

    // Perform money transfer via QueueManager
    queueManager.transferMoney(transferAmount, bankId, recipientId);

    // Print transaction receipt to file
    printTransactionReceipt(customer, "Transfer", {
        "Transferred: PHP " + formatMoney(transferAmount),
        "Recipient Bank ID: " + recipientId,
        "Remaining Balance: PHP " + formatMoney(customer.bank.balance - transferAmount)
    });

    if (handleExitPrompt()) return;
    showCustomerMenu();
}

void CustomerInterface::payment(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	string paymentPurpose = "";
	double paymentAmount, minPayment = 0, maxPayment = customer.bank.balance;

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout << "║        " << firstName << "'s Payment                ║" << "\n";
	cout << "╚═════════════════════════════════════════════╝" << "\n";
	cout << " Available balance: " << maxPayment << endl;
	paymentPurpose = inputString("Enter Purpose of Payment: ");
	paymentAmount = inputDouble("Payment Amount: ", minPayment, maxPayment);

	queueManager.deductFromBalance(paymentAmount, bankId);

    printTransactionReceipt(customer, "Deposit", {
        "Payment: PHP " + formatMoney(paymentAmount),
        "To: " + paymentPurpose,
        "Remaining Balance: PHP " + formatMoney(customer.bank.balance - paymentAmount)
    });

	if (handleExitPrompt()) return;
    showCustomerMenu();
}

bool CustomerInterface::isBankIdRegistered(const string& bankId)
{
    string line, storedBankId;

    // Open file and check if Bank ID exists
    ifstream checkRegistered("RegisteredCustomers.txt");
    while(getline(checkRegistered, line))
    {
        stringstream ss(line); 
        string tempName, ageStr, balanceStr;

        getline(ss, storedBankId, '|');

        if(storedBankId == bankId) 
        {
            return true;
        }
    } 
    checkRegistered.close();

    return false;
}

string CustomerInterface::getFirstName(const string& name)
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

void CustomerInterface::printTransactionReceipt(
    const Customer& customer, 
    const string& transactionType, 
    const vector<string>& additionalInfo)
{
    // Create folder if it doesn't exist
    #ifdef _WIN32
        _mkdir("receipts");
    #else
        mkdir("receipts", 0777);
    #endif

    // Generate unique filename
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char filename[100];
    strftime(filename, sizeof(filename), "receipts/receipt_%Y%m%d_%H%M%S.txt", localTime);

    ofstream file(filename);

    // Create box title: FirstName - TransactionType
    string firstName = getFirstName(customer.name);
    string title = firstName + " - " + transactionType;

    file << title << '\n';
    file << "Full Name" << customer.name << '\n';
    file << "Age " << customer.age << '\n';
    file << "Balance " << customer.bank.balance << '\n';
    file << "Bank ID: " << customer.bank.bankId << '\n';

    for (const string& line : additionalInfo)
    {
        file << "║" << line << "║\n";
    }
    file.close();

    cout << "\nReceipt saved to file: " << filename << "\n";
}

bool CustomerInterface::handleExitPrompt()
{
    char choice = getYesNoChoice("Do you want to exit [y or n]:");
    if (choice == 'y') 
    {
		clearScreen();
		return true;
	}
    clearScreen();
    return false;
}

void CustomerInterface::setWaitingForCompletion(const Customer& customer)
{
    waitingForCompletion.push_back(customer);
}