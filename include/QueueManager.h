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
private: 
    std::queue<Customer> regularQueue;              // Queue of customers waiting to be served.
    std::vector<Customer> servedCustomers;          // List of customers who have been served.
    int customerCounter = 0;                        // Used to generate unique customer IDs.
    int peakQueueLength = 0;                        // Tracks the maximum queue length recorded.

private: 
    // Utility / Internal Helpers 
    bool isVip(const std::string& name);            // Determines if a customer is a VIP based on name.
    void updateCustomersBalance(double balance, const std::string& bankId, double (*op)(double, double));
                                                    // Updates the balance of a customer in the file
    static double useOperator(double a, double b, double (*func)(double, double)); // Applies the given binary function to two values
    static double add(double x, double y);          // Returns the sum of two values
    static double subtract(double x, double y);     // Returns the difference between two values

public:
    // Customer Creation 
    Customer createCustomer(
        const std::string& name, 
        int age, 
        const std::string& transactionType, 
        double balance, 
        const std::string& bankID
    ); // Creates and returns a new Customer object.

    // Queue Management 
    void addCustomer(const Customer& newCustomer);  // Adds a new customer to the queue.
    Customer serveCustomer();                       // Removes and returns the next customer to be served.
    void displayQueue();                            // Displays all customers currently in the queue.
    bool hasCustomers();                            // Returns true if queue is not empty.
    int getCurrentQueueLength();                    // Returns number of customers currently in queue.
    int getPeakQueueLength(int currentQueueLength); // Updates and returns peak queue length.
    
    // Transactions 
    void depositMoney(double amount, const std::string& bankId);                 // Adds money to a customer's balance.
    void transferMoney(double amount, const std::string& senderId, const std::string& recipientId); // Transfers money between customers.
    void deductFromBalance(double amount, const std::string& bankId);            // Deducts amount from a customer's balance.
    
    bool isInTheQueue(const std::string& bankId);    // Returns true if a customer with the given bankId exists in the regular queue.
};
