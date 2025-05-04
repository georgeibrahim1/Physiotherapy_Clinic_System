#include "Scheduler.h"
//#include "EarlyPList.h"
//#include "X_WaitList.h"
//#include "EU_WaitList.h"
//#include "Patient.h"

void Scheduler::Simulate()
{

    Patient* temp = nullptr;
    int priority; // Dummy Variable
    bool check = false;
    string m = "Type in File Name:";
    UI_Class::PrintMsg(m);
    string inputfile = UI_Class::ReadInput();
    bool loaded = File_Loading_Function(inputfile);
    if (!loaded)
    {
        string M = "Can't Open the File ... :D";
        UI_Class::PrintMsg(M);
        return;
    }
    timestep = 1;
    bool silent = true;
    string s = "Do you want it in silent mode ? Y/N.....";
    UI_Class::PrintMsg(s);
    char answer = UI_Class::ReadChar();
    if (answer == 'Y' || answer == 'y')
    {
        silent = 1;
    }
    else if (answer == 'N' || answer == 'n')
    {
        silent = 0;
    }
    else
    {
        while (answer != 'Y' || answer != 'y' || answer != 'N' || answer != 'n')
        {
            //cout << "Invalid Character";
            string sos = "Invalid Character";
            UI_Class::PrintMsg(sos);
            answer = UI_Class::ReadChar();
            //cin >> answer;

            if (answer == 'Y' || answer == 'y')
            {
                silent = 1;
            }
            else if (answer == 'N' || answer == 'n')
            {
                silent = 0;
            }
        }
    }

    int NumAllPatients = All_Patients.getcount();
    while (Finished_Patients.getCount() != NumAllPatients)
    {
       /* if (!silent)
        {
            cout << "\nTimestep :" << timestep << endl;
        }*/

        Check_All_List(); //Moves Fromm All-Patients list to Early/Late/Waiting list
        Check_Early_List();
        Reschedule_Treatment();
        From_Late_To_Wait();
        From_InTreatment_To_Wait_or_Finsih();
        Assign_E();
        Assign_U();
        E_U_To_Destroy(); // It may be destroyed here after assigning U , E
        From_MainT_E_U_to_Avail();
        Cancel_Treatment();
        Assign_X();

        if (!silent)
        {
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
                Finished_Patients,
                MainT_E, MainT_U, timestep);

            string Rotoscope = "\nPress any key to proceed to the next timestep...";
            UI_Class::PrintMsg(Rotoscope);
            //cout << "\nPress any key to proceed to the next timestep..." << endl;
            _getch();  // Waits for a keypress
        }
        timestep++;
    }

    if (silent)
    {
        string F = "Silent Mode, Simulation Ends, Output File Created"; // logically you shouldn't say output file created here because it hasn't been created yet
        UI_Class::PrintMsg(F);
    }
}

bool Scheduler::File_Loading_Function(string s)
{
    int Num_E_Devices;
    int Num_U_Devices;
    int Num_X_Rooms;
    int Num_Patients;

    ifstream MyFile(s);

    if (MyFile.is_open())
    {
        MyFile >> Num_E_Devices >> Num_U_Devices >> Num_X_Rooms;
        int* MainT_E = new int[Num_E_Devices];
        int* MainT_U = new int[Num_U_Devices];
        int* Capacities = new int[Num_X_Rooms];

        for (int i = 0; i < Num_E_Devices; i++)
        {

            MyFile >> MainT_E[i];
        }

        for (int i = 0; i < Num_U_Devices; i++)
        {

            MyFile >> MainT_U[i];
        }

        for (int i = 0; i < Num_X_Rooms; i++)
        {

            MyFile >> Capacities[i];
        }


        E_Resource** ResE = new E_Resource * [Num_E_Devices];
        U_Resource** ResU = new U_Resource * [Num_U_Devices];
        X_Resource** ResX = new X_Resource * [Num_X_Rooms];

        for (int i = 0; i < Num_E_Devices; i++)
        {
            ResE[i] = new E_Resource(Electro_Device, i, MainT_E[i]);
            E_Devices.enqueue(ResE[i]);
        }

        for (int i = 0; i < Num_U_Devices; i++)
        {
            ResU[i] = new U_Resource(Ultrasound_Device, i, MainT_U[i]);
            U_Devices.enqueue(ResU[i]);
        }

        for (int i = 0; i < Num_X_Rooms; i++)
        {
            ResX[i] = new X_Resource(Room, i, Capacities[i]);
            X_Rooms.enqueue(ResX[i]);
        }

        MyFile >> Pcancel >> Presc >> PFreeFail >> PBusyFail;


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




            for (int j = 0; j < NUM_R; j++)
            {
                MyFile >> R >> Time;
                Input_P[i]->InctreatmentTime(Time); // for output file
                if (R == 'E')
                {
                    E_Treatment* P_Treatment = new E_Treatment();
                    Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time, 'E');
                }
                else if (R == 'U')
                {
                    U_Treatment* P_Treatment = new U_Treatment();
                    Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time, 'U');
                }
                else if (R == 'X')
                {
                    X_Treatment* P_Treatment = new X_Treatment();
                    Input_P[i]->Enqueue_ReqTreatment(P_Treatment, Time, 'X');
                }
            }
            Input_P[i]->setStaute(IDLE);
            All_Patients.enqueue(Input_P[i]);
        }

        delete[]Capacities;
        delete[]MainT_E;
        delete[]MainT_U;



        delete[]ResE;
        delete[]ResU;
        delete[]ResX;
        delete[]Input_P;

        MyFile.close();
        return true;
    }
    else
    {
        return false;
    }
}


bool Scheduler::Check_All_List()
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
            temp->Set_State('E'); //early

            Early_Patients.enqueue(temp, -temp->getPT());// Sorted by PT
            r = true;
            //Done : to EarlyPList after merging the branches
        }
        else if (temp->getPT() < temp->getVT()) //late
        {
            All_Patients.dequeue(temp);
            temp->setStaute(LATE);
            temp->Set_State('L');//late
            Late_Patients.enqueue(temp, -(temp->getVT() + Late_Penalty(temp))); // Sorted by VT+Penalty
            r = true;
        }
        else // Move to Waiting List 
        {
            All_Patients.dequeue(temp);
            Treatment* reqTreatment = nullptr;

            if (temp->get_Type() == 'R')
            {
                PrepareRecoveringPatient(temp);
            }

            if (temp->Peek_ReqTreatment(reqTreatment))
            {
                EnqueueToAppropriateWaitList(temp, reqTreatment);
                temp->Set_EnteredWaitRoom(timestep);
            }
        }
    }
    return r;
}
bool Scheduler::Check_Early_List()
{
    Patient* temp;
    bool r = false;
    int priority = 0; // Early patient list is a priority queue, so it needs priority as a parameter 
    Treatment* reqTreatment = nullptr;


    if (!Early_Patients.peek(temp, priority))
    {
        return false;
    }
    while (Early_Patients.peek(temp, priority) && timestep == temp->getPT()) // checks if the appointment time  
    {                                                                       // of the front patient matches the timestep
        Early_Patients.dequeue(temp, priority);

        if (temp->get_Type() == 'R') // logic of recovering patients, we have to check treatment latencies
        {
            PrepareRecoveringPatient(temp);
        }
        // logic of normal patients (after PrepareRecoveringPatient() , Recovering patients are treated as normal)
        {
            if (temp->Peek_ReqTreatment(reqTreatment))
            {

                r = EnqueueToAppropriateWaitList(temp, reqTreatment);
                temp->Set_EnteredWaitRoom(timestep);
            }
        }
    }
    return r;
}

bool Scheduler::MoveToWait_U(Patient* currPatient)
{
    char state = currPatient->get_State();
    bool check = false;
    if (state == 'E' && currPatient->getStatue() != SERV)
        check = U_Waiting_Patients.enqueue(currPatient);
    else if (state == 'L' && currPatient->getStatue() != SERV)
        check = U_Waiting_Patients.InsertSorted(currPatient, currPatient->getPT() + Late_Penalty(currPatient));
    else if (currPatient->getStatue() == SERV)
        check = U_Waiting_Patients.InsertSorted(currPatient, currPatient->getPT());
    else
        check = U_Waiting_Patients.enqueue(currPatient);

    if (check)
    {
        currPatient->setStaute(WAIT);
    }
    return check;
}

bool Scheduler::MoveToWait_E(Patient* currPatient)
{
    char state = currPatient->get_State();
    bool check = false;
    if (state == 'E' && currPatient->getStatue() != SERV)
        check = E_Waiting_Patients.enqueue(currPatient);
    else if (state == 'L' && currPatient->getStatue() != SERV)
        check = E_Waiting_Patients.InsertSorted(currPatient, currPatient->getPT() + Late_Penalty(currPatient));
    else if (currPatient->getStatue() == SERV)
        check = E_Waiting_Patients.InsertSorted(currPatient, currPatient->getPT());
    else
        check = E_Waiting_Patients.enqueue(currPatient);

    if (check)
    {
        currPatient->setStaute(WAIT);
    }
    return check;
}

bool Scheduler::MoveToWait_X(Patient* currPatient)
{
    char state = currPatient->get_State();
    bool check = false;
    if (state == 'E' && currPatient->getStatue() != SERV)
        check = X_Waiting_Patients.enqueue(currPatient);
    else if (state == 'L' && currPatient->getStatue() != SERV)
        check = X_Waiting_Patients.InsertSorted(currPatient, currPatient->getPT() + Late_Penalty(currPatient));
    else if (currPatient->getStatue() == SERV)
        check = X_Waiting_Patients.InsertSorted(currPatient, currPatient->getPT());
    else
        check = X_Waiting_Patients.enqueue(currPatient);

    if (check)
    {
        currPatient->setStaute(WAIT);
    }
    return check;
}

bool Scheduler::From_Late_To_Wait()
{
    Patient* temp;
    Treatment* reqTreatment = nullptr;
    int priority;
    bool r = false;

    while (Late_Patients.peek(temp, priority) && timestep == -priority)
    {
        Late_Patients.dequeue(temp, priority);

        if (temp->get_Type() == 'R')
        {
            PrepareRecoveringPatient(temp);
        }

        if (temp->Peek_ReqTreatment(reqTreatment))
        {
            r = EnqueueToAppropriateWaitList(temp, reqTreatment);
            temp->Set_EnteredWaitRoom(timestep);
        }
    }

    return r;
}

bool Scheduler::EnqueueToAppropriateWaitList(Patient* patient, Treatment* treatment)
{
    bool r = false;
    r = treatment->MoveToWait(this, patient);
    return r;
}

bool Scheduler::Assign_E()
{
    Patient* currPatient;
    Resource* resource = nullptr;
    Treatment* treatment = nullptr;
    bool patientmoved = false;

    while (E_Waiting_Patients.peek(currPatient))
    {

        if (currPatient->Peek_ReqTreatment(treatment))
        {
            if (treatment->CanAssign(this))
            {
                if (E_Waiting_Patients.dequeue(currPatient) && E_Devices.dequeue(resource))
                {
                    if (dynamic_cast<E_Resource*>(resource)->Get_Destroyed() == 0)
                    {
                        resource->Set_Availability(0);
                        treatment->Set_Assigned_Resource(resource);
                        treatment->setAssignmentTime(timestep);
                        currPatient->IncwaitTime(timestep - currPatient->getEnteredWaitRoom());
                        patientmoved = true;
                        currPatient->setStaute(SERV);
                        In_Treatment_List.enqueue(currPatient, -(timestep + treatment->GetDuration()));
                    }
                    else
                    {
                        dynamic_cast<E_Resource*>(resource)->Set_Assigment_Time(timestep);
                        MainT_E.enqueue(resource);
                    }
                }
            }
            else
                break;
        }
    
    }

    return patientmoved;
}

bool Scheduler::Assign_U()
{
    Patient* currPatient;
    Resource* resource = nullptr;
    Treatment* treatment = nullptr;
    bool patientmoved = false;

    while (U_Waiting_Patients.peek(currPatient))
    {
        if (currPatient->Peek_ReqTreatment(treatment))
        {
            if (treatment->CanAssign(this))
            {
                if (U_Waiting_Patients.dequeue(currPatient) && U_Devices.dequeue(resource))
                {
                    if (dynamic_cast<U_Resource*>(resource)->Get_Destroyed() == 0)
                    {
                        resource->Set_Availability(0);
                        treatment->Set_Assigned_Resource(resource);
                        treatment->setAssignmentTime(timestep);
                        currPatient->IncwaitTime(timestep - currPatient->getEnteredWaitRoom());
                        patientmoved = true;
                        currPatient->setStaute(SERV);
                        In_Treatment_List.enqueue(currPatient, -(timestep + treatment->GetDuration()));
                    }
                    else
                    {
                        dynamic_cast<U_Resource*>(resource)->Set_Assigment_Time(timestep);
                        MainT_U.enqueue(resource);
                    }
                }
            }
            else
                break;
        }
    }

    return patientmoved;
}

bool Scheduler::From_MainT_E_U_to_Avail()
{
    bool OneRepaired = false;
    Resource* temp;
    LinkedQueue<Resource*> tempQ;

    // Handle E_Resources
    while (MainT_E.dequeue(temp)) {
        E_Resource* eres = dynamic_cast<E_Resource*>(temp);
        if (eres && timestep == eres->Get_Assigment_Time() + eres->Get_Maintenance_Time()) {
            eres->Set_Destroyed(0);
            E_Devices.enqueue(temp);
            OneRepaired = true;
        }
        else {
            tempQ.enqueue(temp);
        }
    }
    while (tempQ.dequeue(temp)) MainT_E.enqueue(temp);

    // Handle U_Resources
    while (MainT_U.dequeue(temp)) {
        U_Resource* ures = dynamic_cast<U_Resource*>(temp);
        if (ures && timestep == ures->Get_Assigment_Time() + ures->Get_Maintenance_Time()) {
            ures->Set_Destroyed(0);
            U_Devices.enqueue(temp);
            OneRepaired = true;
        }
        else {
            tempQ.enqueue(temp);
        }
    }
    while (tempQ.dequeue(temp)) MainT_U.enqueue(temp);

    return OneRepaired;
}

bool Scheduler::Assign_X()
{
    Patient* currPatient;
    X_Resource* resource = nullptr;
    Treatment* treatment = nullptr;
    bool patientmoved = false;

    while (X_Waiting_Patients.peek(currPatient))
    {
        if (currPatient->Peek_ReqTreatment(treatment))
        {
            if (treatment->CanAssign(this))
            {
                if (X_Waiting_Patients.dequeue(currPatient) && X_Rooms.peek(resource))
                {
                    if (resource->get_Capacity() - resource->get_Num_Of_Patients() > 1)
                    {
                        if (resource->Increment_Patient())
                        {
                            treatment->Set_Assigned_Resource(resource);
                            treatment->setAssignmentTime(timestep);
                            currPatient->IncwaitTime(timestep - currPatient->getEnteredWaitRoom());
                            patientmoved = true;
                            currPatient->setStaute(SERV);
                            In_Treatment_List.enqueue(currPatient, -(timestep + treatment->GetDuration()));
                        }
                    }
                    else
                    {
                        if (resource->Increment_Patient())
                        {
                            if (X_Rooms.dequeue(resource))
                            {
                                resource->Set_Availability(0);
                                treatment->Set_Assigned_Resource(resource);
                                treatment->setAssignmentTime(timestep);
                                currPatient->IncwaitTime(timestep - currPatient->getEnteredWaitRoom());
                                patientmoved = true;
                                currPatient->setStaute(SERV);
                                In_Treatment_List.enqueue(currPatient, -(timestep + treatment->GetDuration()));
                            }
                        }
                    }

                }
            }
            else
            {
                break;
            }
        }
    }

    return patientmoved;
}


bool Scheduler::From_InTreatment_To_Wait_or_Finsih()
{
    Patient* currPatient;
    Treatment* treatment = nullptr;
    Resource* resource = nullptr;
    int Priority;
    bool patientmoved = false;

    while (In_Treatment_List.peek(currPatient, Priority) && timestep == -(Priority))
    {
        //Change Resource Status
        //Dequeue the treatment from Reqtreatment List
        if (currPatient->Peek_ReqTreatment(treatment))
        {
            if (dynamic_cast<X_Treatment*>(treatment))
            {
                if (treatment->Get_Assigned_Resource(resource))
                {
                    if (resource->Get_Availability())
                    {
                        dynamic_cast<X_Resource*>(resource)->Decrement_Patient();
                        treatment->Set_Assigned_Resource(nullptr);
                        currPatient->Dequeue_ReqTreatment(treatment);
                        delete treatment;
                    }
                    else
                    {
                        resource->Set_Availability(1);
                        dynamic_cast<X_Resource*>(resource)->Decrement_Patient();
                        X_Rooms.enqueue(dynamic_cast<X_Resource*>(resource));
                        treatment->Set_Assigned_Resource(nullptr);
                        currPatient->Dequeue_ReqTreatment(treatment);
                        delete treatment;
                    }
                }
            }
            else if (dynamic_cast<U_Treatment*>(treatment))
            {
                if (treatment->Get_Assigned_Resource(resource))
                {
                    resource->Set_Availability(1);
                    U_Devices.enqueue(resource);
                    treatment->Set_Assigned_Resource(nullptr);
                    currPatient->Dequeue_ReqTreatment(treatment);
                    delete treatment;
                }
            }
            else if (dynamic_cast<E_Treatment*>(treatment))
            {
                if (treatment->Get_Assigned_Resource(resource))
                {
                    resource->Set_Availability(1);
                    E_Devices.enqueue(resource);
                    treatment->Set_Assigned_Resource(nullptr);
                    currPatient->Dequeue_ReqTreatment(treatment);
                    delete treatment;
                }
            }
        }


        //Dequeue the patient from In Treatment List
        if (In_Treatment_List.dequeue(currPatient, Priority))
        {
            if (!currPatient->Get_reqtreatmentlistcount())
            {
                currPatient->setStaute(FNSH);
                currPatient->Set_FT(timestep);
                patientmoved = true;
                Finished_Patients.push(currPatient);
            }
            else
            {
                // currPatient->setStaute(WAIT);
                if (currPatient->get_Type() == 'R')
                {
                    PrepareRecoveringPatient(currPatient);
                }

                Treatment* assigned_treatment = nullptr;

                if (currPatient->Peek_ReqTreatment(assigned_treatment)) // logic of moving of recovering and normal is the same after calling Prepare()
                {
                    patientmoved = EnqueueToAppropriateWaitList(currPatient, assigned_treatment);
                    currPatient->Set_EnteredWaitRoom(timestep);

                }
            }
        }

    }

    return patientmoved;
}
// we don't actually enqueue patients to their waitlist, instead we prepare the recovering patient to be treated
// like a normal patient(just dequeue the required treatment list and move that patient to the appropriate treatment wait list) 
void Scheduler::PrepareRecoveringPatient(Patient* temp) // this functions puts the treatment with least latency at the front
{
    Treatment* reqTreatment;
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

        TempReqTreatmentList.enqueue(reqTreatment);
    }



    temp->Enqueue_ReqTreatment(TreatmentOfList, TreatmentOfList->GetDuration(), TreatmentOfList->get_type());// the treatment with the min latency is at front

    while (TempReqTreatmentList.dequeue(reqTreatment))
    {
        if (reqTreatment != TreatmentOfList)
        {
            temp->Enqueue_ReqTreatment(reqTreatment, reqTreatment->GetDuration(), reqTreatment->get_type());
        }
    }

}


int Scheduler::GetTreatmentLatency(Treatment* treatment)
{
    if (dynamic_cast<X_Treatment*>(treatment))
        return X_Waiting_Patients.GetTreatmentLatency();
    else if (dynamic_cast<U_Treatment*>(treatment))
        return U_Waiting_Patients.GetTreatmentLatency();
    else if (dynamic_cast<E_Treatment*>(treatment))
        return E_Waiting_Patients.GetTreatmentLatency();
    return INT_MAX;
}

int Scheduler::Late_Penalty(Patient* Late_Patient)
{
    int P = (Late_Patient->getVT() - Late_Patient->getPT()) / 2;

    Late_Patient->SetLatePenalty(P);
    return P;
}

bool Scheduler::E_U_To_Destroy()
{
    bool One_Had_been_destroyed = false;
    int random_number = generateRandomNumber(0, 100);
    if (random_number < PFreeFail)
    {
        // ----------- E Devices -----------
        int Ecount = E_Devices.getcount();
        if (Ecount > 0) {
            int Eidx = generateRandomNumber(0, Ecount - 1);
            Resource* temp = nullptr;
            // Move Eidx-th device to the front by rotating others to the back
            for (int i = 0; i < Ecount; ++i) {
                E_Devices.dequeue(temp);
                if (i == Eidx) {
                    // mark as destroyed
                    E_Resource* eres = dynamic_cast<E_Resource*>(temp);
                    if (eres) {
                        eres->Set_Destroyed(1);
                        One_Had_been_destroyed = true;
                    }
                }
                E_Devices.enqueue(temp); // Put it back regardless of status
            }
        }

        // ----------- U Devices -----------
        int Ucount = U_Devices.getcount();
        if (Ucount > 0) {
            int Uidx = generateRandomNumber(0, Ucount - 1);
            Resource* temp = nullptr;
            for (int i = 0; i < Ucount; ++i) {
                U_Devices.dequeue(temp);
                if (i == Uidx) {
                    U_Resource* ures = dynamic_cast<U_Resource*>(temp);
                    if (ures) {
                        ures->Set_Destroyed(1);
                        One_Had_been_destroyed = true;
                    }
                }
                U_Devices.enqueue(temp);
            }
        }
    }
    return One_Had_been_destroyed;
}

bool Scheduler::Cancel_Treatment()
{
    int random_number = generateRandomNumber(0, 100);
    if (random_number < Pcancel)
    {
        Patient* temp;
        bool check = X_Waiting_Patients.cancel(temp);
        if (check)
        {
            Finished_Patients.push(temp);
            return true;
        }
    }
    return false;
}
bool Scheduler::Reschedule_Treatment()
{
    int random_number = generateRandomNumber(0, 100);
    if (random_number < Presc)
    {
        bool check = Early_Patients.reschedule();
        if (check)
        {
            return true;
        }
    }
    return false;
}

int Scheduler::generateRandomNumber(int min, int max, unsigned int seed)
{
    static std::mt19937 engine(seed); // Mersenne Twister engine with fixed seed
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}
bool Scheduler::Create_Output_File()
{


    int totalPatients = 0;
    int totalNPatients = 0;
    int totalRPatients = 0;
    int totalWaitTime = 0;
    int totalNWaitTime = 0;
    int totalRWaitTime = 0;
    int totalTreatmentTime = 0;
    int totalNTreatmentTime = 0;
    int totalRTreatmentTime = 0;
    int totalCancelled = 0;
    int totalRescheduled = 0;
    int totalEarly = 0;
    int totalLate = 0;
    double totalLatePenalty = 0;
    double avgWaitAll = 0;
    double avgWaitN = 0;
    double avgWaitR = 0;
    double avgTreatmentAll = 0;
    double avgTreatmentN = 0;
    double avgTreatmentR = 0;
    double cancelPercentage = 0;
    double rescPercentage = 0;
    double earlyPercentage = 0;
    double latePercentage = 0;
    double avgLatePenalty = 0;

    //string msg = "Enter the name of your file";
    //UI_Class::PrintMsg(msg);
    // string outputfile = UI_Class::ReadInput(); // if you want the user to choose the name of the file
    //ofstream outFile(outputfile);

    ofstream outFile("OutputFile.txt");
    if (!outFile.is_open())
    {
        return false;
    }

    //outFile << "| PID | PType | PT | VT | FT | WT | TT | Cancel | Resc |\n";
    //outFile << "|---|---|---|---|---|---|---|---|---|\n";
    outFile << "PID\tPType\tPT\tVT\tFT\tWT\tTT\tCancel\tResc\n";

    while (!Finished_Patients.isEmpty())
    {
        Patient* p;
        Finished_Patients.pop(p);


        totalPatients++;
        if (p->get_Type() == 'N')
            totalNPatients++;
        if (p->get_Type() == 'R')
            totalRPatients++;


        int waitTime = 0;
        waitTime = p->GetwaitTime();
        totalWaitTime += waitTime;
        if (p->get_Type() == 'N')
            totalNWaitTime += waitTime;
        if (p->get_Type() == 'R')
            totalRWaitTime += waitTime;


        int treatmentTime = 0;
        treatmentTime = p->GettreatmentTime();
        totalTreatmentTime += treatmentTime;
        if (p->get_Type() == 'N')
            totalNTreatmentTime += treatmentTime;
        if (p->get_Type() == 'R')
            totalRTreatmentTime += treatmentTime;

        // Count cancellations and reschedules
        if (p->GetDidCancel())
            totalCancelled++;
        if (p->GetDidReschedule() > 0)
            totalRescheduled++;

        /*Count early/late patients*/
        if (p->get_State() == 'E')
            totalEarly++;
        if (p->get_State() == 'L')
        {
            int LatePenalty = 0;
            LatePenalty = p->GetLatePenalty();
            totalLatePenalty += LatePenalty;
            totalLate++;
        }

        // Output patient data
        /*outFile << "| P" << p->getID() << " | "
            << p->get_Type() << " | "
            << p->getPT() << " | "
            << p->getVT() << " | "
            << p->getFT() << " | "
            << waitTime << " | "
            << treatmentTime << " | "
            << (p->GetDidCancel() ? "T" : "F") << " | "
            << (p->GetDidReschedule() > 0 ? "T" : "F") << " |\n";*/
        outFile << *p << "\n";
        delete p;

    }
    if (totalPatients > 0)
    {
        avgWaitAll = (double)totalWaitTime / totalPatients;
        avgTreatmentAll = (double)totalTreatmentTime / totalPatients;
        cancelPercentage = ((double)totalCancelled / totalPatients) * 100;
        rescPercentage = ((double)totalRescheduled / totalPatients) * 100;
        earlyPercentage = ((double)totalEarly / totalPatients) * 100;
        latePercentage = ((double)totalLate / totalPatients) * 100;
    }
    if (totalNPatients > 0)
    {
        avgWaitN = (double)totalNWaitTime / totalNPatients;
        avgTreatmentN = (double)totalNTreatmentTime / totalNPatients;
    }
    if (totalRPatients > 0)
    {
        avgWaitR = (double)totalRWaitTime / totalRPatients;
        avgTreatmentR = (double)totalRTreatmentTime / totalRPatients;
    }

    if (totalLate > 0)
    {
        avgLatePenalty = ((double)totalLatePenalty / totalLate);
    }


    outFile << "\nTotal number of timesteps = " << timestep << "\n";
    outFile << "Total number of all, N, and R patients = "
        << totalPatients << ", " << totalNPatients << ", " << totalRPatients << "\n";
    outFile << "Average total waiting time for all, N, and R patients = "
        << fixed << setprecision(2) << avgWaitAll << ", " << avgWaitN << ", " << avgWaitR << "\n";
    outFile << "Average total treatment time for all, N, and R patients = "
        << fixed << setprecision(2) << avgTreatmentAll << ", " << avgTreatmentN << ", " << avgTreatmentR << "\n";
    outFile << "Percentage of patients of an accepted cancellation (%) = "
        << fixed << setprecision(0) << cancelPercentage << " %\n";
    outFile << "Percentage of patients of an accepted rescheduling (%) = "
        << fixed << setprecision(0) << rescPercentage << " %\n";
    outFile << "Percentage of early patients (%) = "
        << fixed << setprecision(0) << earlyPercentage << " %\n";
    outFile << "Percentage of late patients (%) = "
        << fixed << setprecision(0) << latePercentage << " %\n";
    outFile << "Average late penalty = " << fixed << setprecision(1) << avgLatePenalty << " timestep(s)\n";

    outFile.close();
    return true;
}

bool Scheduler::CanAssign_E()
{
    return !E_Devices.isEmpty();
}

bool Scheduler::CanAssign_U()
{
    return !U_Devices.isEmpty();
}

bool Scheduler::CanAssign_X()
{
    return !X_Rooms.isEmpty();
}

Scheduler::~Scheduler() {
    // Delete all resources
    while (!E_Devices.isEmpty()) 
    {
        Resource* res;
        E_Devices.dequeue(res);
        delete res;
    }
    while (!U_Devices.isEmpty()) 
    {
        Resource* res;
        U_Devices.dequeue(res);
        delete res;
    }
    while (!X_Rooms.isEmpty()) 
    {
        X_Resource* res;
        X_Rooms.dequeue(res);
        delete res;
    }

    while (!MainT_E.isEmpty()) 
    {
        Resource* res;
        MainT_E.dequeue(res);
        delete res;
    }
    while (!MainT_U.isEmpty()) 
    {
        Resource* res;
        MainT_U.dequeue(res);
        delete res;
    }

}