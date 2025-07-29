#include "QueueManager.h"

using namespace Utils;
using namespace std;

// ---------- Utility / Internal Helpers ----------
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

string QueueManager::generateBankId()
{
	string code = generateCode(3) + "-" + generateCode(3);
	if (regularQueue.empty())
	{
		return code;
	}
	queue<Customer> temp = regularQueue;
	
	while (!temp.empty())
	{
		Customer c = temp.front();
		temp.pop();
		
		if (c.bank.bankId == code)
		{
			code = generateCode(3) + "-" + generateCode(3);
		}
	}

	return code;
}

string QueueManager::generateCode(int length)
{
	string RandomCode = "";

	while (RandomCode.length() < length)
	{
		char random = (rand() % 10) + '0';
		RandomCode += random;
	}
	return RandomCode;
}

// ---------- Customer Creation & Lookup ----------
bool QueueManager::isExistingName(const std::string& name)
{
	// check served customers
	for (int i = 0; i < servedCustomers.size(); i++)
	{
		if (toUpper(servedCustomers[i].name) == trim(toUpper(name)))
		{
			return true;
		}
	}

	// if none in served customer
	queue<Customer>tempQueue = regularQueue;
	while (!tempQueue.empty())
	{
		Customer c = tempQueue.front();
		tempQueue.pop();

		if (toUpper(c.name) == trim(toUpper(name)))
		{
			return true;
		}
	}
	return false;
}

Customer QueueManager::createCustomer(const string& name, int age, const string& transactionType, double balance)
{

	Customer c;
	
	customerCounter++;
	c.name = nameFormatter(name);
	c.id = customerCounter;
	c.bank.bankId = generateBankId();
	c.age = age;
	c.bank.balance = balance;
	c.transactionType = transactionType;
	c.estimatedServiceTime = estimateServiceTime(transactionType);
	c.arrivalOrder = regularQueue.size();

	if (isVip(name)) { c.priorityLevel = 2; }
	else if (c.age >= 60) { c.priorityLevel = 1; }
	else { c.priorityLevel = 0; }

	return c;
}

// ---------- Queue Management ----------
void QueueManager::addCustomer(const Customer& newCustomer)
{
	queue<Customer> newQueue;
	bool inserted = false;

	while (!regularQueue.empty())
	{
		Customer current = regularQueue.front();
		regularQueue.pop();

		// Insert before the first customer with lower priority
		if (!inserted && newCustomer.priorityLevel > current.priorityLevel)
		{
			newQueue.push(newCustomer);
			inserted = true;
		}

		newQueue.push(current);
	}

	// If not inserted (i.e., queue is empty or newCustomer has lowest priority), add at the end
	if (!inserted)
	{
		newQueue.push(newCustomer);
	}

	// Replace the original queue
	regularQueue = newQueue;

	// Track peak queue length
	if (regularQueue.size() > peakQueueLength) {
		peakQueueLength = regularQueue.size();
	}
}


Customer QueueManager::serveCustomer()
{
	if (!regularQueue.empty())
	{
		Customer front = regularQueue.front();
		servedCustomers.push_back(front);
		regularQueue.pop();
		return front;
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

	while (!tempQueue.empty())
	{
		Customer c = tempQueue.front();
		cout << "║  " << left << setw(4) << c.id << "║ " << left << setw(29) << c.name << "║  " << left << setw(5) << c.age << "║ " << left << setw(14) << c.transactionType << "║ " << c.estimatedServiceTime << " mins  ║" << endl;
		if(tempQueue.size() == 1) break;
		cout << "╠══════╬══════════════════════════════╬═══════╬═══════════════╬═════════╣" << endl;
		tempQueue.pop();
	}
}

bool QueueManager::hasCustomers()
{
	return !regularQueue.empty();
}

int QueueManager::getCurrentQueueLength()
{
	return regularQueue.size();
}

int QueueManager::getPeakQueueLength(int currentQueueLength)
{
	return peakQueueLength;
}

Customer QueueManager::getFront()
{
	return regularQueue.front();
}

// ---------- Transactions ----------
void QueueManager::depositMoney(double deposit, const string& bankId)
{
	for (Customer& c : servedCustomers)
	{
		if (c.bank.bankId == bankId)
		{
			c.bank.balance += deposit;
			return;
		}
	}
}

void QueueManager::transferMoney(double amount, const std::string& senderId, const std::string& recipientId)
{
	int senderIndex = -1;

	for (int i = 0; i < servedCustomers.size(); i++)
	{
		if (servedCustomers[i].bank.bankId == senderId)
		{
			senderIndex = i;
			break;
		}
	}

	if (senderIndex == -1) { cout << "Invalid sender id! "; return; }

	// Transfer if recipient is in servedCustomers
	for (int i = 0; i < servedCustomers.size(); i++)
	{
		if (servedCustomers[i].bank.bankId == recipientId && senderIndex != -1)
		{
			servedCustomers[senderIndex].bank.balance -= amount;
			servedCustomers[i].bank.balance += amount;
			return;
		}
	}

	// If not found in servedCustomers, search in regularQueue and rebuild it
	queue<Customer> tempQueue;
	while (!regularQueue.empty())
	{
		Customer c = regularQueue.front();
		regularQueue.pop();

		if (c.bank.bankId == recipientId && senderIndex != -1)
		{
			servedCustomers[senderIndex].bank.balance -= amount;
			c.bank.balance += amount;
		}

		tempQueue.push(c);
	}

	regularQueue = tempQueue;
}

void QueueManager::deductFromBalance(double amount, const string& bankId)
{
	for (Customer& c : servedCustomers)
	{
		if (c.bank.bankId == bankId)
		{
			c.bank.balance -= amount;
			return;
		}
	}
}

// ---------- Statistics & Accessors ----------
int QueueManager::getLastServiceTime()
{
	if (!regularQueue.empty())
		return regularQueue.front().estimatedServiceTime;
	return 0;
}

const vector<Customer>& QueueManager::getServedCustomers()
{
	return servedCustomers;
}

const queue<Customer>& QueueManager::getPendingCustomers()
{
	return regularQueue;
}

void QueueManager::isServed(const Customer& customer)
{
	// Check if the customer is in the served list
	for(int i = 0; i < servedCustomers.size(); i++)
	{
		if (servedCustomers[i].id == customer.id)
		{
			// If found, remove them from the served list
			servedCustomers.erase(servedCustomers.begin() + i);
			return;
		}
	}
}