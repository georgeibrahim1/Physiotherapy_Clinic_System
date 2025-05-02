#pragma once
#include "Treatment.h"

class Scheduler;
class Patient;

class U_Treatment : public Treatment
{
public:
	virtual bool CanAssign();
	virtual bool MoveToWait(Scheduler* schedular, Patient* currPatient);
};