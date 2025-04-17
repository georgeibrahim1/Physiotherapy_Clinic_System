#include <iostream>
#include "Scheduler.h"
#include "UI_Class.h"
#include <conio.h>


int main()
{
    Scheduler Maestro;

    /*while (true)
    {*/
        //cout << "\nTimestep :" << timestep << endl;

        Maestro.Simulate();

       // cout << "\nPress any key to proceed to the next timestep..." << endl;
       // _getch();  // Waits for a keypress

        //timestep++;
    
    return 0;
}