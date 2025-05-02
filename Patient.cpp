#include "Patient.h"

#include "X_Treatment.h"
#include "U_Treatment.h"
#include "E_Treatment.h"



Patient::Patient()
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

Patient::Patient(int d, int pt, int vt, char type) : ID(d), PT(pt), VT(vt), FT(0), Type(type), DidReschedule(0), DidCancel(false), waitTime(0), treatmentTime(0), LatePenalty(0)
	{
		//CurrTreatment == nullptr;
	}

	void Patient::Set_ID(int d)
	{
		ID = d;
	}

	void Patient::Set_PT(int pt)
	{
		PT = pt;
	}

	int Patient::getPT() const
	{
		return PT;
	}

	void Patient::Set_VT(int vt)
	{
		VT = vt;
	}

	int Patient::getVT() const
	{
		return VT;
	}

	void Patient::Set_FT(int ft)
	{
		FT = ft;
	}

	int Patient::getFT() const
	{
		return FT;
	}

	int Patient::getID() const
	{
		return ID;
	}

	P_Status Patient::getStatue() const
	{
		return Status;
	}

	void Patient::setStaute(P_Status S)
	{
		Status = S;
	}

	void Patient::Set_Type(char T)
	{
		Type = T;
	}

	void Patient::Set_State(char T)
	{
		State = T;
	}

	void Patient::IncDidReschedule(int T)
	{
		DidReschedule = DidReschedule + T;
	}

	void Patient::SetDidCancel(bool T)
	{
		DidCancel = T;
	}



	int Patient::GetDidReschedule() const
	{
		return DidReschedule;
	}

	bool Patient::GetDidCancel() const

	{
		return DidCancel;

	}
	int Patient::GetwaitTime() const
	{
		return waitTime;
	}
	void Patient::IncwaitTime(int T)
	{
		waitTime = waitTime + T;
	}

	int Patient::GettreatmentTime() const
	{
		return treatmentTime;
	}
	void Patient::InctreatmentTime(int T)
	{
		treatmentTime = treatmentTime + T;
	}

	int Patient::GetLatePenalty() const
	{
		return LatePenalty;
	}

	void Patient::SetLatePenalty(double T)
	{
		LatePenalty = T;
	}



	char Patient::get_Type() const
	{
		return Type;
	}
	char Patient::get_State() const
	{
		return State;
	}

	bool Patient::Enqueue_ReqTreatment(Treatment* treatment, int d, char type)
	{
		treatment->Set_Duration(d);
		treatment->set_type(type);
		bool check = ReqTreatmentList.enqueue(treatment);
		return check;
	}

	bool Patient::Dequeue_ReqTreatment(Treatment*& temp)
	{
		bool check = ReqTreatmentList.dequeue(temp);
		return check;
	}

	bool Patient::Peek_ReqTreatment(Treatment*& temp)
	{
		bool check = ReqTreatmentList.peek(temp);
		return check;
	}

	LinkedQueue<Treatment*> Patient::Get_reqtreatmentlist() const
	{
		return ReqTreatmentList;
	}

	int Patient::Get_reqtreatmentlistcount()
	{
		return ReqTreatmentList.getcount();
	}

	void Patient::Print()
	{
		if (Status == IDLE)
		{
			cout << "P" << ID << "_" << VT;
		}
		else if (Status == ERLY)
		{
			cout << ID;
			//cout << endl << PT; // for debugging
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

	ostream& operator << (ostream& outFile, const Patient& p)
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


