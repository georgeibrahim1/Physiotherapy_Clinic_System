#include "X_TreatmentB.h"
#include "Scheduler.h"
#include "Patient.h"

bool X_TreatmentB::CanAssign(Scheduler* s)
{
	return s->CanAssign_X();
}

bool X_TreatmentB::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_XB(currPatient);
}