#pragma once
#include "Treatment.h"

class E_Treatment : public Treatment 
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