#include <iostream>
#include "Scheduler.h"
#include "UI_Class.h"
#include <conio.h>


int main()
{
    Scheduler Maestro;
    Maestro.Simulate();
    bool Created = Maestro.Create_Output_File();
    if (!Created) 
    {
        string s = "Error creating output file!";
        UI_Class::PrintMsg(s);
    }
    /*else
    {
        string s = "Output file created succesfully!";
        UI_Class::PrintMsg(s);
    }*/
    return 0;
}