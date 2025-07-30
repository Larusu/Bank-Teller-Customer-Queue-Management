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
    void showCustomerMenu();
    void setWaitingForCompletion(const Customer& customer);
private:
	QueueManager& queueManager;
	Statistics& stats;
	std::vector<Customer> waitingForCompletion;
    std::map<std::string, int>& g_announcements;
private:
    void registerCustomer();                // Handles register of customer's account
    void choosingTransaction();             // Handles input transaction and inserting in queue
    void completeTransaction();             // Handles completion of transaction

    // paki ayos ng interface dito
    void account(const Customer& customer);   // Shows customer's account info.
	void deposit(const Customer& customer);   // Handles deposit transactions.
	void withdraw(const Customer& customer);  // Handles withdrawal transactions.
	void transfer(const Customer& customer);  // Handles fund transfer between accounts.
	void payment(const Customer& customer);   // Handles bill or other payments.

    // Private Utilities
    bool isInTheWaitingList(const std::string& bankId);
    std::string getFirstName(const std::string& name);
    void printTransactionReceipt(const Customer& customer, 
            const std::string& transactionType, 
            const std::vector<std::string>& additionalInfo = {}); // ito rin pakiayos interface
    bool isBankIdRegistered(const std::string& bankId);
    bool handleExitPrompt();
};
