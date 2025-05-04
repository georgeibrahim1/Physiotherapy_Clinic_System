#include "X_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool X_Treatment::CanAssign(Scheduler* s, X_Resource*& x)
{
	return s->CanAssign_X(x);
}

bool X_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_X(currPatient);
}