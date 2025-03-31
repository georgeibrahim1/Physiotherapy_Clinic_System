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
	void SetCurrTreatment(Treatment* c)
	{
		CurrTreatment = c;
	}
	Treatment* GetCurrTreatment()
	{
		return CurrTreatment;
	}
	int getPT() const
	{
		return PT;
	}
};

