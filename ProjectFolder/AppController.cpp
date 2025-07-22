#include "AppController.h"

using namespace std;

void AppController::run()
{
	showMainMenu();
}

void AppController::showMainMenu()
{
	int choice = 0;
	std::cout << "=== BANK TELLER QUEUE SYSTEM ===" << std::endl;
	std::cout << "1. Add Customer to Queue " << std::endl;
	std::cout << "2. Serve Next Customer" << std::endl;
	std::cout << "3. Display Current Queue" << std::endl;
	std::cout << "4. Show Statistics" << std::endl;
	std::cout << "5. Exit" << std::endl;
	std::cout << "Enter choice : " << std::endl;

	while (choice == 0)
	{
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}
	}
}

void AppController::handleAddCustomer()
{

}

void AppController::handleServeCustomer()
{

}

void AppController::handleDisplayQueue()
{

}

void AppController::handleShowStatistics()
{

}