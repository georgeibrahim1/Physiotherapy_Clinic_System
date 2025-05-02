#include "U_Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

bool U_Treatment::CanAssign()
{
	if (!AssignedResource)
	{
		return true;
	}
	else
		return false;
}

bool U_Treatment::MoveToWait(Scheduler* schedular, Patient* currPatient)
{
	return schedular->MoveToWait_U(currPatient);
}