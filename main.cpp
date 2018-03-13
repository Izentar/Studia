/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 11.03.2018
*/

#define DEBUG

#include <iostream>

#include "headers/student.h"

using namespace std;

int main(int ac, char* av[], char* ev[])
{
    S_group A;
    Student *tmp;
    tmp=create(&A);
    delete tmp;



    cout << "Hello world!" << endl;

    return 0;
}
