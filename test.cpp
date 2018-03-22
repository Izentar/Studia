#ifndef TEST_CPP
#define TEST_CPP


#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "test.h"

static vector <Student *> stud_all;
static vector <S_group *> gr_all;
static unsigned long int MAX_STUD = stud_all.max_size()/LESS_VECTOR;
static unsigned long int MAX_GR = gr_all.max_size()/LESS_VECTOR;
string na, surna, ind, gr_na;
Student *st;
S_group *gr;
int int_tmp;


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

inline void sweep ()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int find_v(vector <Student *> st, Student* what)
{
    for (unsigned int i=0; i<st.size(); i++)
    {
        if(st[i]==what)
        {
            #ifdef DEBUG
            cout << "Founded " << i << endl;
            #endif
            return i;
        }
    }
    return -1;
}

int find_v(vector <S_group *> gr, S_group* what)
{
    for (unsigned int i=0; i<gr.size(); i++)
    {
        if(gr[i]==what)
        {
            #ifdef DEBUG
            cout << "Founded " << i << endl;
            #endif
            return i;
        }
    }
    return -1;
}

int load_again(string &tmp)
{
    while(!cin)
    {
        cin.clear();
        sweep();    //must be

        cout << "Something went wrong, try again (or end program writing 'NULL'): ";
        cin >> *tmp;
        if(cin && *tmp=="NULL")
        {
            #ifdef DEBUG
            cout << "Succeed fail: load_again(string *tmp)" << endl;
            #endif
            return true;
        }
    }
    #ifdef DEBUG
    cout << "Succeed: load_again(string *tmp)" << endl;
    #endif

    return false;
}

int conn()
{
    cout << "Index: ";
    getline(cin, ind);
    load_again(ind);

    if((int_tmp=find_v(stud_all, ))==-1)
    {
        cout << "Cannot find" << endl;
    }

    cout << "Group name: ";
    getline(cin, gr_na);
    load_again(gr_na)

    if((int_tmp=find_v(gr_all))==-1)
    {
        cout << "Cannot find" << endl;
    }

    #ifdef DEBUG
    cout << "Succeed: connect(Student *st, S_group *sgr)" << endl;
    #endif

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
            conn();
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
