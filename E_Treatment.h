#pragma once
#include "Treatment.h"

class Scheduler;
class Patient;

class E_Treatment : public Treatment 
{
public:
	virtual bool CanAssign(Scheduler* s);

	virtual bool MoveToWait(Scheduler* schedular, Patient* currPatient);
};