#pragma once
#include "Resource.h"


class E_Resource : public Resource
{
protected:
	int Assigment_Time;
	int Maintenance_Time;
	bool Destroyed;
	int Max_D;

public:

	E_Resource(Resource_Type type, int id, int main) : Resource(type, id), Maintenance_Time(main)
	{
		Assigment_Time = -1;
		Destroyed = 0; //flase
	}

	int Get_Max_D()
	{
		return Max_D;
	}

	void set_Max_D(int y)
	{
		Max_D = y;
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