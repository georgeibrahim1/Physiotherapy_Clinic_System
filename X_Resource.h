#pragma once
#include "Resource.h"


class X_Resource : public Resource
{
protected:
	int CapacityA;
	int CapacityB;
	int CapacityC;
	int Num_Of_Patients;
	int Num_Of_PatientsA;
	int Num_Of_PatientsB;
	int Num_Of_PatientsC;

public:



	X_Resource(Resource_Type type , int id ,int a ,int b ,int c) : Resource(type,id) , CapacityA(a) , CapacityB(b), CapacityC(c)
	{
		Num_Of_Patients = 0;
		Num_Of_PatientsA = 0 ;
		Num_Of_PatientsB = 0 ;
		Num_Of_PatientsC = 0;
	}



	// For group A
	bool Increment_PatientA()
	{
		if (Num_Of_PatientsA >= CapacityA)
			return false;
		Num_Of_PatientsA++;
		Num_Of_Patients++;
		return true;
	}

	void Decrement_PatientA()
	{
		if (Num_Of_PatientsA > 0) {
			Num_Of_PatientsA--;
			Num_Of_Patients--;
		}
	}

	// For group B
	bool Increment_PatientB()
	{
		if (Num_Of_PatientsB >= CapacityB)
			return false;
		Num_Of_PatientsB++;
		Num_Of_Patients++;
		return true;
	}

	void Decrement_PatientB()
	{
		if (Num_Of_PatientsB > 0) {
			Num_Of_PatientsB--;
			Num_Of_Patients--;
		}
	}

	// For group C
	bool Increment_PatientC()
	{
		if (Num_Of_PatientsC >= CapacityC)
			return false;
		Num_Of_PatientsC++;
		Num_Of_Patients++;
		return true;
	}

	void Decrement_PatientC()
	{
		if (Num_Of_PatientsC > 0) {
			Num_Of_PatientsC--;
			Num_Of_Patients--;
		}
	}

	int get_Num_Of_PatientsA() { return Num_Of_PatientsA; }
	int get_Num_Of_PatientsB() { return Num_Of_PatientsB; }
	int get_Num_Of_PatientsC() { return Num_Of_PatientsC; }
	int get_CapacityA() { return CapacityA; }
	int get_CapacityB() { return CapacityB; }
	int get_CapacityC() { return CapacityC; }

	virtual void Print() const
	{
		
		cout << "R" << Id << "[" << Num_Of_PatientsA << "," << CapacityA << "-" << Num_Of_PatientsB << "," << CapacityB << "-" << Num_Of_PatientsC << "," << CapacityC << "]";
	}


};