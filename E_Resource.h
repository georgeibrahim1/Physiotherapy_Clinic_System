#pragma once
#include "Resource.h"


class E_Resource : public Resource
{
protected:
	int Assigment_Time;
	int Maintenance_Time;
	bool Destroyed;

public:

	E_Resource(Resource_Type type, int id, int main) : Resource(type, id), Maintenance_Time(main)
	{
		Assigment_Time = -1;
		Destroyed = 0; //flase
	}

	bool Get_Destroyed()
	{
		return Destroyed;
	}

	void Set_Destroyed(bool r)
	{
		Destroyed = r;
	}

	int Get_Assigment_Time()
	{
		return Assigment_Time;
	}

	void Set_Assigment_Time(int r)
	{
		Assigment_Time = r;
	}

	void Set_Maintenance_Time(int t) { Maintenance_Time = t; }

	int Get_Maintenance_Time() const { return Maintenance_Time; }

};