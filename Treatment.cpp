#include"Treatment.h"
#include "Scheduler.h"
#include "Patient.h"

Treatment::Treatment()
{
	Duration = -1;
	AssignmentTime = -1;
	AssignedResource = nullptr;
}

int Treatment::GetDuration()
{
	return Duration;
}

void Treatment::Set_Duration(int t)
{
	Duration = t;
}
void Treatment::set_type(char c)
{
	Type = c;
}
char Treatment::get_type()
{
	return Type;
}

void Treatment::Set_Assigned_Resource(Resource* r)
{
	AssignedResource = r;
}

bool Treatment::Get_Assigned_Resource(Resource*& r)
{
	if (AssignedResource)
	{
		r = AssignedResource;
		return true;
	}
	else
		return false;
}

void Treatment::setAssignmentTime(int assignment_time)
{
	AssignmentTime = assignment_time;
}
