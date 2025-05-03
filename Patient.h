#pragma once

//#include "Treatment.h"
#include "E_Treatment.h"
#include "U_Treatment.h"
#include "X_Treatment.h"

#include "LinkedQueue.h"
using namespace std;

//class Treatment;
class E_Treatment;
class U_Treatment;
class X_Treatment;

enum P_Status
{
	IDLE,
	ERLY,
	LATE,
	WAIT,
	SERV,
	FNSH
};

class Treatment;

class Patient
{
protected:
	int ID;
	int PT;
	int VT;
	int FT;
	char Type; // N or R
	char State;// early or late (E or L)
	P_Status Status;
	int DidReschedule; // to be used in in output file
	bool DidCancel;
	int waitTime;
	int EnteredWaitRoom; // time of entering waiting list
	int treatmentTime;
	int LatePenalty;
	LinkedQueue<Treatment*> ReqTreatmentList;

public:

	Patient();

	Patient(int d, int pt, int vt, char type);

	void Set_ID(int d);

	void Set_PT(int pt);

	int getPT() const;

	void Set_VT(int vt);

	int getVT() const;

	void Set_FT(int ft);

	int getFT() const;

	int getID() const;

	P_Status getStatue() const;

	void setStaute(P_Status S);

	void Set_Type(char T);

	void Set_State(char T);

	void IncDidReschedule(int T);

	void SetDidCancel(bool T);

	int GetDidReschedule() const;

	bool GetDidCancel() const;

	int GetwaitTime() const;

	int getEnteredWaitRoom() const;

	void Set_EnteredWaitRoom(int t);


	void IncwaitTime(int T);

	int GettreatmentTime() const;

	void InctreatmentTime(int T);

	int GetLatePenalty() const;

	void SetLatePenalty(double T);

	char get_Type() const;

	char get_State() const;

	bool Enqueue_ReqTreatment(Treatment* treatment, int d, char type);

	bool Dequeue_ReqTreatment(Treatment*& temp);

	bool Peek_ReqTreatment(Treatment*& temp);

	LinkedQueue<Treatment*> Get_reqtreatmentlist() const;

	int Get_reqtreatmentlistcount();

	void Print();

	friend ostream& operator << (ostream& outFile, const Patient& p);
};
