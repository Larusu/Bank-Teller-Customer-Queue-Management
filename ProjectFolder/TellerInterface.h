#pragma once
#include "QueueManager.h"
#include "Customer.h"
#include "Statistics.h"
#include "Utils.h"

#include <iostream>
#include <string>

class TellerInterface
{
public:
    TellerInterface(QueueManager& queueManager, Statistics& stats)
        : queueManager(queueManager), stats(stats)
    { }
    void showTellerMenu();         // Displays the teller main menu.
private:
    QueueManager& queueManager;
    Statistics& stats;
private:
    // ---------- Teller ----------
    void addCustomer();          // Collects data and adds a customer to the queue.
    void serveCustomer();        // Serves the next customer in the queue.
    void displayQueue();         // Displays current queue of customers.
    void showStatistics();       // Displays statistics like served customers, transaction counts, etc.
};