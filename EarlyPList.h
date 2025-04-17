#pragma once
#include "priQueue.h"


//TODO : Delete the template shit -> replace by patient
//Don't forget to edit them in Schedular.h

class EarlyPList : public priQueue<Patient*>
{
public:
	EarlyPList() {}

	~EarlyPList() {}

	bool reschedule(int newPriority)
	{
		for (int i = 0; i < (this->getcount() * 3); i++) // loop multiple times with different index
		{
			if (isEmpty()) return false;

			std::srand(std::time(nullptr));

			int randomIndex = std::rand() % count;

			priNode<Patient*>* current = head;
			priNode<Patient*>* prev = nullptr;
			for (int i = 0; i < randomIndex; ++i) {
				prev = current;
				current = current->getNext();
			}

			int oldPriority;
			Patient* patient = current->getItem(oldPriority);

			if (newPriority < oldPriority)
			{
				if (prev)
					prev->setNext(current->getNext());
				else
					head = current->getNext(); // it was head

				current->setNext(nullptr);
				count--;


				current->setItem(patient, newPriority);
				enqueue(patient, newPriority);

				delete current;

				return true;
			}
			else
			{
				return false;
			}

		}
   	}
};

