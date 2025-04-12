#pragma once

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
	//int capacity;

public:
	//Resource()
	//{

	//}

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


};