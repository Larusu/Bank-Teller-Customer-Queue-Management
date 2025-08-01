﻿#include "Utils.h"

using namespace std;

string Utils::toUpper(const string& str)
{
	string copy = str;
	transform(copy.begin(), copy.end(), copy.begin(), ::toupper);

	return copy;
}

string Utils::trim(const std::string& str) 
{
	auto start = find_if_not(str.begin(), str.end(), ::isspace);
	auto end = find_if_not(str.rbegin(), str.rend(), ::isspace).base();

	return string(start, end);
}

string Utils::formatMoney(double amount) 
{
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return ss.str();
}

string Utils::nameFormatter(const string& name)
{
	string newName;
	bool firstLetter = true;

	for (char n : Utils::trim(name))
	{
		if (firstLetter)
		{
			newName += toupper(n);
			firstLetter = false;
			continue;
		}

		if (isspace(n))
		{
			newName += " ";
			firstLetter = true;
			continue;
		}

		newName += tolower(n);
	}

	return newName;
}

int Utils::inputInteger(const string& prompt, int min, int max)
{
	int input = 0;

	while (true)
	{
		cout << prompt;

		if (!(cin >> input)) 
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number.\n> ";
			continue;
		}
		cin.ignore(1000, '\n');

		if (input < min || input > max)
		{
			cout << "Input must be between " << min << " and " << max << ". Please try again.\n> ";
			continue;
		}

		return input;
	}
}

double Utils::inputDouble(const string& prompt, double min, double max)
{
	double input;

	while (true)
	{
		cout << prompt;

		if (!(cin >> input))
		{
			cin.clear();                  // Clear the error flag
			cin.ignore(1000, '\n');       // Discard bad input
			cout << "Invalid input. Please enter a numeric value.\n";
			continue;
		}

		cin.ignore(1000, '\n');           // Clear newline left in buffer

		if (input < min || input > max)
		{
			cout << "Input must be between " << min << " and " << max << ". Please try again.\n";
			continue;
		}

		return input;
	}
}

string Utils::inputString(const string& prompt)
{
	string input;

	while (true)
	{
		cout << prompt;
		if (!getline(cin, input))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please try again.\n> ";
		}

		input = Utils::trim(input);

		bool isValid = true;
		for (char c : input)
		{
			if (!isalpha(c) && !isspace(c))
			{
				isValid = false;
				break;
			}
		}
		if (!isValid)
		{
			cout << "Input must be letters only. Please try again.\n> ";
			continue;
		}

		if (!input.empty())
		{
			return input;
		}
		cout << "Input cannot be empty. Please try again.\n> ";
	}
}

char Utils::inputChar(const string& prompt)
{
	char input;
	cout << prompt;

	while (!(cin >> input))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n> ";
		continue;
	}cin.ignore(1000, '\n');

	return tolower(input);
}

char Utils::getYesNoChoice(const string& prompt)
{
	char input;

	while (true)
	{
		input = Utils::inputChar(prompt);

		if (tolower(input) != 'y' && tolower(input) != 'n')
		{
			cout << "Must be Y or N only! Please try again.\n> ";
			continue;
		}
		return tolower(input);
	}
}

string Utils::inputBankId(const string& prompt)
{
	string input;

	while(true)
	{
		cout << prompt;

		if (!getline(cin, input))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again.\n> ";
        }

		input = Utils::trim(input);
		// Validation format
        if(input.length() != 7 || input[3] != '-' ||
		   !isdigit(input[0]) || !isdigit(input[1]) || !isdigit(input[2]) ||
		   !isdigit(input[4]) || !isdigit(input[5]) || !isdigit(input[6]))
        {
            cout << "Bank ID must be in format 000-000 using digits only. Please try again!\n>";
            continue;
        }

		if(!input.empty())
		{
			return input;
		}

		cout << "Input cannot be empty. Please try again.\n> ";
	}
}

string Utils::generateBankId()
{
	ifstream registered("RegisteredCustomers.txt");
	string line = "", bankId = "";
	set<string> existingIds;

	while(getline(registered, line))
	{
		stringstream ss(line); 
		getline(ss, bankId, '|');
		existingIds.insert(bankId);
	}
	registered.close();

	string newCode;
	do {
        newCode = Utils::generateRandomDigits(3) + '-' + Utils::generateRandomDigits(3);
    } while (existingIds.find(newCode) != existingIds.end());

	return newCode;
}

string Utils::generateRandomDigits(int length)
{
	string code = "";

	while(code.length() < length)
	{
		char random = (rand() % 9) + '1';  // 1 to 9
		code += random;
	}

	return code;
}

int Utils::estimateServiceTime(const string& transactionType)
{
	string upper = Utils::trim(Utils::toUpper(transactionType));
	if (upper == "TRANSFER")return 6;   // 6 minutes - Transfers need account confirmation and possible approvals
	if (upper == "WITHDRAW")return 5;   // 5 minutes - Withdrawals take longer due to cash handling & verification
	if (upper == "PAYMENT") return 4;   // 4 minutes - Payments (bills, cards) are usually the quickest 
	if (upper == "DEPOSIT") return 3;   // 3 minutes - Deposits are relatively fast, just counting and logging
	if (upper == "ACCOUNT") return 2;	// 2 minutes - Account checking for accessing their details
	return 0;
}

void Utils::clearScreen()
{
#ifndef WINDOWS
	system("cls");
#else
	system("clear");
#endif
}

