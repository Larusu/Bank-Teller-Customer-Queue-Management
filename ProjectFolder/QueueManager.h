#pragma once
#include "Customer.h"
#include <queue>
#include <string>

// Handles queue logic: adding, serving, and listing customers.
class QueueManager 
{
private:
    std::queue<Customer> regularQueue;
    int customerCounter = 0;
    int peakQueueLength = 0;

public:
    Customer createCustomer(const std::string& name, int age, const std::string& transactionType); // Creates a Customer object with generated ID and ETA.
    void addCustomer(const Customer& customer);     // Adds a customer to the queue.
    Customer serveCustomer();                       // Serves (removes) the first customer in queue.
    void displayQueue();                            // Displays all customers in the queue.
    bool hasCustomers();                            // Checks if the queue has customers.
    int getCurrentQueueLength();                    // Returns the current number of people in queue.
    int getPeakQueueLength();                       // Returns the highest number of people recorded in queue.
    int getLastServiceTime();                       // Returns the service time of the last served customer.
};
