#pragma once
#include <iostream>
using namespace std;

enum Resource_Type
{
	Electro_Device , 
	Ultrasound_Device ,
	Room
};

class Resource
{
protected:
	Resource_Type Type;
	const int Id;
	bool Availability;

public:

	Resource(Resource_Type RT , int ID ) : Type(RT), Id(ID), Availability(1)
	{}

	Resource_Type Get_Type()
	{
		return Type;
	}

	int Get_Id()
	{
		return Id;
	}

	void Set_Availability(bool Statue)
	{
		Availability = Statue;
	}

	bool Get_Availability()
	{
		return Availability;
	}

	virtual void Print() const
	{
		//if (Type == Electro_Device)
		//{
			cout << Id;
		//}
	//	else if (Type == Ultrasound_Device)
		//{
			//cout << Id;
		//}
	}
};