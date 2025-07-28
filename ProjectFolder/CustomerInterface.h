#pragma once
#include "QueueManager.h"
#include "Customer.h"
#include "Statistics.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>

class CustomerInterface
{
public:
	CustomerInterface(QueueManager& queueManager, Statistics& stats)
		: queueManager( queueManager ), stats( stats )
	{ }
	void showCustomerMenu();								// Displays the customer main menu.
private:
	QueueManager& queueManager;
	Statistics& stats;
	std::vector<Customer> existingCustomersData;
private:
	int findServedCustomerIndex(const std::string& name);   // Finds the index of a served customer by name.
	void account(Customer& servedCustomer);   // Shows customer's account info.
	void deposit(Customer& servedCustomer);   // Handles deposit transactions.
	void withdraw(Customer& servedCustomer);  // Handles withdrawal transactions.
	void transfer(Customer& servedCustomer);  // Handles fund transfer between accounts.
	void payment(Customer& servedCustomer);   // Handles bill or other payments.
	std::string getFirstName(const std::string& name);      // Extracts first name from full name string.
	bool completeTransaction(const std::string& name);
};