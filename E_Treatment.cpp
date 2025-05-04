#include "E_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"
#include "Scheduler.h"

bool E_Treatment::CanAssign(Scheduler* s, Resource*& e)
{
	return s->CanAssign_E(e);
}

bool E_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_E(currPatient);
}