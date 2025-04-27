#pragma once
#include "Treatment.h"
#include "Scheduler.h"
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