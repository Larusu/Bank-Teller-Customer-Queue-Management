#pragma once
#include "QueueManager.h"
#include "Statistics.h"
#include "Utils.h"
#include "CustomerInterface.h"
#include "TellerInterface.h"

#include <iostream>
#include <map>
#include <ctime>

// For file handling
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h> 
#endif

// Handles the main application loop and menu navigation.
class AppController
{
public:
    AppController()
        : customerUI(queueManager, stats, announcements), tellerUI(queueManager, stats, announcements, customerUI)
    { }

    void run();                      // Starts the application loop.

private: // Private Attributes 
    QueueManager queueManager;       // Manages the customer queue.
    Statistics stats;                // Tracks and reports application statistics.
    CustomerInterface customerUI;    // Manages the customer interface.
    TellerInterface tellerUI;        // Handles the teller side.
    std::map<std::string, int> announcements;  // To store all the announcements for served customers
private: 
    void showMasterMainMenu();       // Displays the top-level master menu 
    void printAnnouncements();       // Printing all necessary announcements
};