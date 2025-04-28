#pragma once
#include "Treatment.h"
#include "Scheduler.h"
class E_Treatment : public Treatment 
{
public:
	bool CanAssign()
	{
		if (!AssignedResource)
		{
			return true;
		}
		else
			return false;
	}

	bool MoveToWait()
	{
		return true;
	}
};