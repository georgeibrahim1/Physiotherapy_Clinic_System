#pragma once
#include "Treatment.h"

class U_Treatment : public Treatment
{
public:
	bool CanAssign()
	{
		return true;
	}

	bool MoveToWait()
	{
		return true;
	}
};