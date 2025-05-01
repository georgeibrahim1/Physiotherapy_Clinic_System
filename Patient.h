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
	int FT;
	char Type; // N or R
	char State;// early or late (E or L)
	LinkedQueue<Treatment*> ReqTreatmentList;
	P_Status Status;
	int DidReschedule; // to be used in in output file
	bool DidCancel;
	int waitTime;
	int treatmentTime;
	int LatePenalty;
	//friend ostream& operator << (ostream& out, const Patient& p);

public:

	Patient()
	{
		 ID = 0;
		 PT = 0;
		 VT = 0;
		 FT = 0;
		 DidReschedule = 0;
		 DidCancel = false;
		 waitTime = 0;
		 treatmentTime = 0;
		 LatePenalty = 0;
	}

	Patient(int d, int pt, int vt, char type) : ID(d) , PT(pt) , VT(vt), FT(0), Type(type), DidReschedule(0), DidCancel(false), waitTime(0), treatmentTime(0), LatePenalty(0)
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

	int getPT() const const
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

	void Set_FT(int ft)
	{
		FT = ft;
	}

	int getFT() const
	{
		return FT;
	}

	int getID() const
	{
		return ID;
	}

	P_Status getStatue() const
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

	void Set_State(char T)
	{
		State = T;
	}

	void IncDidReschedule(int T)
	{
		DidReschedule = DidReschedule + T;
	}

	void SetDidCancel(bool T)
	{
		DidCancel = T;
	}

	

	int GetDidReschedule() const
	{
		return DidReschedule;
	}

	bool GetDidCancel() const

	{
		return DidCancel;

	}
	int GetwaitTime() const
	{
		return waitTime;
	}
	void IncwaitTime(int T)
	{
		waitTime = waitTime + T;
	}

	int GettreatmentTime() const
	{
		return treatmentTime;
	}
	void InctreatmentTime(int T)
	{
		treatmentTime = treatmentTime + T;
	}

	int GetLatePenalty() const
	{
		return LatePenalty;
	}

	void SetLatePenalty(double T)
	{
		LatePenalty = T;
	}



	char get_Type() const
	{
		return Type;
	}
	char get_State() const
	{
		return State;
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

	bool Peek_ReqTreatment(Treatment*& temp)
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
			cout << endl<< PT; // for debugging
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
			Treatment* tre;
			Resource* res;
			ReqTreatmentList.peek(tre);
			tre->Get_Assigned_Resource(res);
			cout << "P" << ID << "_" << tre->get_type() << res->Get_Id();
		}
		else if (Status == FNSH)
		{
			cout << ID;
		}
	}


	friend ostream& operator << (ostream& outFile, const Patient& p)
	{
		outFile << "| P" << p.getID() << " | "
			<< p.get_Type() << " | "
			<< p.getPT() << " | "
			<< p.getVT() << " | "
			<< p.getFT() << " | "
			<< p.GetwaitTime() << " | "
			<< p.GettreatmentTime() << " | "
			<< (p.GetDidCancel() ? "T" : "F") << " | "
			<< (p.GetDidReschedule() > 0 ? "T" : "F") << " |\n";
		return outFile;
	}

};

