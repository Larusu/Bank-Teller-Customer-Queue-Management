#include "QueueManager.h"

using namespace std;

Customer QueueManager::createCustomer(const std::string& name, int age, const std::string& transactionType)
{
	Customer c;
	c.id = customerCounter++;
	c.name = name;
	c.age = age;
	c.transactionType = transactionType;
	c.estimatedServiceTime = Utils::estimateServiceTime(transactionType);
	c.arrivalOrder = regularQueue.size();
	c.priorityLevel = (c.age >= 60);
	return c;
}

void QueueManager::addCustomer(const Customer& customer)
{
	if (customer.priorityLevel)
	{
		queue<Customer> temp;
		
		while (!regularQueue.empty())
		{
			Customer c = regularQueue.front();
			if (c.priorityLevel) break;

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
	regularQueue.push(customer);
}

Customer QueueManager::serveCustomer()
{

}

void QueueManager::displayQueue()
{

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