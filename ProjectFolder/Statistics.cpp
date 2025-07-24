#include "Statistics.h"

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
	// BASAHIN MO TO ::: lagay ka peak queue length
	int notYetServe = totalCustomersServed - totalServed;
	// Display overall number of Customer, served customer, not yet serve customer, average waiting time of all transactiosn
						   // Number of customer per types of transactions, average waiting time per type of transaction
	cout << fixed << setprecision(2);
	cout << "╔══════════════════════════════════╗" << "\n";
	cout << "║         Customer Report          ║" << "\n";                                                                        
	cout << "╠══════════╦═══════════╦═══════════╣" << "\n";
	cout << "║ Overall  ║  Served   ║  Pending  ║" << "\n";
	cout << "╠══════════╬═══════════╬═══════════╣" << "\n";
	cout << "║    " << left << setw(6) << totalCustomersServed << "║    " << setw(7) << totalServed << "║    " << setw(7) << notYetServe << getAverageServiceTime << "║" << "\n";
	
	cout << "╔═══════════════════════════════════════════════════╗" << "\n";
	cout << "║               Average Waiting Time                ║" << "\n";                                                              
	cout << "╠══════════╦══════════╦═════════╦═════════╦═════════╣" << "\n";	
	cout << "║ Transfer ║ Withdraw ║ Payment ║ Deposit ║ Account ║" << "\n";
	cout << "╠══════════╬══════════╬═════════╬═════════╬═════════╣" << "\n";
	cout << totalCustomersServed << "|" << totalServed << "|" << notYetServe << getAverageServiceTime();
	cout << "Overall customer's type of transcation      | Overall customer's waiting time per transaction" << endl;
	cout << "Transfer|Withdraw|Payment|Deposit|Account   | Transfer|Withdraw|Payment|Deposit|Account" << endl;
	cout << totalCustomerTransfer << " " << totalCustomerWithdraw << " " << totalCustomerPayment << " " << totalCustomerDeposit << " " << totalCustomerAccount << " ";
	cout << 6 << " " << 5 << " " << 4 << " " << 3 << " " << 2;
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