#include "Utils.h"

using namespace std;

int Utils::estimateServiceTime(const string& transactionType)
{
	string upper = Utils::trim(Utils::toUpper(transactionType));
	if (upper == "WITHDRAW") return 5;  // 5 minutes - Withdrawals take longer due to cash handling & verification
	if (upper == "TRANSFER") return 4;  // 4 minutes - Transfers need account confirmation and possible approvals
	if (upper == "DEPOSIT") return 3;   // 3 minutes - Deposits are relatively fast, just counting and logging
	if (upper == "PAYMENT") return 2;	// 2 minutes - Payments (bills, cards) are usually the quickest
	return 3;
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

		while (!(cin >> input)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. \n";
			continue;
		}
		cin.ignore(1000, '\n');

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
		if (getline(cin, input))
		{
			input = Utils::trim(input);
			if (!input.empty()) return input;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n";
	}
}

string Utils::inputString(const string& prompt, const string fields[], int size)
{
	string input = "";

	// Show prompt and allowed fields
	cout << prompt <<  endl;
	for (int i = 0; i < size; i++)
	{
		cout << " - " << fields[i] << endl;
	}

	while (true)
	{
		cout << "> ";

		if (getline(cin, input))
		{
			input = Utils::trim(input);
			if (input.empty()) continue;
		}

		// Check if input matches any valid value
		bool valid = false;
		for (int i = 0; i < size; i++)
		{
			if (toUpper(input) == toUpper(fields[i]))
			{
				valid = true;
				break;
			}
		}

		if (valid) 
			return input;

		cout << "Input must be one of the listed options. Please try again.\n";
	}
}

string Utils::trim(const std::string& str) 
{
	auto start = find_if_not(str.begin(), str.end(), ::isspace);
	auto end = find_if_not(str.rbegin(), str.rend(), ::isspace).base();

	return string(start, end);
}