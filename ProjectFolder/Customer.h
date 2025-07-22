#pragma once

struct Customer 
{
    int id;
    std::string name;
    int age;
    std::string transactionType;
    int estimatedServiceTime; // simulated (e.g., 5 mins)
    int arrivalOrder;         // used for FIFO or priority ordering
};
