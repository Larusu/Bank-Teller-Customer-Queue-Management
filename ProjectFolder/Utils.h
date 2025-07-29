#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>  
#include <ctime>    
#include <set>

// Utility functions for input, estimation, and formatting.
namespace Utils
{
    int estimateServiceTime(const std::string& transactionType);    // Returns estimated time based on transaction type.
    void clearScreen();                                             // Clears the screen.
    std::string toUpper(const std::string& str);                    // Converts string to uppercase.
    int inputInteger(const std::string& prompt, int min, int max);  // Asks and validates for integer input.
    std::string inputString(const std::string& prompt);             // Prompts for and returns a string input.
    char inputChar(const std::string& prompt);
    std::string trim(const std::string& str);                       // Trim both leading and trailing whitespace
    char getYesNoChoice(const std::string& prompt);
    double inputDouble(const std::string& prompt, double min, double max);
    std::string inputBankId(const std::string& prompt);
    std::string generateBankId();
    std::string nameFormatter(const std::string& name); // Formats name into a standard format.
    std::string formatMoney(double amount);
}