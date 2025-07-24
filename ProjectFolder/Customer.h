#pragma once
#include <string>

struct Customer 
{
    int id = 1;                            // Unique ID
    std::string name = "";                 // Customer name
    int age = 0;                           // Age for priority
    std::string transactionType = "";      // Deposit, Withdrawal, etc.
    int estimatedServiceTime = 0;          // Simulated service time in mins
    int arrivalOrder = 0;                  // Queue order
    int priorityLevel = 0;                 // 0 = Regular, 1 = Senior Citizen, 2 = VIP
};