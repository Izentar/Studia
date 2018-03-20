#ifndef TEST_CPP
#define TEST_CPP


#include <iostream>
#include <fstream>
#include "test.h"

bool test(unsigned int repeat)
{
    string a, b, t;
    char c[INDEX];
    Student ABE( "Ala", "ma", "252");
    S_group ISC("jak");

    Student *sp[repeat];
    S_group *sgp[repeat*2];

    for (unsigned int i=0; i<repeat; i++)
    {
        a="S";
        b="G";
        c[0]='G';
        t=to_string(i);
        a+=t;
        b+=t;
        for (int j=1; j<INDEX; j++)
        {
            c[j]=static_cast<char>(i+j);
        }
        sp[i]=new Student(a, a, c);
        sgp[i]=new S_group(b);
    }



    for (unsigned int i=0; i<repeat; i++)
    {
        delete sp[i];
        delete sgp[i];
    }

    return false;
}



#endif
