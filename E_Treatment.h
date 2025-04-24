#pragma once
#include "Treatment.h"

class E_Treatment : public Treatment 
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