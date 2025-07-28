#pragma once
#include "Customer.h"
#include "Utils.h"
#include <queue>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

// Handles queue logic: adding, serving, and listing customers.
class QueueManager
{
private: // Private attributes
    std::queue<Customer> regularQueue;              // Queue of customers waiting to be served.
    std::vector<Customer> servedCustomers;          // List of customers who have been served.

    int customerCounter = 0;                        // Used to generate unique customer IDs.
    int peakQueueLength = 0;                        // Tracks the maximum queue length recorded.

private: // Private Methods
    // ---------- Utility / Internal Helpers ----------
    bool isVip(const std::string& name);            // Determines if a customer is a VIP based on name.
    std::string nameFormatter(const std::string& name); // Formats name into a standard format.
    std::string generateBankId();                   // Generates a unique bank ID.
    std::string generateCode(int length);           // Helper to generate random numeric strings.

public: // Public Methods
    // ---------- Customer Creation ----------
    bool isExistingName(const std::string& name);   // Checks if a name already exists in the queue.
    Customer createCustomer(
        const std::string& name,
        int age,
        const std::string& transactionType,
        double balance
    );                                              // Creates and returns a new Customer object.

    // ---------- Queue Management ----------
    void addCustomer(const Customer& newCustomer);  // Adds a new customer to the queue.
    Customer serveCustomer();                       // Removes and returns the next customer to be served.
    void displayQueue();                            // Displays all customers currently in the queue.
    bool hasCustomers();                            // Returns true if queue is not empty.
    int getCurrentQueueLength();                    // Returns number of customers currently in queue.
    int getPeakQueueLength(int currentQueueLength); // Updates and returns peak queue length.
    Customer getFront();                            // Returns the front customer without removing them.

    // ---------- Transactions ----------
    void depositMoney(double deposit, const std::string& bankId);                 // Adds money to a customer's balance.
    void transferMoney(double amount, const std::string& senderId, const std::string& recipientId); // Transfers money between customers.
    void deductFromBalance(double amount, const std::string& bankId);            // Deducts amount from a customer's balance.

    // ---------- Statistics & Accessors ----------
    int getLastServiceTime();                         // Returns the ETA or time of last served customer.
    const std::vector<Customer>& getServedCustomers(); // Returns reference to list of served customers.
    const std::queue<Customer>& getPendingCustomers(); // Returns reference to current customer queue.
    void isServed(const Customer& customer);
};
