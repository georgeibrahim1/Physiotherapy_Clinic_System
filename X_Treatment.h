#pragma once
#include "Treatment.h"

class X_Treatment : public Treatment
{
public:
	bool CanAssign()
	{
		if (AssignedResource->Get_Availability() == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool MoveToWait()
	{

	}
};