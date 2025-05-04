#include "U_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool U_Treatment::CanAssign(Scheduler* s)
{
	return s->CanAssign_U();
}

bool U_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_U(currPatient);
}