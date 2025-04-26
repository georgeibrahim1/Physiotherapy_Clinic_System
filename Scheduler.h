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
#include <climits>



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

    void File_Loading_Function(string s)
    {
        int Num_E_Devices;
        int Num_U_Devices;
        int Num_X_Rooms;
        int Pcancel;
        int Presc;
        int Num_Patients;

        ifstream MyFile(s);//we can add the text name as a parameter in the function

        if (MyFile.is_open())
        {
            MyFile >> Num_E_Devices >> Num_U_Devices >> Num_X_Rooms;
            int* Capacities = new int[Num_X_Rooms];

            for (int i = 0 ; i < Num_X_Rooms ; i++)
            {

                MyFile >> Capacities[i];
            }


            Resource** ResE = new Resource * [Num_E_Devices];
            Resource** ResU = new Resource * [Num_U_Devices];
            X_Resource** ResX = new X_Resource * [Num_X_Rooms];

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
                        E_Treatment* P_Treatment = new E_Treatment();
                        Input_P[i]->Enqueue_ReqTreatment(P_Treatment , Time,'E');
                    }
                    else if(R == 'U')
                    {
                        U_Treatment* P_Treatment = new U_Treatment();
                        Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time,'U');
                    }
                    else if(R == 'X')
                    {
                        X_Treatment* P_Treatment = new X_Treatment();
                        Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time,'X');
                    }
                }
                Input_P[i]->setStaute(IDLE);
                All_Patients.enqueue(Input_P[i]);
            }

           delete []Capacities;


            delete []ResE;
            delete []ResU;
            delete []ResX;
            delete []Input_P;

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
                temp->setStaute(ERLY);
                Early_Patients.enqueue(temp, -temp->getPT());// Sorted by PT
                r = true;
                //Done : to EarlyPList after merging the branches
            }
            else if (temp->getPT() < temp->getVT()) //late
            {
                All_Patients.dequeue(temp);
                temp->setStaute(LATE);
                Late_Patients.enqueue(temp, -(temp->getVT() + Late_Penalty(temp))); // Sorted by VT+Penalty
                r = true;
            }
            else // Move to Waiting List 
            { // this should probably be deleted, what the hell is it doing here? it doesn't belong here.
                All_Patients.dequeue(temp);
                Treatment* reqTreatment = nullptr;
                    
                if (temp->Peek_ReqTreatment(reqTreatment))
                {
                    if (dynamic_cast<X_Treatment*>(reqTreatment))
                    {
                        MoveToWait_X(temp);
                        r = true;
                    }
                    else if (dynamic_cast<U_Treatment*>(reqTreatment))
                    {
                        MoveToWait_U(temp);
                        r = true;
                    }
                    else if (dynamic_cast<E_Treatment*>(reqTreatment))
                    {
                        MoveToWait_E(temp);
                        r = true;
                    }
                }
            }
            // All_Patients.peek(temp);
        }
        return r;
    }
    bool Check_Early_List() 
    {
        Patient* temp;
        bool r = false;
        int priority = 0; // Early patient list is a priority queue, so it needs priority as a parameter 
        Treatment* reqTreatment = nullptr;


        if (!Early_Patients.peek(temp,priority))
        {
            return false;
        }
        while (Early_Patients.peek(temp,priority) && timestep == temp->getPT()) // checks if the appointment time  
        {                                                                       // of the front patient matches the timestep
            Early_Patients.dequeue(temp, priority);

            if (temp->get_Type() == 'R') // logic of recovering patients, we have to check treatment latencies
            {
                LinkedQueue<Treatment*> TempReqTreatmentList;
                Treatment* TreatmentOfList = nullptr; // this will have the treatment of the list with the least Latency

                int LeastLatency = INT_MAX; // we will use this variable to get the min latency


                while (temp->Dequeue_ReqTreatment(reqTreatment))
                {

                    if (GetTreatmentLatency(reqTreatment) < LeastLatency)
                    {
                        LeastLatency = GetTreatmentLatency(reqTreatment);
                        TreatmentOfList = reqTreatment;
                    }

                   /* if (dynamic_cast<X_Treatment*>(reqTreatment))
                    {*/

                      /*  if (X_Waiting_Patients.GetTreatmentLatency() < LeastLatency)
                        {
                            LeastLatency = X_Waiting_Patients.GetTreatmentLatency();
                            TreatmentOfList = reqTreatment;
                        }


                    }
                    else if (dynamic_cast<U_Treatment*>(reqTreatment))
                    {

                        if (U_Waiting_Patients.GetTreatmentLatency() < LeastLatency)
                        {
                            LeastLatency = U_Waiting_Patients.GetTreatmentLatency();
                            TreatmentOfList = reqTreatment;
                        }
                    }
                    else if (dynamic_cast<E_Treatment*>(reqTreatment))
                    {

                        if (E_Waiting_Patients.GetTreatmentLatency() < LeastLatency)
                        {
                            LeastLatency = E_Waiting_Patients.GetTreatmentLatency();
                            TreatmentOfList = reqTreatment;
                        }
                    }*/
                    TempReqTreatmentList.enqueue(reqTreatment);
                }
                if (TreatmentOfList)
                {
                    r = EnqueueToAppropriateWaitList(temp, TreatmentOfList);
                }
                //if (dynamic_cast<X_Treatment*>(TreatmentOfList))
                //{
                //    MoveToWait_X(temp);//this should be a Treatment function, scheduler should have AddToWait, check doc 2, appendix A
                //    r = true;
                //}
                //else if (dynamic_cast<U_Treatment*>(TreatmentOfList))
                //{
                //    MoveToWait_U(temp);
                //    r = true;
                //}
                //else if (dynamic_cast<E_Treatment*>(TreatmentOfList))
                //{
                //    MoveToWait_E(temp);
                //    r = true;              
                //}

                while (TempReqTreatmentList.dequeue(reqTreatment))
                {
                    if (reqTreatment != TreatmentOfList) 
                    {
                        temp->Dequeue_ReqTreatment(reqTreatment);
                    }
                
                }
                
            }
            else // logic of normal patients
            {
                if (temp->Peek_ReqTreatment(reqTreatment))
                {
                   r = EnqueueToAppropriateWaitList(temp, reqTreatment);
                }            
            }
        }
        return r;
    }

        bool MoveToWait_U(Patient* currPatient)
        {
                bool check = U_Waiting_Patients.enqueue(currPatient);
                if (check)
                {
                    currPatient->setStaute(WAIT);
                }
                return check;
            }

        bool MoveToWait_E(Patient* currPatient)
        {
            bool check = E_Waiting_Patients.enqueue(currPatient);
            if (check)
            {
                currPatient->setStaute(WAIT);
            }
            return check;
        }

        bool MoveToWait_X(Patient* currPatient)
        {
            bool check = X_Waiting_Patients.enqueue(currPatient);
            if (check)
            {
                currPatient->setStaute(WAIT);
            }
            return check;
        }

        bool From_Early_To_Wait()
        {
            Patient* temp;
            Treatment* reqTreatment = nullptr;
            int priority;
            bool r = false;

            while (Early_Patients.peek(temp,priority) && timestep == -priority)
            {
                if (temp->Peek_ReqTreatment(reqTreatment))
                {
                    if (dynamic_cast<X_Treatment*>(reqTreatment))
                    {
                        bool check = Early_Patients.dequeue(temp,priority);
                        if (check)
                        {
                            MoveToWait_X(temp);
                            r = true;
                        }
                    }
                    else if (dynamic_cast<U_Treatment*>(reqTreatment))
                    {
                        bool check = Early_Patients.dequeue(temp, priority);
                        if (check)
                        {
                            MoveToWait_U(temp);
                            r = true;
                        }
                    }
                    else if (dynamic_cast<E_Treatment*>(reqTreatment))
                    {
                        bool check = Early_Patients.dequeue(temp, priority);
                        if (check)
                        {
                            MoveToWait_E(temp);
                            r = true;
                        }
                    }
                }
            }

            return r;
        }

        bool From_Late_To_Wait()
        {
            Patient* temp;
            Treatment* reqTreatment = nullptr;
            int priority;
            bool r = false;

            while (Late_Patients.peek(temp, priority) && timestep == -priority)
            {
                if (temp->Peek_ReqTreatment(reqTreatment))
                {
                    if (dynamic_cast<X_Treatment*>(reqTreatment))
                    {
                        bool check = Late_Patients.dequeue(temp, priority);
                        if (check)
                        {
                            MoveToWait_X(temp);
                            r = true;
                        }
                    }
                    else if (dynamic_cast<U_Treatment*>(reqTreatment))
                    {
                        bool check = Late_Patients.dequeue(temp, priority);
                        if (check)
                        {
                            MoveToWait_U(temp);
                            r = true;
                        }
                    }
                    else if (dynamic_cast<E_Treatment*>(reqTreatment))
                    {
                        bool check = Late_Patients.dequeue(temp, priority);
                        if (check)
                        {
                            MoveToWait_E(temp);
                            r = true;
                        }
                    }
                }
            }

            return r;
        }
        bool EnqueueToAppropriateWaitList(Patient* patient, Treatment* treatment)
        {
            bool r = false;
            if (dynamic_cast<X_Treatment*>(treatment))
            {             
                r = MoveToWait_X(patient);    
                    
            }
            else if (dynamic_cast<U_Treatment*>(treatment))
            {
                r = MoveToWait_U(patient);
                     
            }
            else if (dynamic_cast<E_Treatment*>(treatment))
            {
                r = MoveToWait_E(patient);
                    
            }
            return r;
        }


        int GetTreatmentLatency(Treatment* treatment)
        {
            if (dynamic_cast<X_Treatment*>(treatment))
                return X_Waiting_Patients.GetTreatmentLatency();
            else if (dynamic_cast<U_Treatment*>(treatment))
                return U_Waiting_Patients.GetTreatmentLatency();
            else if (dynamic_cast<E_Treatment*>(treatment))
                return E_Waiting_Patients.GetTreatmentLatency();
            return INT_MAX;
        }

        

        void Simulate()
        {
            Patient* temp = nullptr;
            int priority; // Dummy Variable
            bool check=false;
            string inputfile = UI_Class::ReadInput();
            File_Loading_Function(inputfile);
            timestep = 0;
            int NumAllPatients = All_Patients.getcount();
            while(Finished_Patients.getCount() != NumAllPatients)
            {
                cout << "\nTimestep :" << timestep << endl;

                Check_All_List();
                From_Early_To_Wait();
                From_Late_To_Wait();

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
        }
        

        double Late_Penalty(Patient* Late_Patient)
        {
            return (Late_Patient->getPT() + Late_Patient->getVT()) / 2.0;
        }

};