#pragma once
#include "priQueue.h"


//TODO : Delete the template shit -> replace by patient
//Don't forget to edit them in Schedular.h
template <typename T>
class EarlyPList : public priQueue<T>
{
public:
	EarlyPList() {}

	~EarlyPList() {}

	bool reschedule(const T& data, int newPriority)
	{
		priNode<T>* Phead = head;
		if (isEmpty()) // No Nodes
		{
			return false;
		}

		// If the Phead is the node to be rescheduled (Suitable also if there is only one node in the priqueue) 
		//REMEMBER: the new priority should be higher and this must be checked in the Scheduler Class 
		if (Phead->getItem() == data)
		{
			Phead->Pri = newPriority;
			return true;
		}

		// remove this node from the priority queue and store it in a temporary node
		priNode<T>* current = this->Phead->getNext();
		priNode<T>* prev = this->Phead;
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
			return true;
		}
		else
		{
			return false;
		}
	}
};

