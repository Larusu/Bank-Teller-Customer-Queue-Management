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
    void showTellerMenu();         // Displays the teller main menu.
private:
    QueueManager& queueManager;
    Statistics& stats;
    CustomerInterface& customerUI;
    std::map<std::string, int>& g_announcements;
private:
    // ---------- Teller ----------
    void registerCustomer();          // Collects data and adds a customer to the queue.
    void serveCustomer();        // Serves the next customer in the queue.
    void displayQueue();         // Displays current queue of customers.
    void showStatistics();       // Displays statistics like served customers, transaction counts, etc.
};