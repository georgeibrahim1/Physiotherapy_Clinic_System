#pragma once
#include "Node.h"
#include "QueueADT.h"
#include "EU_WaitList.h"
#include "LinkedQueue.h"
template <typename T>
class X_WaitList : public EU_WaitList <T>
{
public:
	X_WaitList() {}

	bool cancel(const T& to_delete);

	~X_WaitList() {}
};
template <typename T>
bool X_WaitList<T>::cancel(const T& to_delete)
{
	//test
	//loop to search for the patient to remove
	//delete this node then connect previous node to next
	//make a temp pointer to that node and enqueue it to finish list
	Node<T>* curr = this->frontPtr;
	Node<T>* prev = this->frontPtr;
	Node<T>* chosen = nullptr;
	if (LinkedQueue <T> ::isEmpty())
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