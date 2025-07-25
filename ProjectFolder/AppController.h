#pragma once
#include "QueueManager.h"
#include "Statistics.h"
#include "Utils.h"
#include <iostream>

// Handles the main application loop and menu navigation.
class AppController
{
private: // Private Attributes 
    QueueManager queueManager;   // Manages the customer queue.
    Statistics stats;            // Tracks and reports application statistics.

private: // Private Methods 
    // ---------- Customer ----------
    void showCustomerMainMenu();                      // Displays the customer main menu.
    void customerAccount(Customer& servedCustomer);   // Shows customer's account info.
    void customerDeposit(Customer& servedCustomer);   // Handles deposit transactions.
    void customerWithdraw(Customer& servedCustomer);  // Handles withdrawal transactions.
    void customerTransfer(Customer& servedCustomer);  // Handles fund transfer between accounts.
    void customerPayment(Customer& servedCustomer);   // Handles bill or other payments.

    // ---------- Teller ----------
    void showTellerMainMenu();         // Displays the teller main menu.
    void handleAddCustomer();          // Collects data and adds a customer to the queue.
    void handleServeCustomer();        // Serves the next customer in the queue.
    void handleDisplayQueue();         // Displays current queue of customers.
    void handleShowStatistics();       // Displays statistics like served customers, transaction counts, etc.

    // ---------- Utility methods ----------
    int findServedCustomerIndex(const std::string& name);   // Finds the index of a served customer by name.
    std::string getFirstName(const std::string& name);      // Extracts first name from full name string.

    // ---------- Main Menu ----------
    void showMasterMainMenu();        // Displays the top-level master menu 

public:
    void run();  // Starts the application loop. Called from main().
};