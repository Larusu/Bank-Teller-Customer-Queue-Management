#include "QueueManager.h"

using namespace Utils;
using namespace std;

Customer QueueManager::createCustomer(const std::string& name, int age, const std::string& transactionType)
{
	Customer c;
	customerCounter++;
	c.id = customerCounter;
	c.name = nameFormatter(name);
	c.age = age;
	c.transactionType = transactionType;
	c.estimatedServiceTime = estimateServiceTime(transactionType);
	c.arrivalOrder = regularQueue.size();

	if (c.age >= 60) { c.priorityLevel = 1; }
	else if (isVip(name)) { c.priorityLevel = 2; }
	else { c.priorityLevel = 0; }

	return c;
}

void QueueManager::addCustomer(const Customer& newCustomer)
{
	// If customer has a priority level (1 = Senior Citizen, 2 = VIP)
	if (newCustomer.priorityLevel > 0)
	{
		queue<Customer> temp;
		
		while (!regularQueue.empty())
		{
			Customer c = regularQueue.front();

			/* Priority Rules:
                - VIP (2) has the highest priority: placed in front of everyone.
                - Senior Citizen (1) is placed after all VIPs, but before regular customers and other seniors.
                - Regular customers (0) are always placed at the back. */
			if (c.priorityLevel > newCustomer.priorityLevel) break;
			
			temp.push(c);
			regularQueue.pop();
		}
		
		regularQueue.push(newCustomer);

		while (!temp.empty())
		{
			regularQueue.push(temp.front());
			temp.pop();
		}

		// Set peak queue length
		if (regularQueue.size() > peakQueueLength) {
			peakQueueLength = regularQueue.size();
		} 
		return;
	}
	// Regular customers are added to the end of the queue
	regularQueue.push(newCustomer);

	// Set peak queue length
	if (regularQueue.size() >= peakQueueLength) {
		peakQueueLength = regularQueue.size();
	} 
}

Customer QueueManager::serveCustomer()
{
	if (!regularQueue.empty())
	{
		Customer c = regularQueue.front();
		regularQueue.pop();
		return c;
	}
	return Customer(); // return default if empty
}

void QueueManager::displayQueue()
{
	queue<Customer> tempQueue = regularQueue;
	if (regularQueue.empty())
	{
		cout << "Queue is empty. Insert a customer first." << endl;
		return;
	}
	
	cout << "╔══════════════════════════ CURRENT QUEUE ══════════════════════════════╗" << endl;
	cout << "╠══════╦══════════════════════════════╦═══════╦═══════════════╦═════════╣" << endl;
	cout << "║  ID  ║             Name             ║  Age  ║  Transaction  ║   ETA   ║" << endl;
	cout << "╠══════╬══════════════════════════════╬═══════╬═══════════════╬═════════╣" << endl;

	while (!tempQueue.empty())
	{
		Customer c = tempQueue.front();
		cout << "║  " << left << setw(4) << c.id << "║ " << left << setw(29) << c.name << "║  " << left << setw(5) << c.age << "║ " << left << setw(14) << c.transactionType << "║ " << c.estimatedServiceTime << " mins  ║" << endl;
		if(tempQueue.size() == 1) break;
		cout << "╠══════╬══════════════════════════════╬═══════╬═══════════════╬═════════╣" << endl;
		tempQueue.pop();
	}
	cout << "╚══════╩══════════════════════════════╩═══════╩═══════════════╩═════════╝\n";
}

bool QueueManager::hasCustomers()
{
	return regularQueue.empty();
}

int QueueManager::getCurrentQueueLength()
{
	return regularQueue.size();
}

int QueueManager::getPeakQueueLength(int currentQueueLength)
{
	return peakQueueLength;
}

int QueueManager::getLastServiceTime()
{
	if (!regularQueue.empty())
		return regularQueue.front().estimatedServiceTime;
	return 0;
}

bool QueueManager::isVip(const std::string& name)
{
	ifstream vipFile;
	string line;

	vipFile.open("vip_names.txt");
	while (getline(vipFile, line))
	{
		if (toUpper(trim(name)) == line)
		{
			return true;
		}
	}
	return false;
}

string QueueManager::nameFormatter(const string& name)
{
	string newName;
	bool firstLetter = true;

	for (char n : trim(name))
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