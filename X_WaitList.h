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

		if (LinkedQueue <Patient*> ::isEmpty())
			return false;

		int to_cancel = rand() % this->getcount();
		//loop to search for the patient to remove
		//delete this node then connect previous node to next
		//make a temp pointer to that node and enqueue it to finish list


		Node<Patient*>* curr = this->frontPtr;
		Node<Patient*>* prev = nullptr;



		for (int j = 0; j < to_cancel; j++)
		{
			prev = curr;
			curr = curr->getNext();

		}

		Treatment* x;
		curr->getItem()->Get_reqtreatmentlist().peek(x);
		if (curr->getItem()->Get_reqtreatmentlistcount() == 1 && x->get_type() == 'X')   // If the count of remaining treatments is one, then X_exercise is the last treatment for sure.
		{
			if (curr == prev) // Single Node
			{
				this->frontPtr = nullptr;
				this->backPtr = nullptr;
			}
			else if (curr == this->frontPtr) // Front Node
				this->frontPtr = curr->getNext();
			else if (curr == this->backPtr) // Back Node
			{
				this->backPtr = prev;
				prev->setNext(nullptr);
			}
			else
				prev->setNext(curr->getNext()); // General case

			to_delete = curr->getItem();
			count--;
			curr->setNext(nullptr);
			delete curr;
			return true;
		}
	}
	return false;
	//After deleting the patient, he should be moved to the finish list(push(dataentry))
	// after deleting, you should decrment count


}