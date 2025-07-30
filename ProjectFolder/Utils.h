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
    // Formatting Utilities
    std::string toUpper(const std::string& str);                    // Converts string to uppercase.
    std::string trim(const std::string& str);                       // Trim both leading and trailing whitespace
    std::string formatMoney(double amount);                         // Formats a double value to a string with two decimal places
    std::string nameFormatter(const std::string& name);             // Formats name into a standard format.

    // Input Utilities
    int inputInteger(const std::string& prompt, int min, int max);  // Prompts and validates integer input within a range  
    std::string inputString(const std::string& prompt);             // Prompts for and returns a string input.
    char inputChar(const std::string& prompt);                      // Prompts for and returns a single character input  
    double inputDouble(const std::string& prompt, double min, double max); // Prompts for and return a double input.
    std::string inputBankId(const std::string& prompt);             // Prompts for Bank ID and return a valid Bank ID.
    char getYesNoChoice(const std::string& prompt);                 // Prompts the user for a 'y' or 'n' response and returns it in lowercase.
   
    // Generator and Estimation
    int estimateServiceTime(const std::string& transactionType);    // Returns estimated time based on transaction type.
    std::string generateBankId();                                   // Generates a unique 3-3 formatted bank ID 
    std::string generateRandomDigits(int length);                   // Generates a string of random digits
    
    // Sysytem Utilities
    void clearScreen();                                             // Clears the screen.
}