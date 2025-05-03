#pragma once
#include "X_Resource.h"

class Scheduler;
class Patient;

class Treatment
{
protected:
	int Duration; // The amount of time(timesteps) the treatment takes
	int AssignmentTime; //the time at which this treatment was assigned to a resource
	Resource* AssignedResource;
	char Type; // pls check
public:
	Treatment();
	virtual bool CanAssign() = 0;
	virtual bool MoveToWait(Scheduler* schedular, Patient* currPatient) = 0;
	int GetDuration();
	void Set_Duration(int t);
	void set_type(char c);
	char get_type();
	void Set_Assigned_Resource(Resource* r);
	bool Get_Assigned_Resource(Resource*& r);
	void setAssignmentTime(int assignment_time);
};

