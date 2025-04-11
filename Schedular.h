#pragma once
#include "Patient.h"
#include "LinkedQueue.h"
#include "PriQueue.h"
#include "EU_WaitList.h"
#include "priQueue.h"
#include "EarlyPList.h"
#include "X_WaitList.h"
#include "Resource.h"
#include "ArrayStack.h"
#include <fstream>

class Schedular
{
protected:

	LinkedQueue<Patient*> All_Patients;
	EarlyPList<Patient*> Early_Patients;
	priQueue<Patient*> Late_Patients;
	EU_WaitList<Patient*> U_Waiting_Patients;
	EU_WaitList<Patient*> E_Waiting_Patients;
	X_WaitList<Patient*> X_Waiting_Patients;
	LinkedQueue<Resource*> E_Devices;
	LinkedQueue<Resource*> U_Devices;
	LinkedQueue<Resource*> X_Devices;
	priQueue<Patient*> In_Treatment_List;
	ArrayStack<Patient*> Finished_Patients;

public:

    void File_Loading_Function()
    {
        int Num_E_Devices;
        int Num_U_Devices;
        int Num_X_Devices;

        //int* Ptr = new cap[0];

        int Pcancel;
        int Presc;

        int Num_Patients;

        ifstream MyFile("filename.txt");

        if (MyFile.is_open())
        {
            MyFile >> Num_E_Devices >> Num_U_Devices >> Num_X_Devices;





            MyFile.close();
        }
        else
        {

        }
    }


};