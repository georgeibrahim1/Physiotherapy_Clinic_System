#pragma once
#include "X_Treatment.h"

class Scheduler;
class Patient;

class X_TreatmentC : public X_Treatment
{
public:
	virtual bool CanAssign(Scheduler* s);

	virtual bool MoveToWait(Scheduler* schedular, Patient* currPatient);
};
