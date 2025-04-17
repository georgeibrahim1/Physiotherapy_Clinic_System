#pragma once
#include "Node.h"
#include "QueueADT.h"
#include "EU_WaitList.h"
#include "LinkedQueue.h"

class X_WaitList : public EU_WaitList
{
public:
	X_WaitList() {}

	bool cancel(Patient*& to_delete);

	~X_WaitList() {}
};

bool X_WaitList::cancel(Patient*& to_delete)
{

	for (int i = 0; i < (this->getcount() * 3); i++) // loop multiple times with different index
	{
		srand(time(0));
		int to_cancel = rand() % this->getcount();

		//loop to search for the patient to remove
		//delete this node then connect previous node to next
		//make a temp pointer to that node and enqueue it to finish list


		Node<Patient*>* curr = this->frontPtr;
		Node<Patient*>* prev = this->frontPtr;

		if (LinkedQueue <Patient*> ::isEmpty())
			return false;

		for (int j = 0; j < to_cancel; j++)
		{
			curr = curr->getNext();
		}
		for (int j = 0; j < to_cancel - 1; j++)
		{
			prev = prev->getNext();
		}


		if (curr->getItem()->Get_reqtreatmentlist().getcount() == 1) // If the count of remaining treatments is one, then X_exercise is the last treatment for sure.
		{
			if (!(prev == this->frontPtr))
				prev->setNext(curr->getNext());
			else
				this->frontPtr = curr->getNext();
			to_delete = curr->getItem();
			this->setcount(-1);
			delete curr;
			return true;
		}
	}
	return false;
	//After deleting the patient, he should be moved to the finish list(push(dataentry))
	// after deleting, you should decrment count


}