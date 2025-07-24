#pragma once
#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <vector>

// Tracks statistics like total customers served and average time.
class Statistics 
{
private:
    int totalCustomersServed = 0;
    int totalServiceTime = 0;
    int totalServed = 0;
    int totalCustomerTransfer= 0;
    int totalCustomerWithdraw = 0;
    int totalCustomerPayment = 0;
    int totalCustomerDeposit = 0;
    int totalCustomerAccount = 0;

public:
    void recordService(int serviceTime);            // Records the time taken for a served customer.
    void displayStatistics(int peakQueueLength);    // Displays current statistics summary.
    double getAverageServiceTime();                 // Returns average service time.
    int getTotalCustomersServed();                  // Returns total number of customers served.
    void setTotalServed();

};
