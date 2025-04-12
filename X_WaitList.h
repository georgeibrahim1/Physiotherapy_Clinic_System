#pragma once
#include "Node.h"
#include "QueueADT.h"
#include "EU_WaitList.h"
#include "LinkedQueue.h"

class X_WaitList : public EU_WaitList <Patient*>
{
public:
	X_WaitList() {}

	bool cancel(const Patient* to_delete);

	~X_WaitList() {}
};

bool X_WaitList ::cancel(const Patient* to_delete)
{
	//test
	//loop to search for the patient to remove
	//delete this node then connect previous node to next
	//make a temp pointer to that node and enqueue it to finish list
	Node<Patient*>* curr = this->frontPtr;
	Node<Patient*>* prev = this->frontPtr;
	Node<Patient*>* chosen = nullptr;
	if (LinkedQueue <Patient*> ::isEmpty())
		return false;
	// corner case : first node is the one to cancel
	if (curr->getItem() == to_delete)
	{
		if (!(curr->getNext()))
		{
			chosen = curr;
			curr = nullptr;
			prev = nullptr;
			this->frontPtr = nullptr;
			return true;
		}
		else
		{
			chosen = curr;
			curr = curr->getNext();
			this->frontPtr = curr;
			prev = curr;
			return true;
		}
	}
	// move current pointer forward
	curr = curr->getNext();
	while (curr)
	{
		if (curr->getItem() == to_delete)
		{
			chosen = curr;
			curr = curr->getNext();
			prev->setNext(curr);
			chosen->setNext(nullptr);
			return true;
		}
		else
		{
			prev = prev->getNext();
			curr = curr->getNext();
		}
	}
	//After deleting the patient, he should be moved to the finish list(push(dataentry))
}