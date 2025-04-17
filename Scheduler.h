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
#include "X_Resource.h"
#include "UI_Class.h" 
#include <fstream>

class Scheduler
{
protected:

    LinkedQueue<Patient*> All_Patients;
    EarlyPList Early_Patients;
    priQueue<Patient*> Late_Patients;
    EU_WaitList U_Waiting_Patients;
    EU_WaitList E_Waiting_Patients;
    X_WaitList X_Waiting_Patients;
    LinkedQueue<Resource*> E_Devices;
    LinkedQueue<Resource*> U_Devices;
    LinkedQueue<Resource*> X_Rooms;
    priQueue<Patient*> In_Treatment_List;
    ArrayStack<Patient*> Finished_Patients;

public:

    Scheduler()
    {
        srand(time(0));
    }

    void File_Loading_Function()
    {
        int Num_E_Devices;
        int Num_U_Devices;
        int Num_X_Rooms;
        int Pcancel;
        int Presc;
        int Num_Patients;

        ifstream MyFile("test.txt");//we can add the text name as a parameter in the function

        if (MyFile.is_open())
        {
            MyFile >> Num_E_Devices >> Num_U_Devices >> Num_X_Rooms;
            int* Capacities = new int[Num_X_Rooms];

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
                ResX[i] = new X_Resource(Ultrasound_Device, i,Capacities[i]);
                X_Rooms.enqueue(ResX[i]);
            }

            MyFile >> Pcancel >> Presc;

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

            if (!All_Patients.peek(temp))
            {
                return false;
            }
            if (temp->getPT() > temp->getVT()) //early
            {
                All_Patients.dequeue(temp);
                Early_Patients.enqueue(temp, - temp->getPT());// Sorted by PT
                return true;
                //Done : to EarlyPList after merging the branches
            }
            else if (temp->getPT() < temp->getVT()) //late
            {
                All_Patients.dequeue(temp);
                Late_Patients.enqueue(temp, temp->getVT() + Late_Penalty(temp)); // Sorted by VT+Penalty
                return true;
            }
            else // Move to Waiting List 
            {
                All_Patients.dequeue(temp);
                Random_Waiting_List(temp, 0, 1);
                return true;
            }
            return false;
        }

        void Simulate()
        {
            Patient* temp = nullptr;
            int priority; // Dummy Variable
            File_Loading_Function();
            if (Check_All_List())
            {
                
                int Random_Assign = rand() % 101;    // Random no. from [0,100]
                if (Random_Assign < 10)
                {
                    Early_Patients.dequeue(temp,priority);
                    Random_Waiting_List(temp, 0, 1);
                }
                else if (Random_Assign >= 10 && Random_Assign < 20)
                {
                    Late_Patients.dequeue(temp, priority);
                    Random_Waiting_List(temp, temp->getPT() + Late_Penalty(temp), 1); // Sorted by PT+Penalty
                }
                else if (Random_Assign >= 20 && Random_Assign < 40)
                {
                    Dequeue_Twice(temp);
                }
                else if (Random_Assign >= 40 && Random_Assign < 50)
                {
                    In_Treatment_List.dequeue(temp, priority);
                    Random_Waiting_List(temp, temp->getPT(), 1); // Sorted by PT 
                }
                else if (Random_Assign >= 50 && Random_Assign < 60)
                {
                    In_Treatment_List.dequeue(temp,priority);
                    Finished_Patients.push(temp);
                }
                else if (Random_Assign >= 60 && Random_Assign < 70)
                {
                    bool canceled = false;
                    canceled = X_Waiting_Patients.cancel(temp);
                    if (canceled)
                    {
                        Finished_Patients.push(temp);
                        cout << "Cancel Operation Succesful for Patient " << temp->getID() << endl;
                    }
                }
                else if (Random_Assign >= 70 && Random_Assign < 80)
                {
                    bool reschedule = false;
                    
                    int newPriority = rand() % 1000 ;
                    reschedule = Early_Patients.reschedule(newPriority);
                    if (reschedule)
                    {
                        Early_Patients.enqueue(temp, priority);
                        cout << "Reschedule Operation Succesful for Patient " << temp->getID() << endl;
                    }
                }
            }

            UI_Class::PrintOutputScreen(
                All_Patients,
                Early_Patients,
                Late_Patients,
                U_Waiting_Patients,
                E_Waiting_Patients,
                X_Waiting_Patients,
                E_Devices,
                U_Devices,
                X_Rooms,
                In_Treatment_List,
                Finished_Patients
            );
        
        }


        double Late_Penalty(Patient* Late_Patient)
        {
            return (Late_Patient->getPT() + Late_Patient->getVT()) / 2;
        }

   
        void Random_Waiting_List(Patient* temp,int priority,bool enqueue_or_dequeue)  // Priority matters when assigning a late patient otherwise "priority = 0" 
        {                                                                             // Enqueue=1 & Dequeue=0 
            
            int Random_Waiting = rand() % 101;    // Random no. from [0,100]
            if (Random_Waiting < 33)              // Assign to E Waiting List
            {
                if (enqueue_or_dequeue)
                {
                    if (!priority)                // Checks if late patient 
                        E_Waiting_Patients.enqueue(temp);
                    else
                        E_Waiting_Patients.InsertSorted(temp, priority);
                }
                else
                        E_Waiting_Patients.dequeue(temp); 
            }
            else if (Random_Waiting < 66)         // Assign to U Waiting List
            {
                if (enqueue_or_dequeue)
                {
                    if (!priority)                 // Checks if late patient 
                        U_Waiting_Patients.enqueue(temp);
                    else
                        U_Waiting_Patients.InsertSorted(temp, priority);
                }
                else
                    U_Waiting_Patients.dequeue(temp);
            }
            else                                  // Assign to X Waiting List
            {
                if (enqueue_or_dequeue)
                {
                    if (!priority)                 // Checks if late patient 
                        X_Waiting_Patients.enqueue(temp);
                    else
                        X_Waiting_Patients.InsertSorted(temp, priority);
                }
                else
                    X_Waiting_Patients.dequeue(temp);
            }
        }

        void Dequeue_Twice(Patient* temp)
        {
            
            int Random_Waiting = rand() % 101;    // Random no. from [0,100]
            if (Random_Waiting < 33)              // Assign to E Waiting List
            {
                E_Waiting_Patients.dequeue(temp);
                In_Treatment_List.enqueue(temp, temp->GetCurrTreatment()->GetDuration());
                E_Waiting_Patients.dequeue(temp);
                In_Treatment_List.enqueue(temp, temp->GetCurrTreatment()->GetDuration());
            }
            else if (Random_Waiting < 66)         // Assign to U Waiting List
            {
                U_Waiting_Patients.dequeue(temp);
                In_Treatment_List.enqueue(temp, temp->GetCurrTreatment()->GetDuration());
                U_Waiting_Patients.dequeue(temp);
                In_Treatment_List.enqueue(temp, temp->GetCurrTreatment()->GetDuration());
            }
            else                                  // Assign to X Waiting List
            {
                X_Waiting_Patients.dequeue(temp);
                In_Treatment_List.enqueue(temp, temp->GetCurrTreatment()->GetDuration());
                X_Waiting_Patients.dequeue(temp);
                In_Treatment_List.enqueue(temp, temp->GetCurrTreatment()->GetDuration());

            }
        }
};