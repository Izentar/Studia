#ifndef TEST_CPP
#define TEST_CPP


#include <iostream>
#include <fstream>
#include "test.h"

bool test(unsigned int repeat)
{
    string a, b, t;
    Student ABE( "Ala", "ma", "252");
    S_group ISC("jak");

    Student *sp[repeat];
    S_group *sgp[repeat*2];

    for (unsigned int i=0; i<repeat; i++)
    {
        a="S";
        b="G";
        t=to_string(i);
        a+=t;
        b+=t;
        sp[i]=new Student(a, a, a);
        sgp[i]=new S_group(b);
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        b="G";
        t=to_string(i+repeat);
        b+=t;
        sgp[repeat+i]=new S_group(b);
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        connect(*sgp[i], *sp[i]);
    }

    for (unsigned int i=0; i<repeat-1; i++)
    {
        *sgp[repeat+i]+=*sgp[i];
        *sgp[repeat+i]=*sgp[i]+*sgp[i+1];
        *sgp[repeat+i]*=*sgp[i];
        *sgp[repeat+i]=*sgp[i]**sgp[i+1];
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        cout << *sgp[i] << " " << *sp[i] << endl;
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        sgp[i]->display_min_max();
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        delete sp[i];
        delete sgp[i];
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        delete sgp[repeat+i];
    }


    return false;
}

void help()
{
    cout << "create group" << endl;
    cout << "create student" << endl;
    cout << "connect" << endl;
    cout << "min max" << endl;
    cout << "display group" << endl;
    cout << "sum" << endl;
    cout << "logic" << endl;
    cout << "exit" << endl;
}

void create_group()
{

}


void menu()
{
    string buf;

    while(1)
    {
        getline(cin, buf);

        if(buf=="create group"||buf=="cg")
        {
            create_group();
        }
        else
        if(buf=="create student"||buf=="cs")
        {
            create_student();
        }
        else
        if(buf=="connect"||buf=="cn")
        {
            connect();
        }
        else
        if(buf=="min max")
        {
            d_min_max();
        }
        if(buf=="display group"||buf=="dg")
        {
            display_group();
        }
        else
        if(buf=="sum")
        {
            sum();
        }
        else
        if(buf=="logic")
        {
            logic();
        }
        else
        if(buf=="q"||buf=="quit"||buf=="exit")
        {
            return;
        }
        else
        {
            cout << "Unknown command" << endl;
        }
    }
}

#endif
