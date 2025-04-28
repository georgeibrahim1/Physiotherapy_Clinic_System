    #pragma once
#include "Resource.h"
#include "Scheduler.h"

class Treatment
{
protected:
	int Duration; // The amount of time(timesteps) the treatment takes
	int AssignmentTime; //the time at which this treatment was assigned to a resource
	Resource* AssignedResource;
	char Type; // pls check
public:
	Treatment()
	{
		Duration = -1;
		AssignmentTime = -1;
		AssignedResource = nullptr;
	}

	virtual bool CanAssign() = 0;

	virtual bool MoveToWait() = 0;

	int GetDuration()
	{
		return Duration;
	}

	void Set_Duration(int t)
	{
		Duration = t;
	}
	void set_type(char c)
	{
		Type = c;
	}
	char get_type()
	{
		return Type;
	}

	void Set_Assigned_Resource(Resource* r)
	{
		AssignedResource = r;
	}

	bool Get_Assigned_Resource(Resource*& r)
	{
		if (AssignedResource)
		{
			r = AssignedResource;
			return true;
		}
		else
			return false;
	}

	void setAssignmentTime(int assignment_time)
	{
		AssignmentTime = assignment_time;
	}
};

