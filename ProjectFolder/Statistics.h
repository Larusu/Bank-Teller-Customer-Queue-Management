#pragma once

// Tracks statistics like total customers served and average time.
class Statistics 
{
private:
    int totalCustomersServed = 0;
    int totalServiceTime = 0;

public:
    void recordService(int serviceTime);            // Records the time taken for a served customer.
    void displayStatistics(int peakQueueLength);    // Displays current statistics summary.
                           // Display overall number of Customer, served customer, not yet serve customer, average waiting time of all transactiosn
                           // Number of customer per types of transactions, average waiting time per type of transaction
    double getAverageServiceTime();                 // Returns average service time.
                                                    // Including the ones that have been served
    int getTotalCustomersServed();                  // Returns total number of customers served.
};
