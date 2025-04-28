#pragma once
#include "Treatment.h"


class X_Treatment : public Treatment
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