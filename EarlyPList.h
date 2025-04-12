#pragma once
#include "priQueue.h"


//TODO : Delete the template shit -> replace by patient
//Don't forget to edit them in Schedular.h

class EarlyPList : public priQueue<Patient*>
{
public:
	EarlyPList() {}

	~EarlyPList() {}

	bool reschedule(const Patient* data, int newPriority)//const Patient& data changed
	{
		priNode<Patient*>* Phead = head;
		if (isEmpty()) // No Nodes
		{
			return false;
		}

		// If the Phead is the node to be rescheduled (Suitable also if there is only one node in the priqueue) 
		//REMEMBER: the new priority should be higher and this must be checked in the Scheduler Class 
		int x;
		if (Phead->getItem(x) == data)
		{
			Phead->setItem(Phead->getItem(x), newPriority);
			return true;
		}

		// remove this node from the priority queue and store it in a temporary node
		priNode<Patient*>* current = Phead->getNext();
		priNode<Patient*>* prev = Phead;
		priNode<Patient*>* temp = nullptr;

		while (current)
		{
			if (current->getItem(x) == data)
			{
				prev->setNext(current->getNext());
				temp = current;
				temp->setNext(nullptr);
				break;
			}

			prev = current;
			current = current->getNext();
		}

		if (temp)
		{
			temp->setItem(temp->getItem(x), newPriority);
			enqueue(temp->getItem(x), temp->getPri());
			delete temp; //Memory save :)
			return true;
		}
		else
		{
			return false;
		}
	}
};

