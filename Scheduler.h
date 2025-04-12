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

class Scheduler
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
	LinkedQueue<Resource*> X_Rooms;
	priQueue<Patient*> In_Treatment_List;
	ArrayStack<Patient*> Finished_Patients;

public:

    void File_Loading_Function()
    {
        int Num_E_Devices;
        int Num_U_Devices;
        int Num_X_Rooms;
        int* Capacities = new int[Num_X_Rooms];

        int Pcancel;
        int Presc;

        int Num_Patients;

        ifstream MyFile("filename.txt");//we can add the text name as a parameter in the function

        if (MyFile.is_open())
        {
            MyFile >> Num_E_Devices >> Num_U_Devices >> Num_X_Rooms;

            for (int i = 0 ; i < Num_X_Rooms ; i++)
            {

                MyFile >> Capacities[i];
            }


            Resource** ResE = new Resource * [Num_E_Devices];
            Resource** ResU = new Resource * [Num_E_Devices];
            Resource** ResX = new Resource * [Num_E_Devices];

            for (int i = 0; i < Num_E_Devices; i++)
            {
                ResE[i] = new Resource(Electro_Device, i);
                E_Devices.enqueue(ResE[i]);
            }

            for (int i = 0; i < Num_U_Devices; i++)
            {
                ResU[i] = new Resource(Ultrasound_Device, i);
                U_Devices.enqueue(ResU[i]);
            }

            for (int i = 0; i < Num_X_Rooms; i++)
            {
                ResX[i] = new Resource(Ultrasound_Device, i);
                //TODO : set the capacity for each room
                X_Rooms.enqueue(ResX[i]);
            }

            MyFile >> Pcancel >> Presc;

            //TODO : PCANCEL , Presc 

            MyFile >> Num_Patients;

            Patient** Input_P = new Patient * [Num_Patients];

            for (int i = 0; i < Num_Patients; i++)
            {
                char type;
                int PT, VT, NUM_R;
                char R;
                int Time;

                MyFile >> type >> PT >> VT >> NUM_R;
                
                Input_P[i] = new Patient(i, PT, VT, type);

                for (int j = 0 ; j < NUM_R ; j++)
                {
                    MyFile >> R >> Time;

                    if(R == 'E')
                    {
                        Treatment* P_Treatment = new Treatment();
                        Input_P[i]->Enqueue_ReqTreatment(P_Treatment , Time);
                    }
                    else if(R == 'U')
                    {
                        Treatment* P_Treatment = new Treatment();
                        Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time);
                    }
                    else if(R == 'X')
                    {
                        Treatment* P_Treatment = new Treatment();
                        Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time);
                    }
                }

                All_Patients.enqueue(Input_P[i]);
            }

            MyFile.close();
        }
        else
        {
            cout << "Can't Open the File ... :D" << endl;
        }
    }


    bool Check_All_List()
    {
        Patient* temp;

        if(!All_Patients.peek(temp))
        {
            return false;
        }

        if(temp->getPT() > temp->getVT()) //early
        {
            All_Patients.dequeue(temp);
            //TODO : to EarlyPList after merging the branches
        }
        //else if () //late
        //{

        //}
        //else if () //wait
        //{

        //}
    }


};