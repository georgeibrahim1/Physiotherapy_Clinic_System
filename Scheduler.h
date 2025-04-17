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
#include <conio.h>
#include <random>


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
    int timestep;

public:

    Scheduler()
    {
        //srand(time(0));
    }
    int getRandomNumber(int min = 0, int max = 100)
    {
        static std::mt19937 rng(42); // Fixed seed for reproducibility
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }


 
    int generateRandomNumber(int min, int max, unsigned int seed = 42)
    {
        static std::mt19937 engine(seed); // Mersenne Twister engine with fixed seed
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }

    void File_Loading_Function()
    {
        int Num_E_Devices;
        int Num_U_Devices;
        int Num_X_Rooms;
        int Pcancel;
        int Presc;
        int Num_Patients;

        ifstream MyFile("pierre2.txt");//we can add the text name as a parameter in the function

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
                ResX[i] = new X_Resource(Room, i,Capacities[i]);
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
            bool r = false;
            if (!All_Patients.peek(temp))
            {
                return false;
            }
            while (All_Patients.peek(temp) && timestep == temp->getVT())
            {
                
                if (temp->getPT() > temp->getVT()) //early
                {
                    All_Patients.dequeue(temp);
                    Early_Patients.enqueue(temp, -temp->getPT());// Sorted by PT
                    r = true;
                    //Done : to EarlyPList after merging the branches
                }
                else if (temp->getPT() < temp->getVT()) //late
                {
                    All_Patients.dequeue(temp);
                    Late_Patients.enqueue(temp, -(temp->getVT() + Late_Penalty(temp))); // Sorted by VT+Penalty
                    r = true;
                }
                else // Move to Waiting List 
                {
                    All_Patients.dequeue(temp);
                    Random_Waiting_List_Enqueue(temp, 0);
                    r = true;
                }
               // All_Patients.peek(temp);
            }
            return r;
        }

        void Simulate()
        {
            Patient* temp = nullptr;
            int priority; // Dummy Variable
            bool check=false;
            File_Loading_Function();
            timestep = 0;
            int NumAllPatients = All_Patients.getcount();
            while(Finished_Patients.getCount() != NumAllPatients)
            {
                cout << "\nTimestep :" << timestep << endl;

                //if (Check_All_List())
                Check_All_List();
                
                    srand(time(0));
                    int Random_Assign = generateRandomNumber(0,100,rand());    // Random no. from [0,100]
                    if (Random_Assign < 10)
                    {
                        check = Early_Patients.dequeue(temp, priority);
                        if (check)
                            Random_Waiting_List_Enqueue(temp, 0);
                    }
                    else if (Random_Assign >= 10 && Random_Assign < 20)
                    {
                        check = Late_Patients.dequeue(temp, priority);
                        if (check)
                            Random_Waiting_List_Enqueue(temp, temp->getPT() + Late_Penalty(temp)); // Sorted by PT+Penalty
                    }
                    else if (Random_Assign >= 20 && Random_Assign < 40)
                    {
                        Dequeue_Twice(temp);
                    }
                    else if (Random_Assign >= 40 && Random_Assign < 50)
                    {
                        check = In_Treatment_List.dequeue(temp, priority);
                        if (check)
                            Random_Waiting_List_Enqueue(temp, temp->getPT()); // Sorted by PT 
                    }
                    else if (Random_Assign >= 50 && Random_Assign < 60)
                    {
                        check = In_Treatment_List.dequeue(temp, priority);
                        if (check)
                            Finished_Patients.push(temp);
                    }
                    else if (Random_Assign >= 60 && Random_Assign < 70)
                    {
                        check = X_Waiting_Patients.cancel(temp);
                        if (check)
                        {
                            Finished_Patients.push(temp);
                            cout << "Cancel Operation Succesful for Patient " << endl;
                        }
                    }
                    else if (Random_Assign >= 70 && Random_Assign < 80)
                    {
                        srand(time(0));
                        int newPriority = generateRandomNumber(0, 1000, rand());
                        check = Early_Patients.reschedule(newPriority);
                        if (check)
                        {
                            // Early_Patients.enqueue(temp, priority);
                            cout << "Reschedule Operation Succesful for Patient " << endl;
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
                cout << "\nPress any key to proceed to the next timestep..." << endl;
                _getch();  // Waits for a keypress
                    timestep++;
            }

           /* UI_Class::PrintOutputScreen(
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
            );*/
        
        }


        double Late_Penalty(Patient* Late_Patient)
        {
            return (Late_Patient->getPT() + Late_Patient->getVT()) / 2.0;
        }

   
        void Random_Waiting_List_Enqueue(Patient* temp,int priority_of_LatePatient)  // Priority matters when assigning a late patient otherwise "priority = 0" 
        {                                                                             
            //srand(time(0));
            int Random_Waiting = generateRandomNumber(0, 100, rand());    // Random no. from [0,100]
            if (Random_Waiting < 33)              // Assign to E Waiting List
            {
                if (!priority_of_LatePatient)                // Checks if late patient 
                    E_Waiting_Patients.enqueue(temp);
                else
                    E_Waiting_Patients.InsertSorted(temp, -priority_of_LatePatient);
            }
            else if (Random_Waiting < 66)         // Assign to U Waiting List
            {

                if (!priority_of_LatePatient)                 // Checks if late patient 
                    U_Waiting_Patients.enqueue(temp);
                else
                    U_Waiting_Patients.InsertSorted(temp, -priority_of_LatePatient);
            }
            else                                  // Assign to X Waiting List
            {

                if (!priority_of_LatePatient)                 // Checks if late patient 
                    X_Waiting_Patients.enqueue(temp);
                else
                    X_Waiting_Patients.InsertSorted(temp, -priority_of_LatePatient);
            }
        }

        void Dequeue_Twice(Patient* temp)
        {
            bool check = false;
            srand(time(0));
            int Random_Waiting = generateRandomNumber(0, 100, rand());    // Random no. from [0,100]
            if (Random_Waiting < 33)              // Assign to E Waiting List
            {
                for (int i = 0; i < 2; i++)
                {
                    check = E_Waiting_Patients.dequeue(temp);
                    if (check)
                    {
                        Treatment* x;
                        temp->Get_reqtreatmentlist().peek(x);
                        In_Treatment_List.enqueue(temp, -(x->GetDuration() + timestep));
                    }
                }
            }
            else if (Random_Waiting < 66)         // Assign to U Waiting List
            {
                for (int i = 0; i < 2; i++)
                {
                    check = U_Waiting_Patients.dequeue(temp);
                    if (check)
                    {
                        Treatment* x;
                        temp->Get_reqtreatmentlist().peek(x);
                        In_Treatment_List.enqueue(temp, -(x->GetDuration() + timestep));
                    }
                }
            }
            else                                  // Assign to X Waiting List
            {
                for (int i = 0; i < 2; i++)
                {
                    check = X_Waiting_Patients.dequeue(temp);
                    if (check)
                    {
                        Treatment* x;
                        temp->Get_reqtreatmentlist().peek(x);
                        In_Treatment_List.enqueue(temp, -(x->GetDuration() + timestep));
                    }
                }
            }
        }
};