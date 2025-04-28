#pragma once
#include "Treatment.h"

class U_Treatment : public Treatment
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