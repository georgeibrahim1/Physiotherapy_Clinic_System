#pragma once
#include "priQueue.h"
#include <fstream>
#include <conio.h>
#include <random>
#include "EarlyPList.h"


EarlyPList::EarlyPList() {}

EarlyPList::~EarlyPList() {}

bool EarlyPList::reschedule()
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

	if (patient)
		if (patient->GetDidReschedule() == 3)
			return false;

	int newPriority = -(patient->getPT() + generateRandomNumber(1, 100));

	if (newPriority < oldPriority)
	{
		if (prev)
			prev->setNext(current->getNext());
		else
			head = current->getNext(); // it was head

		current->setNext(nullptr);
		count--;


		current->setItem(patient, newPriority);


		patient->Set_PT(-newPriority); // newpriority equals -newPT
		enqueue(patient, newPriority);

		patient->IncDidReschedule(1);
		return true;
	}
	else
	{
		return false;
	}
}

int EarlyPList::generateRandomNumber(int min, int max, unsigned int seed)
{
	static std::mt19937 engine(seed); // Mersenne Twister engine with fixed seed
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

