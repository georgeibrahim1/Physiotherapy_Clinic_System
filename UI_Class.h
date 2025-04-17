#pragma once
#include<string>
class UI_Class
{
public:
    static string ReadInput()
    {
        string s;
        cout << "Type in File Name : ";   
        cin >> s;
        return s;
    }

    static void PrintOutputScreen(
        LinkedQueue<Patient*>& All_Patients,
        EarlyPList& Early_Patients,
        priQueue<Patient*>& Late_Patients,
        EU_WaitList& U_Waiting_Patients,
        EU_WaitList& E_Waiting_Patients,
        X_WaitList& X_Waiting_Patients,
        LinkedQueue<Resource*>& E_Devices,
        LinkedQueue<Resource*>& U_Devices,
        LinkedQueue<Resource*>& X_Rooms,
        priQueue<Patient*>& In_Treatment_List,
        ArrayStack<Patient*>& Finished_Patients)
    {
        cout << "=============== All List ===============\n";
        cout << All_Patients.getcount() << " ";
        cout << "Patients remaining: ";
        All_Patients.PrintAllList();

        cout << "=============== Waiting List ===============\n";
        cout << E_Waiting_Patients.getcount() << " ";
        cout << "E-therapy Patients: ";
        E_Waiting_Patients.PrintAllList();

        cout << endl;

        cout << U_Waiting_Patients.getcount() << " ";
        cout << "U-therapy Patients: ";
        U_Waiting_Patients.PrintAllList();

        cout << endl;

        cout << X_Waiting_Patients.getcount() << " ";
        cout << "X-therapy Patients: ";
        X_Waiting_Patients.PrintAllList();

        cout << endl;

        cout << "=============== Early List ===============\n";
        cout << Early_Patients.getcount() << " ";
        cout << "Patients: ";
        Early_Patients.Print();

        cout << "=============== Late List ===============\n";
        cout << Late_Patients.getcount() << " ";
        cout << "Patients: ";
        Late_Patients.Print();

        cout << "\n=============== Avail E-Devices ===============\n";
        cout << E_Devices.getcount() << " ";
        cout << "Electro Devices: ";
        E_Devices.Print_Avail_EU_Resources();

        cout << "=============== Avail U-Devices ===============\n";
        cout << U_Devices.getcount() << " ";
        cout << "Ultra Devices: ";
        U_Devices.Print_Avail_EU_Resources();

        cout << "=============== Avail X-Devices ===============\n";
        cout << X_Rooms.getcount() << " ";
        cout << "Rooms: ";
        X_Rooms.Print_Avail_X_Resources();

        cout << "=============== In-treatment List ===============\n";
        cout << In_Treatment_List.getcount() << " ";
        cout << "==>";
        In_Treatment_List.Print();
        Resource* x;
        E_Devices.peek(x);
        cout << x->Get_Id();

        cout << "\n======================================\n";
        cout << Finished_Patients.getCount() << " ";
        cout << "Finished Patients: ";
        Finished_Patients.Print();
    }
};