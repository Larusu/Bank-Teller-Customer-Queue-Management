#include "QueueManager.h"

using namespace Utils;
using namespace std;

Customer QueueManager::createCustomer(const std::string& name, int age, const std::string& transactionType)
{
	Customer c;
	c.id = customerCounter++;
	c.name = name;
	c.age = age;
	c.transactionType = transactionType;
	c.estimatedServiceTime = estimateServiceTime(transactionType);
	c.arrivalOrder = regularQueue.size();

	if (c.age >= 60)
		c.priorityLevel = 1;
	else if (isVip(name))
		c.priorityLevel = 2;
	else
		c.priorityLevel = 0;

	return c;
}

void QueueManager::addCustomer(const Customer& customer)
{
	// If customer has a priority level (1 = Senior Citizen, 2 = VIP)
	if (customer.priorityLevel > 0)
	{
		queue<Customer> temp;
		
		while (!regularQueue.empty())
		{
			Customer c = regularQueue.front();

			/* Priority Rules:
                - VIP (2) has the highest priority: placed in front of everyone.
                - Senior Citizen (1) is placed after all VIPs, but before regular customers and other seniors.
                - Regular customers (0) are always placed at the back. */
			if (c.priorityLevel <= 2 && customer.priorityLevel == 1) break;
			if (c.priorityLevel == 2 && customer.priorityLevel == 2) break;

			temp.push(c);
			regularQueue.pop();
		}
		
		regularQueue.push(customer);
		
		while (!temp.empty())
		{
			regularQueue.push(temp.front());
			temp.pop();
		}
		return;
	}
	// Regular customers are added to the end of the queue
	regularQueue.push(customer);
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

	cout << "|  ID  |             Name             |  Age  |  Transaction  |" << endl;
	while (!tempQueue.empty())
	{
		Customer c = tempQueue.front();
		cout << "|  " << c.id << "  |   " << c.name << "   |   " << c.age << "  |  " << c.transactionType << "  |" << endl;
		tempQueue.pop();
	}
}

bool QueueManager::hasCustomers()
{

}

int QueueManager::getCurrentQueueLength()
{

}

int QueueManager::getPeakQueueLength()
{

}

int QueueManager::getLastServiceTime()
{

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