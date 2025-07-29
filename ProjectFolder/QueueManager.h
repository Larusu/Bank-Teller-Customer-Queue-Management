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
    void updateCustomersBalance(double balance, const std::string& bankId, double (*op)(double, double), const std::string& recipientId = "");
    static double useOperator(double a, double b, double (*func)(double, double)) ;
    static double add(double x, double y);
    static double subtract(double x, double y);

public: // Public Methods
    // ---------- Customer Creation ----------
    Customer createCustomer(
        const std::string& name,
        int age,
        const std::string& transactionType,
        double balance
    );                                              // Creates and returns a new Customer object.
    Customer createCustomer(
        const std::string& name, 
        int age, 
        const std::string& transactionType, 
        double balance, 
        const std::string& bankID
    );

    // ---------- Queue Management ----------
    void addCustomer(const Customer& newCustomer);  // Adds a new customer to the queue.
    Customer serveCustomer();                       // Removes and returns the next customer to be served.
    void displayQueue();                            // Displays all customers currently in the queue.
    bool hasCustomers();                            // Returns true if queue is not empty.
    int getCurrentQueueLength();                    // Returns number of customers currently in queue.
    int getPeakQueueLength(int currentQueueLength); // Updates and returns peak queue length.
    
    // ---------- Transactions ----------
    void depositMoney(double amount, const std::string& bankId);                 // Adds money to a customer's balance.
    void transferMoney(double amount, const std::string& senderId, const std::string& recipientId); // Transfers money between customers.
    void deductFromBalance(double amount, const std::string& bankId);            // Deducts amount from a customer's balance.
    
    bool isInTheQueue(const std::string& bankId);
};
