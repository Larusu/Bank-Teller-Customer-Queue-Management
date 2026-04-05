#pragma once
#include "QueueManager.h"
#include "Customer.h"
#include "Statistics.h"
#include "Utils.h"
#include "CustomerInterface.h"

#include <iostream>
#include <string>
#include <fstream>
#include <map>

class TellerInterface
{
public:
    TellerInterface(QueueManager& queueManager, Statistics& stats, std::map<std::string, int>& announce, CustomerInterface& customerUI)
       : queueManager(queueManager), stats(stats), g_announcements(announce), customerUI(customerUI)
    { }
    // Public Interface
    void showTellerMenu();                      // Displays the teller main menu.
private:
    QueueManager& queueManager;                  // Handles customer queue operations
    Statistics& stats;                           // Tracks and displays service statistics
    CustomerInterface& customerUI;               // For updating customer-related actions
    std::map<std::string, int>& g_announcements; // Reference to global announcements
private:
    // Teller
    void registerCustomer();          // Collects data and adds a customer to the queue.
    void serveCustomer();             // Serves the next customer in the queue.
    void displayQueue();              // Displays current queue of customers.
    void showStatistics();            // Displays statistics like served customers, transaction counts, etc.
};