/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 14.03.2018
*/

#define DEBUG

#include <iostream>

#include "headers/student.h"

using namespace std;

int main(int ac, char* av[], char* ev[])
{
    S_group *b, *c, *d;
    /*Student *tmp, *tmp2, *tmp3;
    tmp=create(&A);
    tmp2=create(&A);
    tmp3=create(&A);
    delete tmp3;*/

    b=new S_group;
    c=new S_group;
    d=new S_group;

    delete c;

    cout << "Hello world!" << endl;

    return 0;
}
