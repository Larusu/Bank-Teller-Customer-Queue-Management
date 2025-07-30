#pragma once
#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "Utils.h"

// Tracks statistics like total customers served and average time.
class Statistics 
{
public:
    Statistics()
    {
        SetConsoleOutputCP(CP_UTF8);                // Enables UTF-8 output in Windows console
    }
    void recordService(int serviceTime);            // Records the time taken for a served customer.
    void displayStatistics(int peakQueueLength);    // Displays current statistics summary.
    double getAverageServiceTime();                 // Returns average service time.
    int getTotalCustomersServed();                  // Returns total number of customers served.
    void setTotalServed();                          // Increments the total number of served customers by one.
    void recordCompleted();                         // Records a completed transaction by incrementing totalServed.

private:
    int totalCustomersServed = 0;
    int totalServiceTime = 0;
    int totalServed = 0;
    int totalCustomerTransfer= 0;
    int totalCustomerWithdraw = 0;
    int totalCustomerPayment = 0;
    int totalCustomerDeposit = 0;
    int totalCustomerAccount = 0;
};
