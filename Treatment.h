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
		Duration = 0;
		AssignmentTime = 0;
		AssignedResource = nullptr;
	}

	virtual bool CanAssign() { return 0; };// to be edited

	virtual bool MoveToWait() { return 0; }; // to be edited

	int GetDuration()
	{
		return Duration;
	}

	void Set_Duration(int t)
	{
		Duration = t;
	}
};

