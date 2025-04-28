#pragma once
#include "priQueue.h"
#include <fstream>
#include <conio.h>
#include <random>

class EarlyPList : public priQueue<Patient*>
{
public:
	EarlyPList() {}

	~EarlyPList() {}

	bool reschedule(int newPriority)
	{
			if (isEmpty()) return false;

			int randomIndex = generateRandomNumber(0, this->getcount() - 1);

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

				return true;
			}
			else
			{
				return false;
			}
   	}

	int generateRandomNumber(int min, int max, unsigned int seed = 42)
	{
		static std::mt19937 engine(seed); // Mersenne Twister engine with fixed seed
		std::uniform_int_distribution<int> dist(min, max);
		return dist(engine);
	}

};

