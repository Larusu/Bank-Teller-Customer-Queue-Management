#pragma once
#include "QueueManager.h"
#include "Customer.h"
#include "Statistics.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <map>
#include <sstream>
#include <fstream>

class CustomerInterface
{
public:
	CustomerInterface(QueueManager& queueManager, Statistics& stats, std::map<std::string, int>& announce)
            : queueManager( queueManager ), stats( stats ), g_announcements(announce)
	{ }
    // Public Interface
    void showCustomerMenu();
    void setWaitingForCompletion(const Customer& customer);
private:
	QueueManager& queueManager;                  // Reference to queue manager
	Statistics& stats;                           // Reference to statistics manager
    std::map<std::string, int>& g_announcements; // Reference to global announcements
	std::vector<Customer> waitingForCompletion;  // Tracks customers waiting to complete transactions
private:
    // Customer flow
    void registerCustomer();                // Handles register of customer's account
    void choosingTransaction();             // Handles input transaction and inserting in queue
    void completeTransaction();             // Handles completion of transaction

    // Customer Transactions
    void account(const Customer& customer);   // Shows customer's account info.
	void deposit(const Customer& customer);   // Handles deposit transactions.
	void withdraw(const Customer& customer);  // Handles withdrawal transactions.
	void transfer(const Customer& customer);  // Handles fund transfer between accounts.
	void payment(const Customer& customer);   // Handles bill or other payments.

    // Utilities
    bool isInTheWaitingList(const std::string& bankId);         // Returns true when customer is currently in the queue
    std::string getFirstName(const std::string& name);          // Returns only the first name
    void printTransactionReceipt(const Customer& customer, 
            const std::string& transactionType, 
            const std::vector<std::string>& additionalInfo = {}); // Printing receipts after completing a transaction
    bool isBankIdRegistered(const std::string& bankId);         // Checks if the given bankId is already registered in the system.
    bool handleExitPrompt();                                    // Prompts the user to confirm exit and returns true if they choose 'y'.
};
