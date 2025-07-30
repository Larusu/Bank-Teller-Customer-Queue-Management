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
        case 4: clearScreen(); return;
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

    // Prompt to confirm details, otherwise exit
    char choice = getYesNoChoice("Confirm details? [y or n]: ");
    if(choice == 'n') return;

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
    ofstream getBankId("customer_bank_id/" + nameToTxt);
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
	cout <<   "   Please check " << nameToTxt << "\n";
    cout <<   "     for Bank ID to proceed to transaction        " << '\n';
    cout <<   "╚═════════════════════════════════════════════╝" << "\n";
}

void CustomerInterface::choosingTransaction()
{
    clearScreen();

    // Declare customer details and Bank ID
    string name, transaction, userBankId;
    int age;
    double balance;

    // Display Header
    cout << "╔═════════════════════════════════════════════╗" << "\n";
    cout << "║            CHOOSE A TRANSACTION             ║" << "\n";
    cout << "╚═════════════════════════════════════════════╝" << "\n";

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
        
        // Check if the customer is in the queue
        if(queueManager.isInTheQueue(userBankId))
        {
            cout << "\n╔═════════════════════════════════════════════╗" << "\n";
            cout <<   "  🛈 You are still in the queue. Please wait." << "\n";
            cout <<   "╚═════════════════════════════════════════════╝" << "\n";
            return;
        }

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

    // Prompt to confirm details, otherwise exit
    char choice = getYesNoChoice("Confirm details? [y or n]: ");
    if(choice == 'n') 
    { 
        clearScreen();
        return;
    }

    // Create a new Customer object with the collected data
    Customer c = queueManager.createCustomer(name, age, transaction, balance, userBankId);
	// Add the customer to the queue for service
    queueManager.addCustomer(c);
    // Record service time statistics
	stats.recordService(c.estimatedServiceTime);

    // Save the customer's queue number to a file named after their first name.
    // This helps the customer identify their unique ID and know their position in line.
    string nameTxt = c.name + ".txt";
    ofstream printCustomerCount("customer_queue_id/" + nameTxt);
    printCustomerCount << "Your unique customer ID is " << c.id << ". Please wait until your number is called.";
    printCustomerCount.close();

    clearScreen();

	cout << "\n╔═════════════════════════════════════════════╗" << "\n";
	cout <<   "   Check " << nameTxt << " for queue number" << "\n";
    cout <<   "╚═════════════════════════════════════════════╝" << "\n";
}

void CustomerInterface::completeTransaction()
{
    clearScreen();

    string userBankId;
    int attempts = 0;
    const int maxAttempts = 3;

    // Display Header
    cout << "╔═════════════════════════════════════════════╗" << "\n";
    cout << "║             COMPLETE TRANSACTION            ║" << "\n";
    cout << "╚═════════════════════════════════════════════╝" << "\n";

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
            clearScreen();
            cout << "\n╔═════════════════════════════════════════════╗" << "\n";
            cout <<   "  🛈 You are still in the queue. Please wait." << "\n";
            cout <<   "╚═════════════════════════════════════════════╝" << "\n";
            return;
        }

        // Check if the user has a completed transaction waiting
        if(!isInTheWaitingList(userBankId))
        {
            clearScreen();
            cout << "\n╔═════════════════════════════════════════════╗" << "\n";
            cout <<   "       ⚠️     No transaction found.            " << "\n";
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

    // Incerement total served for statistics
    stats.setTotalServed();

    // Remove the notification from the announcement 
    if (g_announcements.count(handleTransaction.bank.bankId)) 
    {
        g_announcements.erase(handleTransaction.bank.bankId);
    }
    clearScreen();
    cout << "\n╔═════════════════════════════════════════════╗" << "\n";
    cout <<   "      Thank you for using JRL Bank Teller      " << "\n";
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

    string formattedName = firstName + "'s Details";

    while (true)
    {
        cout << "\n╔═════════════════════════════════════════════╗" << "\n";
        cout << "║               " << left << setw(30) << formattedName << "║" << "\n";
        cout << "╠═════════════════════════════════════════════╣" << "\n";
        cout << "║ Full Name: " << left << setw(33) << customer.name << "║" << '\n';
        cout << "║ Age:        " << left << setw(32) << customer.age << "║" << '\n';
        cout << "║ Balance:    " << setw(32) << left << fixed << setprecision(2) << customer.bank.balance << "║" << '\n';
        cout << "║ Bank ID:    " << left << setw(32) << customer.bank.bankId << "║" << '\n';
        cout << "╚═════════════════════════════════════════════╝" << "\n";

        printTransactionReceipt(customer, "Account Info");

        if (handleExitPrompt()) return;
    }
}

void CustomerInterface::deposit(const Customer &customer)
{
    clearScreen();
    
    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	double depositAmount, minDeposit = 500.0, maxDeposit = 10000000.0;
    bool ask = true;

    string formattedName = firstName + "'s Depositing";

    while (true)
    {
        cout << "\n╔═════════════════════════════════════════════╗" << "\n";
        cout << "║             " << left << setw(32) << formattedName << "║" << "\n";
        cout << "╚═════════════════════════════════════════════╝" << "\n";
        if (ask)
        {
            depositAmount = inputDouble("Deposit Amount: ", minDeposit, maxDeposit);
            queueManager.depositMoney(depositAmount, bankId);
            
            stringstream depositLabel, newBalanceLabel, lineDiv;
            depositLabel << left << setw(16) << "Deposited: " << right << setw(25) << formatMoney(depositAmount);
            newBalanceLabel << left << setw(16) << "New Balance: " << right << setw(25) << formatMoney(depositAmount + customer.bank.balance);
            lineDiv << "- - - - - - - - - - - - - - - - - - - - -";
    
            printTransactionReceipt(customer, "Deposit", {
                depositLabel.str(),
                newBalanceLabel.str(),
                lineDiv.str()
            });
        } 

        if (handleExitPrompt()) return;
        ask = false;
    }
}

void CustomerInterface::withdraw(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	double withdrawAmount, minWithdraw = 0, maxWithdraw = customer.bank.balance;
    bool ask = true;

    string formattedName = firstName + "'s Withdrawing";

    while (true) 
    {
        cout << "\n╔═════════════════════════════════════════════╗" << "\n";
        cout << "║             " << left << setw(32) << formattedName << "║" << "\n";
        cout << "╚═════════════════════════════════════════════╝" << "\n";
        
        if (ask)
        {
            cout << "Available balance: " << maxWithdraw << endl;
            withdrawAmount = inputDouble("Withdraw Amount: ", minWithdraw, maxWithdraw);

            queueManager.deductFromBalance(withdrawAmount, bankId);

            stringstream withdrawLabel, remainingLabel, lineDiv;

            withdrawLabel << left << setw(16) << "Withdrawn:" << right << setw(25) << formatMoney(withdrawAmount);
            remainingLabel << left << setw(16) << "Remaining Balance:" << right << setw(23) << formatMoney(customer.bank.balance - withdrawAmount);
            lineDiv << "- - - - - - - - - - - - - - - - - - - - -";

            printTransactionReceipt(customer, "Withdraw", {
                withdrawLabel.str(),
                remainingLabel.str(),
                lineDiv.str()
            });
        }

        if (handleExitPrompt()) return;
        ask = false;
    }
}

void CustomerInterface::transfer(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	string recipientId;
	double transferAmount, minTransfer = 0, maxTransfer = customer.bank.balance;
	char choice;
    bool ask = true;

    string formattedName = firstName + "'s Transferring";

    while (true)
    {
        cout << "\n╔═════════════════════════════════════════════╗" << "\n";
        cout << "║             " << left << setw(32) << formattedName << "║" << "\n";
        cout << "╚═════════════════════════════════════════════╝" << "\n";

        if (ask) 
        {
            cout << "Available balance: " << maxTransfer << endl;

            // Ask for recipient's Bank ID
            while(true)
            {
                recipientId = inputBankId("Enter recipient's Bank ID: ");
                
                // Prevent transferring to own account
                if(recipientId == bankId)
                {
                    cout << "You cannot transfer into your own account. Please try again!\n";
                    continue;
                }

                break; // Valid recipient ID
            }

            transferAmount = inputDouble("Transfer Amount: ", minTransfer, maxTransfer);

            // Perform money transfer via QueueManager
            queueManager.transferMoney(transferAmount, bankId, recipientId);

            // Print transaction receipt to file
            stringstream transferredLabel, recipientLabel, remainingLabel, lineDiv;

            transferredLabel << left << setw(16) << "Transferred:" << right << setw(25) << formatMoney(transferAmount);
            recipientLabel << left << setw(16) << "Recipient ID:" << right << setw(25) << recipientId;
            remainingLabel << left << setw(16) << "Remaining:" << right << setw(25) << formatMoney(customer.bank.balance - transferAmount);
            lineDiv << "- - - - - - - - - - - - - - - - - - - - -";

            printTransactionReceipt(customer, "Transfer", {
                transferredLabel.str(),
                recipientLabel.str(),
                remainingLabel.str(),
                lineDiv.str()
            });
        }
        
        if (handleExitPrompt()) return;
        ask = false;
    }
}

void CustomerInterface::payment(const Customer &customer)
{
    clearScreen();

    string firstName = getFirstName(customer.name);
	string bankId = customer.bank.bankId;
	string paymentPurpose = "";
	double paymentAmount, minPayment = 0, maxPayment = customer.bank.balance;
    bool ask = true;

    string formattedName = firstName + "'s Payment";

    while (true)
    {
        cout << "\n╔═════════════════════════════════════════════╗" << "\n";
        cout << "║             " << left << setw(32) << formattedName << "║" << "\n";
        cout << "╚═════════════════════════════════════════════╝" << "\n";

        if (ask)
            {
            cout << "Available balance: " << maxPayment << endl;
            paymentPurpose = inputString("Enter Purpose of Payment: ");
            paymentAmount = inputDouble("Payment Amount: ", minPayment, maxPayment);

            queueManager.deductFromBalance(paymentAmount, bankId);

            stringstream paymentLabel, purposeLabel, remainingLabel, lineDiv;

            paymentLabel << left << setw(16) << "Payment:" << right << setw(25) << formatMoney(paymentAmount);
            purposeLabel << left << setw(16) << "To:" << right << setw(25) << paymentPurpose;
            remainingLabel << left << setw(16) << "Remaining:" << right << setw(25) << formatMoney(customer.bank.balance - paymentAmount);
            lineDiv << "- - - - - - - - - - - - - - - - - - - - -";

            printTransactionReceipt(customer, "Deposit", {
                paymentLabel.str(),
                purposeLabel.str(),
                remainingLabel.str(),
                lineDiv.str()
            });
        }

        if (handleExitPrompt()) return;
        ask = false;
    }
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
    // Generate unique filename
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char filename[100];
    strftime(filename, sizeof(filename), "customer_receipts/receipt_%Y%m%d_%H%M%S.txt", localTime);

    char dateStr[11]; // MM-DD-YYYY = 10 chars + null
    char timeStr[6];  // HH-MM = 5 chars + null

    strftime(dateStr, sizeof(dateStr), "%m-%d-%Y", localTime);
    strftime(timeStr, sizeof(timeStr), "%H:%M", localTime);

    // Optional: convert to std::string if needed
    string date = dateStr;
    string time = timeStr;

    ofstream file(filename);

    // Create box title: FirstName - TransactionType
    string firstName = getFirstName(customer.name);
    string title = firstName + " - " + transactionType;

    file << "┌─────────────────────────────────────────┐" << '\n';
    file << "│                 Receipt                 │" << '\n';
    file << "│           " << left << setw(30) << title << "│" << '\n';
    file << "│- - - - - - - - - - - - - - - - - - - - -│" << '\n';
    file << "│  Date: " << left << setw(27) << date << time << " │" << '\n';
    file << "│- - - - - - - - - - - - - - - - - - - - -│" << '\n';
    file << "│" << left << setw(16) << "Full Name" << right << setw(25) << customer.name << "│" <<'\n';
    file << "│" << left << setw(16) << "Age" << right << setw(25) << customer.age << "│" << '\n';
    file << "│" << left << setw(16) << "Balance" << right << setw(25) << customer.bank.balance << "│" << '\n';
    file << "│" << left << setw(16) << "Bank ID" << right << setw(25) << customer.bank.bankId << "│" << '\n';
    file << "│- - - - - - - - - - - - - - - - - - - - -│" << '\n';

    for (const string& line : additionalInfo)
    {
        file << "│" << line << "│" << "\n";
    }

    file << "|   ||| | ||| || ||| || ||| || ||| | ||   |" << '\n';
    file << "|   ||| | ||| || ||| || ||| || ||| | ||   |" << '\n';
    file << "|   ||| | ||| || ||| || ||| || ||| | ||   |" << '\n';
    file << "└─────────────────────────────────────────┘" << '\n';

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