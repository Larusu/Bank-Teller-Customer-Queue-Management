#include "Statistics.h"

using namespace Utils;
using namespace std;

void Statistics::recordService(int serviceTime)
{
	totalCustomersServed++;
	totalServiceTime += serviceTime;

	switch (serviceTime)
	{
	case 6: totalCustomerTransfer++; break;
	case 5: totalCustomerWithdraw++; break;
	case 4: totalCustomerPayment++; break;
	case 3: totalCustomerDeposit++; break;
	case 2: totalCustomerAccount++; break;
	}
}

void Statistics::displayStatistics(int peakQueueLength)
{
	clearScreen();

	int peak = peakQueueLength;
	int notYetServe = totalCustomersServed - totalServed;

	cout << fixed << setprecision(2);

	cout << "╔══════════════════════════════════════════════════════╗" << "\n";
	cout << "║                   Customer Report                    ║" << "\n";                                                                        
	cout << "╠══════════╦═══════════╦═══════════╦═══════════════════╣" << "\n";
	cout << "║ Overall  ║ Completed ║  Pending  ║ Peak Queue Length ║" << "\n";
	cout << "╠══════════╬═══════════╬═══════════╬═══════════════════╣" << "\n";
	cout << "║    " << left << setw(6) << totalCustomersServed << "║    " << setw(7) 
	<< totalServed << "║    " << setw(7) << notYetServe << "║        " << setw(11) << peak << "║" << "\n";
	cout << "╚══════════╩═══════════╩═══════════╩═══════════════════╝" << "\n\n";
	cout << "╔═══════════════════════════════════════════════════╗" << "\n";
	cout << "║                 No of Transactions                ║" << "\n";                                                              
	cout << "╠══════════╦══════════╦═════════╦═════════╦═════════╣" << "\n";	
	cout << "║ Transfer ║ Withdraw ║ Payment ║ Deposit ║ Account ║" << "\n";
	cout << "╠══════════╬══════════╬═════════╬═════════╬═════════╣" << "\n";
	cout << "║    " << setw(6) << totalCustomerTransfer << "║    " << setw(6) << totalCustomerWithdraw << "║   " 
	<< setw(6) << totalCustomerPayment << "║   " << setw(6) << totalCustomerDeposit << "║   " << setw(6) 
	<< totalCustomerAccount << "║" << "\n";
	cout << "╚══════════╩══════════╩═════════╩═════════╩═════════╝" << "\n\n";

	cout << "╔═══════════════════════════════════════════════════╗" << "\n";
	cout << "║                Average Waiting Time               ║" << "\n";
	cout << "╠══════════╦══════════╦═════════╦═════════╦═════════╣" << "\n";
	cout << "║ Transfer ║ Withdraw ║ Payment ║ Deposit ║ Account ║" << "\n";
	cout << "╠══════════╬══════════╬═════════╬═════════╬═════════╣" << "\n";
	cout << "║  6 mins  ║  5 mins  ║ 4 mins  ║ 3 mins  ║ 2 mins  ║" << "\n";
	cout << "╚══════════╩══════════╩═════════╩═════════╩═════════╝" << "\n\n";
}

double Statistics::getAverageServiceTime()
{
	double average = (double)totalServiceTime / totalCustomersServed;
	return round(average * 100.0) / 100.0;
}

int Statistics::getTotalCustomersServed()
{
	return totalCustomersServed;
}

void Statistics::setTotalServed()
{
	totalServed++;
}