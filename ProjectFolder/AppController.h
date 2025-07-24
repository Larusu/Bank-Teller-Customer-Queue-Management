#pragma once
#include "QueueManager.h"
#include "Statistics.h"
#include "Utils.h"
#include <iostream>

// Handles the main application loop and menu navigation.
class AppController 
{
private:
    QueueManager queueManager; 
    Statistics stats;
private:
    // Displays for admins
    void showMasterMainMenu();
    void showCustomerMainMenu();
    void showTellerMainMenu();            // Displays the main menu and gets user input.
    void handleAddCustomer();       // Collects customer data and adds to the queue.
    void handleServeCustomer();     // Serves the next customer and updates statistics.
    void handleDisplayQueue();      // Shows all customers currently in the queue.
    void handleShowStatistics();    // Displays summary statistics.

    // Displays for main menu
public:
    void run();  // Called from main()
};