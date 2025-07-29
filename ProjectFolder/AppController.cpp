#include "AppController.h"

using namespace std;
using namespace Utils;

void AppController::run()
{
	// Create folder if it doesn't exist
    #ifdef _WIN32
        _mkdir("customer_receipts");
		_mkdir("customer_bank_id");
		_mkdir("customer_queue_id");
    #else
        mkdir("customer_receipts", 0777);
		mkdir("customer_bank_id", 0777);
    	mkdir("customer_queue_id", 0777);
    #endif

	Customer customer;
	int choice = 0, choiceMin = 1, choiceMax = 3;

	// Run main loop
	while (true)
	{
		printAnnouncements();
		showMasterMainMenu();
		choice = inputInteger("Enter Choice: ", choiceMin, choiceMax);
		cout << endl;
		switch (choice)
		{
			case 1: customerUI.showCustomerMenu();	break;
			case 2: tellerUI.showTellerMenu();	break;
			case 3: cout << "╔═════════════════════════════════════════════╗" << "\n";
                	cout << "      Thank you for using JRL Bank Teller      " << "\n";
                	cout << "╚═════════════════════════════════════════════╝" << "\n";
					return;
			default: cout << "Invalid choice!"; break;
		}
	}
}

void AppController::showMasterMainMenu()
{
	cout << "┌─────────────────────────────────────────────┐" << "\n";
	cout << "│               JRL BANK TELLER               │" << "\n";
	cout << "├─────┬───────────────────────────────────────┤" << "\n";
	cout << "│  1  │ Enter Bank as Customer                │" << "\n";
	cout << "├─────┼───────────────────────────────────────┤" << "\n";
	cout << "│  2  │ Enter Bank as Teller                  │" << "\n";
	cout << "├─────┼───────────────────────────────────────┤" << "\n";
	cout << "│  3  │ Exit Bank                             │" << "\n";
	cout << "└─────┴───────────────────────────────────────┘" << "\n";
}

void AppController::printAnnouncements()
{
	if(!announcements.empty())
	{
		int count = 1;
		cout << "╔═════════════════════════════════════════════╗\n";
		for(const auto& pair : announcements)
		{
			cout << "    " << count << "       Now serving Customer ID " << pair.second << endl;
			count++;
		}
		cout << "╚═════════════════════════════════════════════╝\n";
	}
}