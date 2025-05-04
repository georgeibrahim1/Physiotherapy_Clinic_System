#include "E_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool E_Treatment::CanAssign(Scheduler* s)
{
	return s->CanAssign_E();
}

bool E_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_E(currPatient);
}