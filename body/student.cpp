/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 11.03.2018
*/

#ifndef STUDENT_CPP
#define STUDENT_CPP
#define DEBUG

#include <iostream>
#include <limits>
#include "../headers/student.h"

//functions

int load_again(unsigned int *tmp)
{
    while(!cin)
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Something went wrong, try again (or end program writing '0'): ";

        cin >> *tmp;
        if(cin && *tmp==0)
        {
            #ifdef DEBUG
            cout << "Succeed fail: load_again(unsigned int *tmp)" << endl;
            #endif
            return 1;
        }
    }

    #ifdef DEBUG
    cout << "Succeed: load_again(unsigned int *tmp)" << endl;
    #endif

    return 0;
}

int load_again(string *tmp)
{
    while(!cin)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Something went wrong, try again (or end program writing 'NULL'): ";
        cin >> *tmp;
        if(cin && *tmp=="NULL")
        {
            #ifdef DEBUG
            cout << "Succeed fail: load_again(string *tmp)" << endl;
            #endif
            return 1;
        }
    }
    #ifdef DEBUG
    cout << "Succeed: load_again(string *tmp)" << endl;
    #endif

    return 0;
}

int add(Student *st, S_group *sgr)
{
    string n, sn;
    unsigned int ix;

    cout << "Please specify:" << endl;
    cout << "Name: ";
    getline(cin, n);
    if(load_again(&n))
    {
        #ifdef DEBUG
        cout << "Succeed fail: add(Student *st, S_group *sgr)" << endl;
        #endif
        return 1;
    }

    cout << "Surname: ";
    getline(cin, sn);
    if(load_again(&sn))
    {
        #ifdef DEBUG
        cout << "Succeed fail: add(Student *st, S_group *sgr)" << endl;
        #endif
        return 1;
    }

    cout << "Index: ";
    cin >> ix;
    if(load_again(&ix))
    {
        #ifdef DEBUG
        cout << "Succeed fail: add(Student *st, S_group *sgr)" << endl;
        #endif
        return 1;
    }

    // real program

    if(sgr->pnt_child!=NULL)
    {
        cout << "hej" << endl;

        Student *tmp, *tmp2;
        tmp2=new Student;

        tmp=st->pnt_next;
        st->pnt_next=tmp2;
        tmp2->pnt_back=st;
        tmp2->pnt_next=tmp;
        tmp->pnt_back=tmp2;

        tmp2->name=n;
        tmp2->surname=sn;
        tmp2->index=ix;

        #ifdef DEBUG
        cout << "Succeed: add(Student *st, S_group *sgr)/sgr->pnt_child!=NULL" << endl;
        #endif

    }
    else
    {

        st->pnt_belong=sgr;
        sgr->pnt_child=st;

        #ifdef DEBUG
        cout << "Succeed: add(Student *st, S_group *sgr)/sgr->pnt_child==NULL" << endl;
        #endif
    }

    #ifdef DEBUG
    cout << "Succeed: add(Student *st, S_group *sgr)" << endl;
    #endif

    return 0;
}

// class functions

Student::Student(string n, string sn, unsigned int ix)
:pnt_belong(NULL), pnt_next(NULL), pnt_back(NULL)
{
    name=n;
    surname=sn;
    index=ix;


    #ifdef DEBUG
    cout << "Create Student:" << name << " " << surname << " " << index << endl;
    #endif
}

Student::~Student()
{
    Student *tmp;
    S_group *stmp;

    if(this->pnt_back==NULL&&this->pnt_next==NULL)
    {
        stmp=this->pnt_belong;
        stmp=NULL;
        delete this;
        return;
    }
    if(this->pnt_back!=NULL)
    {
        tmp=this->pnt_back;
        tmp->pnt_next=this->pnt_next;
    }

    if(this->pnt_next!=NULL)
    {
        tmp=this->pnt_next;
        tmp->pnt_back=this->pnt_back;
    }

    if(this->pnt_belong!=NULL)
    {
        if(this->pnt_next!=NULL)
        {
            tmp=this->pnt_next;
            tmp->pnt_belong=this->pnt_belong;
            stmp=this->pnt_belong;
            stmp->pnt_child=tmp;
        }
        else
        {
            #ifdef DEBUG
            cout << "Fail: Student::~Student()/this->pnt_next==NULL" << endl;
            #endif
        }

    }

    delete this;

    #ifdef DEBUG
    cout << "Delete Student:" << name << " " << surname << " " << index << endl;
    #endif
}

S_group::S_group(string n)
:pnt_next(NULL), pnt_back(NULL)
{
    name=n;

    pnt_child=new Student;
    pnt_child->pnt_belong=this;
    if(add(pnt_child, this))
    {
        cout << "Empty group" << endl;
    }

    #ifdef DEBUG
    cout << "Create S_group:" << name << endl;
    #endif
}

S_group::~S_group()
{
    Student *tmp, *tmp2;
    S_group *stmp;
    tmp=this->pnt_child;

    while(tmp!=NULL)
    {
        tmp2=tmp->pnt_next;
        tmp->~Student();
        tmp=tmp2;
        #ifdef DEBUG
        cout << "Succeed delete: S_group::~S_group()" << name << endl;
        #endif

    }

    if(this->pnt_back!=NULL)
    {
        stmp=this->pnt_back;
        stmp->pnt_next=this->pnt_next;
    }

    if(this->pnt_next!=NULL)
    {
        stmp=this->pnt_next;
        stmp->pnt_back=this->pnt_back;
    }


    delete this;
    #ifdef DEBUG
    cout << "Delete S_group:" << name << endl;
    #endif
}

#endif // STUDENT_CPP

