#include <iostream>
#include "Scheduler.h"
#include "UI_Class.h"
#include <conio.h>


int main()
{
    Scheduler Maestro;
    //Nour: I think the while loop should be here, we should have two loops. one for silent mode and one for normal.
    // the loop for silent mode will call simulate.
    // the loop for normal mode will call simulate then print to the console.
    Maestro.Simulate();
    Maestro.Create_Output_File();
    return 0;
}