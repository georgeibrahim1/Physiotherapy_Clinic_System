#include "X_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool X_Treatment::CanAssign()
{
	if (!AssignedResource)
	{
		return true;
	}
	else
		return false;
}

bool X_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_X(currPatient);
}