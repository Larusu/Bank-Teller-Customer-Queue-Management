#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <iomanip>

// Utility functions for input, estimation, and formatting.
namespace Utils
{
    int estimateServiceTime(const std::string& transactionType);    // Returns estimated time based on transaction type.
    void clearScreen();                                             // Clears the screen.
    std::string toUpper(const std::string& str);                    // Converts string to uppercase.
    int inputInteger(const std::string& prompt, int min, int max);  // Asks and validates for integer input.
    std::string inputString(const std::string& prompt);             // Prompts for and returns a string input.
    std::string inputString(const std::string& prompt, const std::string fields[], int size);
    std::string trim(const std::string& str);                       // Trim both leading and trailing whitespace
    char inputChar(const std::string& prompt);
    char getYesNoChoice(const std::string& prompt);
}