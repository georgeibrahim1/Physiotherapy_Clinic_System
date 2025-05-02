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

	bool cancel(Patient*& to_delete);

	~X_WaitList() {}

	int generateRandomNumber(int min, int max, unsigned int seed = 42);

};



