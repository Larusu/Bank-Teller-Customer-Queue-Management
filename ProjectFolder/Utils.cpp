#include "Utils.h"

using namespace std;

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

string Utils::toUpper(const string& str)
{
	string copy = str;
	transform(copy.begin(), copy.end(), copy.begin(), ::toupper);

	return copy;
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


string Utils::trim(const std::string& str) 
{
	auto start = find_if_not(str.begin(), str.end(), ::isspace);
	auto end = find_if_not(str.rbegin(), str.rend(), ::isspace).base();

	return string(start, end);
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
		return input;
	}
}