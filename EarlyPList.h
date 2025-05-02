#pragma once
#include "priQueue.h"
#include "Patient.h"
#include <fstream>
#include <conio.h>
#include <random>

class EarlyPList : public priQueue<Patient*>
{
public:

	EarlyPList();

	~EarlyPList();

	bool reschedule();

	int generateRandomNumber(int min, int max, unsigned int seed = 42);

};

