#include "X_TreatmentA.h"
#include "Scheduler.h"
#include "Patient.h"

bool X_TreatmentA::CanAssign(Scheduler* s)
{
	return s->CanAssign_X();
}

bool X_TreatmentA::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_XA(currPatient);
}