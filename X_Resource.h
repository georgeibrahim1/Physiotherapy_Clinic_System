#pragma once
#include "Resource.h"


class X_Resource : public Resource
{
protected:
	int Capacity;
	int Num_Of_Patients;

public:



	X_Resource(Resource_Type type , int id , int cap) : Resource(type,id) , Capacity(cap)
	{
		Num_Of_Patients = 0;
	}

	bool Increment_Patient()
	{
		if(Num_Of_Patients >= Capacity)
		{
			return false;
		}
		else
		{
			Num_Of_Patients++;
			return true;
		}
	}

	void Decrement_Patient()
	{
		if (Num_Of_Patients > 0)
			Num_Of_Patients--;
	}

	int get_Num_Of_Patients()
	{
		return Num_Of_Patients;
	}

	int get_Capacity()
	{
		return Capacity;
	}

	virtual void Print() const
	{
		
		cout << "R" << Id << "[" << Num_Of_Patients << "," << Capacity << "]";
	}


};