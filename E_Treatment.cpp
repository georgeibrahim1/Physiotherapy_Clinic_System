#include "E_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool E_Treatment::CanAssign()
{
	if (!AssignedResource)
	{
		return true;
	}
	else
		return false;
}

bool E_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_E(currPatient);
}