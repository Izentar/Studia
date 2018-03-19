/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 19.03.2018
*/

#include <iostream>

#include "headers/student.h"

using namespace std;

int main(int ac, char* av[], char* ev[])
{
    if(test())
    {
        cout << "something went wrong" << endl;
    }
    else
    {
        cout << "All OK" << endl;
    }

    //menu();

    return 0;
}

