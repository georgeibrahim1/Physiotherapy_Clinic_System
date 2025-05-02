#pragma once
#include "priQueue.h"
#include <fstream>
#include <conio.h>
#include <random>
#include "Patient.h"


class EarlyPList : public priQueue<Patient*>
{
public:

	EarlyPList();

	~EarlyPList();

	bool reschedule();

	int generateRandomNumber(int min, int max, unsigned int seed = 42);

};

