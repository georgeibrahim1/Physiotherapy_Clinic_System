#pragma once
#include "EU_WaitList.h"
#include "LinkedQueue.h"
#include <fstream>
#include <conio.h>
#include <random>

class X_WaitList : public EU_WaitList
{
public:
	X_WaitList() {}

	bool cancel(Patient*& to_delete)
	{
		if (LinkedQueue <Patient*> ::isEmpty())
			return false;

		int to_cancel = generateRandomNumber(0, this->getcount());

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
		return false;
		//After deleting the patient, he should be moved to the finish list(push(dataentry))
		// after deleting, you should decrment count
	}

	~X_WaitList() {}

	int generateRandomNumber(int min, int max, unsigned int seed = 42)
	{
		static std::mt19937 engine(seed); // Mersenne Twister engine with fixed seed
		std::uniform_int_distribution<int> dist(min, max);
		return dist(engine);
	}

};



