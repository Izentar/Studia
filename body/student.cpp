/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 14.03.2018
*/

#ifndef STUDENT_CPP
#define STUDENT_CPP
#define DEBUG

#include <iostream>
#include <limits>
#include "../headers/student.h"

static vector <Student *> stud_all;
static vector <S_group *> gr_all;
static unsigned long int MAX_STUD = stud_all.max_size()/LESS_VECTOR;
static unsigned long int MAX_GR = gr_all.max_size()/LESS_VECTOR;

//overload



//functions

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

int find_v(S_group* , Student* what)
{

}

int load_again(unsigned int* const tmp)
{
    while(!cin)
    {

        cin.clear();
        sweep();    // must be

        cout << "Something went wrong, try again (or end program writing '0'): ";

        cin >> *tmp;
        sweep();    // must be
        if(cin && *tmp==0)
        {
            #ifdef DEBUG
            cout << "Succeed fail: load_again(unsigned int *tmp)" << endl;
            #endif
            return true;
        }
    }

    #ifdef DEBUG
    cout << "Succeed: load_again(unsigned int *tmp)" << endl;
    #endif

    return false;
}

int load_again(string* const tmp)
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

int entitle (string* const n, string* const sn, unsigned int* const ix)
{

    string tmp2;
    cout << "Please specify:" << endl;
    cout << "Name: ";
    getline(cin, *n);
    if(load_again(n))
    {
        #ifdef DEBUG
        cout << "Succeed fail: add(Student *st, S_group *sgr)" << endl;
        #endif
        return true;
    }

    cout << "Surname: ";
    getline(cin, *sn);
    if(load_again(sn))
    {
        #ifdef DEBUG
        cout << "Succeed fail: add(Student *st, S_group *sgr)" << endl;
        #endif
        return true;
    }

    cout << "Index: ";
    cin >> *ix;
    sweep();    //must be
    if(load_again(ix))
    {
        #ifdef DEBUG
        cout << "Succeed fail: add(Student *st, S_group *sgr)" << endl;
        #endif
        return true;
    }

    #ifdef DEBUG
    cout << "Succeed: entitle (string *n, string *sn, unsigned int *ix)" << endl;
    #endif

    return false;
}

// class functions

int connect(Student* const st, S_group* const sgr)
{

    st->pnt_belong.push_back(sgr);
    sgr->pnt_child.push_back(st);

    #ifdef DEBUG
    cout << "Succeed: connect(Student *st, S_group *sgr)" << endl;
    #endif

    return false;
}

unsigned int S_group::index_min_max()
{
    unsigned int MIN=numeric_limits<int>::max();
    unsigned int MAX=0;

    for (int i=0; i<this->pnt_child.size(); i++)
    {

    }
}

Student* create (S_group* const sgr)
{
    if(stud_all.size()>MAX_STUD)
    {
        cout << "Max capacity" << endl;
        return nullptr;
    }

    Student *tmp;
    tmp=new Student;

    if(connect(tmp, sgr))
    {
        delete tmp;
        return nullptr;
    }

    #ifdef DEBUG
    cout << "Succeed: create (S_group *sgr)" << endl;
    #endif

    return tmp;
}

Student::Student(string n, string sn, unsigned int ix)
{
    if(stud_all.size()>MAX_STUD)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    string nt, snt;
    unsigned int ixt;
    if(entitle(&nt, &snt, &ixt))
    {
        cout << "Program can not perform this operation (names set to default)" << endl;
        name=n;
        surname=sn;
        index=ix;
    }
    else
    {
        name=nt;
        surname=snt;
        index=ixt;
    }


    stud_all.push_back(this);

    #ifdef DEBUG
    cout << "Created Student:" << "Name-> " << name << " Surname-> " << surname << " Index-> " << index << endl;
    cout << "STUD_ALL " << stud_all[stud_all.size()-1]->name << endl;
    #endif
}

Student::~Student()     // usunięcie studenta z gupy
{
    int tmp;
    if((tmp=find_v(stud_all, this))!=-1)
    {
        #ifdef DEBUG
        cout << endl << "STUD_ALL ERASE " << stud_all[tmp]->name << endl;
        #endif
        stud_all.erase(stud_all.begin()+tmp);
    }
    else
    {
        #ifdef DEBUG
        cout << "In| ~Student() | could not find a pair" << endl;
        #endif
    }

    if((tmp=find_v(this->pnt_belong, this)))

    #ifdef DEBUG
    cout << "Delete Student:" << name << " " << surname << " " << index << endl;
    #endif
}

S_group::S_group(string n)
{
    if(gr_all.size()>MAX_GR)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    string tmp;
    cout << "Enter the name: ";
    getline(cin, tmp);
    if(load_again(&tmp))
    {
        cout << "Program can not perform this operation (names set to default)" << endl;
        name=n;
    }
    else
    {
        name=tmp;
    }

    gr_all.push_back(this);

    #ifdef DEBUG
    cout << "Created S_group :" << name << endl;
    #endif
}

S_group::~S_group()
{
    int tmp;
    if((tmp=find_v(gr_all, this))!=-1)
    {
        #ifdef DEBUG
        cout << endl << "GR_ALL ERASE " << gr_all[tmp]->name << endl;
        #endif
        gr_all.erase(gr_all.begin()+tmp);
    }
    else
    {
        #ifdef DEBUG
        cout << "In| ~S_group() | could not find a pair" << endl;
        #endif
    }


    #ifdef DEBUG
    cout << "Delete S_group:" << name << endl;
    #endif
}

#endif // STUDENT_CPP

