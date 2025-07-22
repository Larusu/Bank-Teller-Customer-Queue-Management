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
    double getAverageServiceTime();                 // Returns average service time.
    int getTotalCustomersServed();                  // Returns total number of customers served.
};
