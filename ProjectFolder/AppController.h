#pragma once
#include "QueueManager.h"
#include "Statistics.h"
#include "Utils.h"
#include "CustomerInterface.h"
#include "TellerInterface.h"

#include <iostream>

// Handles the main application loop and menu navigation.
class AppController
{
public:
    AppController()
        : customerUI(queueManager, stats), tellerUI(queueManager, stats)
    { }

    void run();  // Starts the application loop. Called from main().

private: // Private Attributes 
    QueueManager queueManager;   // Manages the customer queue.
    Statistics stats;            // Tracks and reports application statistics.
    CustomerInterface customerUI;
    TellerInterface tellerUI;

private: 
    void showMasterMainMenu();        // Displays the top-level master menu 
};