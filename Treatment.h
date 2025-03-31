#pragma once
class Treatment
{
protected:
	int Duration; // The amount of time(timesteps) the treatment takes
	int AssignmentTime; //the time at which this treatment was assigned to a resource
	Resource* AssignedResource;
public:
	virtual bool CanAssign()
	{ }
	int GetDuration()
	{
		return Duration;
	}
};

