#pragma once

#include "UI_Class.h" 
#include <fstream>
#include <conio.h>
#include <random>
#include <climits>
#include <iomanip>



class Patient;
class EarlyPList;
class EU_WaitList;
class X_WaitList;


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
    LinkedQueue<X_Resource*> X_Rooms;
    priQueue<Patient*> In_Treatment_List;
    ArrayStack<Patient*> Finished_Patients;
    int timestep, Pcancel, Presc;


public:

    void Simulate();

    bool File_Loading_Function(string s);

    bool Check_All_List();

    bool Check_Early_List();

    bool MoveToWait_U(Patient* currPatient);

    bool MoveToWait_E(Patient* currPatient);

    bool MoveToWait_X(Patient* currPatient);

    bool From_Late_To_Wait();

    bool EnqueueToAppropriateWaitList(Patient* patient, Treatment* treatment);

    bool Assign_E();

    bool Assign_U();

    bool Assign_X();

    bool From_InTreatment_To_Wait_or_Finsih();

    void PrepareRecoveringPatient(Patient* temp);

    int GetTreatmentLatency(Treatment* treatment);

    int Late_Penalty(Patient* Late_Patient);

    bool Cancel_Treatment();

    bool Reschedule_Treatment();

    int generateRandomNumber(int min, int max, unsigned int seed = 42);

    bool Create_Output_File();
    ~Scheduler();
};