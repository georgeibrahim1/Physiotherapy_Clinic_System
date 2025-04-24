#pragma once
#include "Treatment.h"


class X_Treatment : public Treatment
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