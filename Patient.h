#pragma once
#include"LinkedQueue.h"
#include"Treatment.h"

class Patient
{
protected:
	int ID;
	int PT;
	int VT;
	char Type; // N or R
	LinkedQueue<Treatment*> ReqTreatmentList;
	Treatment* CurrTreatment;// wasn't mentioned by TAs

public:

	Patient()
	{
		 ID = 0;
		 PT = 0;
		 VT = 0;
		 Type = ' ';
	}

	Patient(int d, int pt, int vt, char type) : ID(d) , PT(pt) , VT(vt) , Type(type)
	{
		//CurrTreatment == nullptr;
	}

	void Set_ID(int d)
	{
		ID = d;
	}

	void Set_PT(int pt)
	{
		PT = pt;
	}

	int getPT() const
	{
		return PT;
	}

	void Set_VT(int vt)
	{
		VT = vt;
	}

	int getVT() const
	{
		return VT;
	}

	void Set_Type(char T)
	{
		Type = T;
	}

	void Enqueue_ReqTreatment(Treatment* treatment , int d )
	{
		treatment->Set_Duration(d);
		ReqTreatmentList.enqueue(treatment);
	}

	void SetCurrTreatment(Treatment* c)
	{
		CurrTreatment = c;
	}

	Treatment* GetCurrTreatment()
	{
		return CurrTreatment;
	}

};