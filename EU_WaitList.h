#pragma once
#include "Patient.h"

class EU_WaitList : public LinkedQueue<Patient*>
{
protected:
	int TreatmentLatency;
public:

	EU_WaitList();
	~EU_WaitList();
	bool enqueue(Patient*& newEntry);
	bool dequeue(Patient*& frntEntry);
	bool peek(Patient*& frntEntry) const;
	bool InsertSorted(Patient*& newEntry, int SortingValue);
	int GetTreatmentLatency();

};

