#pragma once
#include"LinkedQueue.h"
#include"Treatment.h"
#include"X_Treatment.h"
#include"U_Treatment.h"
#include"E_Treatment.h"

enum P_Status
{
	IDLE,
	ERLY,
	LATE,
	WAIT,
	SERV,
	FNSH
};


class Patient
{
protected:
	int ID;
	int PT;
	int VT;
	char Type; // N or R
	LinkedQueue<Treatment*> ReqTreatmentList;
	P_Status Status;
	static int N_Patitents, R_Patients, R_Waiting_Time, N_Waiting_Time,
		R_Treatment_Time, N_Treatment_Time, Total_Early, Total_Late,Total_Presc,Total_Pcancel,Avg_Late_Penalty;

	//Treatment* CurrTreatment;// wasn't mentioned by TAs

public:

	Patient()
	{
		 ID = 0;
		 PT = 0;
		 VT = 0;
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

	int getID()
	{
		return ID;
	}

	P_Status getStatue()
	{
		return Status;
	}

	void setStaute(P_Status S)
	{
		Status = S;
	}

	void Set_Type(char T)
	{
		Type = T;
	}
	char get_Type()
	{
		return Type;
	}

	bool Enqueue_ReqTreatment(Treatment* treatment , int d,char type )
	{
		treatment->Set_Duration(d);
		treatment->set_type(type);
		bool check = ReqTreatmentList.enqueue(treatment);
		return check;
	}

	bool Dequeue_ReqTreatment(Treatment*& temp)
	{
		 bool check = ReqTreatmentList.dequeue(temp);
		 return check;
	}

	bool Peek_ReqTreatment(Treatment* temp)
	{
		bool check = ReqTreatmentList.peek(temp);
		return check;
	}
	/*void SetCurrTreatment(Treatment* c)
	{
		CurrTreatment = c;
	}

	Treatment* GetCurrTreatment()
	{
		return CurrTreatment;
	}*/

	LinkedQueue<Treatment*> Get_reqtreatmentlist()
	{
		return ReqTreatmentList;
	}

	int Get_reqtreatmentlistcount()
	{
		return ReqTreatmentList.getcount();
	}

	void Print()
	{
		if (Status == IDLE)
		{
			cout << "P" << ID << "_" << VT;
		}
		else if (Status == ERLY)
		{
			cout << ID;
		}
		else if (Status == LATE)
		{
			cout << ID;
		}
		else if (Status == WAIT)
		{
			cout << ID;
		}
		else if (Status == SERV)
		{
			cout << "P" << ID << "_" << "R0";
		}
		else if (Status == FNSH)
		{
			cout << ID;
		}
	}

};