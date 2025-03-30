#pragma once
#include "priQueue.h"

template <typename T>
class priQueue_Reschedulling : public priQueue<T>
{
public:
	priQueue_Reschedulling() {}

	~priQueue_Reschedulling() {}

	bool reschedule(const T& data, int newPriority)
	{
		if (isEmpty()) // No Nodes
		{
			return false;
		}

		// If the head is the node to be rescheduled (Suitable also if there is only one node in the priqueue) 
		//REMEMBER: the new priority should be higher and this must be checked in the Scheduler Class 
		if (head->getItem() == data)
		{
			head->Pri = newPriority;
			return true;
		}

		// remove this node from the priority queue and store it in a temporary node
		priNode<T>* current = head->getNext();
		priNode<T>* prev = head;
		priNode<T>* temp = nullptr;

		while (current)
		{
			if (current->getItem() == data)
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
			temp->pri = newPriority;
			enqueue(temp->getItem(), temp->getPri());
			delete temp; //Memory save :)
			return true
		}
		else
		{
			return false;
		}
	}
};

