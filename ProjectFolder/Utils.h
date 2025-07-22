#pragma once
#include <string>
#include <cstdlib>

// Utility functions for input, estimation, and formatting.
namespace Utils
{
    int estimateServiceTime(const std::string& transactionType); // Returns estimated time based on transaction type.
    void clearScreen();                                          // Clears the screen.
    std::string toUpper(const std::string& str);                 // Converts string to uppercase.
    int inputInteger(const std::string& prompt);                 // Asks and validates for integer input.
    std::string inputString(const std::string& prompt);          // Prompts for and returns a string input.
}