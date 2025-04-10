#pragma once
#include "Resource.h"

class Treatment
{
protected:
	int Duration; // The amount of time(timesteps) the treatment takes
	int AssignmentTime; //the time at which this treatment was assigned to a resource
	Resource* AssignedResource;
public:
	Treatment()
	{

	}

	virtual bool CanAssign() {};

	virtual bool MoveToWait() {};

	int GetDuration()
	{
		return Duration;
	}
};

