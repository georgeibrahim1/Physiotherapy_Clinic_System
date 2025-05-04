#include "X_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool X_Treatment::CanAssign(Scheduler* s)
{
	return s->CanAssign_X();
}

bool X_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_X(currPatient);
}