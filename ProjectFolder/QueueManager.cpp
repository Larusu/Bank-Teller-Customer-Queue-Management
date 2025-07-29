#include "QueueManager.h"

using namespace Utils;
using namespace std;

// ---------- Utility / Internal Helpers ----------
bool QueueManager::isVip(const string& name)
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

// ---------- Customer Creation & Lookup ----------
bool QueueManager::isInTheQueue(const string& bankId)
{
	queue<Customer>current = regularQueue;

	while(!current.empty())
	{
		Customer customer = current.front();
		current.pop();

		if(customer.bank.bankId == bankId)
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

Customer QueueManager::createCustomer(const string& name, int age, const string& transactionType, double balance, const string& bankID)
{
	Customer c;
	
	customerCounter++;
	c.name = nameFormatter(name);
	c.id = customerCounter;
	c.bank.bankId = bankID;
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

// ---------- Transactions ----------
void QueueManager::depositMoney(double amount, const string& bankId)
{
	// Change file balance
	updateCustomersBalance(amount, bankId, add);

	// Remove element on servedCustomer
	for (auto it = servedCustomers.begin(); it != servedCustomers.end(); ++it)
	{
		if (it->bank.bankId == bankId)
		{
			servedCustomers.erase(it);
			return;
		}
	}
}

void QueueManager::transferMoney(double amount, const std::string& senderId, const std::string& recipientId)
{
	// Change file balance
	updateCustomersBalance(amount, senderId, subtract);
	updateCustomersBalance(amount, recipientId, add);

	int senderIndex = -1;

	for (int i = 0; i < servedCustomers.size(); i++)
	{
		if (servedCustomers[i].bank.bankId == senderId)
		{
			senderIndex = i;
			break;
		}
	}

	// If recipient is in the queue, change their balance
	queue<Customer> tempQueue;
	while (!regularQueue.empty())
	{
		Customer c = regularQueue.front();
		regularQueue.pop();

		if (c.bank.bankId == recipientId && senderIndex != -1)
		{
			c.bank.balance += amount;
			cout << "New balance for recipient " << c.bank.balance + amount;
		}
		
		tempQueue.push(c);
	}

	regularQueue = tempQueue;

	// Remove element on servedCustomer
	servedCustomers.erase(servedCustomers.begin() + senderIndex);
}

void QueueManager::deductFromBalance(double amount, const string& bankId)
{
	updateCustomersBalance(amount, bankId, subtract);

	for(size_t i = 0; i < servedCustomers.size(); i++)
	{
		Customer c = servedCustomers[i];
		
		if(c.bank.bankId == bankId)
		{
			servedCustomers.erase(servedCustomers.begin() + i);
			return;
		}
	}
}

void QueueManager::updateCustomersBalance(double balance, const string& bankId, double (*op)(double, double))
{
	ifstream readFile("RegisteredCustomers.txt");
	vector<string> storingPerLine;
	string line;

	// Read all lines
	while(getline(readFile, line))
	{
		stringstream ss(line);
		string storedBankId;
		
		getline(ss, storedBankId, '|');
		
		// Modify the target line per current customer
		if(storedBankId == bankId)
		{
			string storedName, strAge, strBalance;
			double storedBalance;

			getline(ss, storedName, '|');
			getline(ss, strAge, '|');
			getline(ss, strBalance, '|');
			
			storedBalance = stod(strBalance);

			double newBalance = useOperator(storedBalance, balance, op);

			stringstream updatedLine;
			updatedLine << storedBankId << "|" << storedName << "|" << strAge << "|" << fixed << setprecision(2) << newBalance;
			storingPerLine.push_back(updatedLine.str());
		}
		// Keep original line
		else
		{
			storingPerLine.push_back(line);
		}
	}
	readFile.close();

	// Write back to the file
	ofstream fileWrite("RegisteredCustomers.txt");

	for(const string& updatedLine : storingPerLine)
	{
		fileWrite << updatedLine << endl;
	}
	fileWrite.close();
}

double QueueManager::add(double x, double y)
{
	return x + y;
}

double QueueManager::subtract(double x, double y)
{
	return x - y;
}

double QueueManager::useOperator(double a, double b, double (*func)(double, double)) 
{
    return func(a, b);
}