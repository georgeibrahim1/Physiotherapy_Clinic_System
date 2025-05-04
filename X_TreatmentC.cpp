#include "X_TreatmentC.h"
#include "Scheduler.h"
#include "Patient.h"

bool X_TreatmentC::CanAssign(Scheduler* s)
{
	return s->CanAssign_X();
}

bool X_TreatmentC::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_XC(currPatient);
}
