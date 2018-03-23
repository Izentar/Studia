/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 23.03.2018
*/


#ifndef STUDENT_CPP
#define STUDENT_CPP

#define DEBUG

#include <iostream>
#include <cstring>
#include "student.h"


int find_t(const S_group &gr, const Student *p)
{
    for (unsigned int i=0; i<gr.size; i++)
    {
        if(gr.p[i]==p)
        {
            #ifdef DEBUG
            cout << "Founded " << i << endl;
            #endif
            return i;
        }
    }
    return -1;
}

ostream & operator<< (ostream& outgo, const Student &st)
{
    return outgo << "~Name: " << st.name << " ~Surname: " << st.surname << " ~Index: " << st.index;
}

ostream & operator<< (ostream& outgo, const S_group &gr)
{
    cout << "~Name: " << gr.name << endl;
    for (unsigned int i=0; i<gr.size; i++)
    {
        if(gr.p[i]!=nullptr)
        {
            cout << *(gr.p[i]) << endl;
        }

    }
    return outgo << "End" << endl;
}

S_group& S_group::operator= (const S_group &gr)
{
    if(this!=&gr)
    {
        if_min_max=gr.if_min_max;
        delete [] p;
        p=nullptr;
        allocate(gr.size);
        for (unsigned int i=0; i<gr.size; i++)      // copy pointers
        {
            p[i]=gr.p[i];
        }
        min_val=gr.min_val;
        max_val=gr.max_val;
    }
    return *this;
}

S_group S_group::operator+ (const S_group &gr) const
{
    unsigned int a=0;
    S_group temp("TEMPORARY");
    temp.if_min_max=false;
    Student** pnt=new Student*[size];

    for (unsigned int i=0; i<size; i++)      // find different
    {
        if(find_t(gr, p[i])==-1)
        {
            pnt[a]=p[i];
            a++;
        }

        /*for (unsigned int j=0; j<size; j++)
        {
            if(gr.p[i]==p[j])
            {
                continue;
            }
            else
            {
                pnt[a]=gr.p[i];
                a++;
                break;
            }
        }*/
    }


    temp.allocate(gr.size+a);
    for (unsigned int i=0; i<gr.size; i++) // copy
    {
        temp.p[i]=gr.p[i];
    }

    for (unsigned int i=0; i<a; i++)        // the different
    {
        temp.p[gr.size+i]=pnt[i];
    }


    delete [] pnt;
    return temp;
}

S_group& S_group::operator+= (const S_group &gr)
{
    *this=(*this+gr);
    return *this;
}

S_group S_group::operator* (const S_group &gr) const
{
    unsigned int a=0;
    S_group temp("TEMPORARY");
    Student** pnt=new Student*[size];
    for (unsigned int i=0; i<size; i++)      // find the same
    {
        if(find_t(gr, p[i])!=-1)
        {
            pnt[a]=p[i];
            a++;
        }

        /*for (unsigned int j=0; j<size; j++)
        {
            if(gr.p[i]==p[j])
            {
                pnt[a]=gr.p[i];
                a++;
                break;
            }
        }*/
    }
    temp.allocate(a);

    for (unsigned int i=0; i<a; i++)    // copy the same
    {
        temp.p[i]=pnt[i];
    }

    delete [] pnt;
    return temp;
}

S_group& S_group::operator*= (const S_group &gr)
{
    *this=(*this*gr);
    return *this;
}

S_group::S_group(string na)
:name(na), p(nullptr), min_val("0"), max_val("0")
{
    if_min_max=false;
    size=0;

    cout << "S_group created: " << na << " if_min_max, min_val, max_val" <<   endl;
}

S_group::S_group(const S_group& gr)
{
    if_min_max=gr.if_min_max;
    allocate(gr.size);
    for(unsigned int i=0; i<gr.size; i++)
    {
        p[i]=gr.p[i];
    }
    name=gr.name;
    min_val=gr.min_val;
    max_val=gr.max_val;

    cout << "S_group copied: " << gr.name << " if_min_max, min_val, max_val" << endl;
}

S_group::~S_group()
{
    cout << "S_group delete: " << name << " if_min_max, min_val, max_val, p" << endl;
    delete &size;
    delete &if_min_max;
    delete [] p;
    p=nullptr;
}

Student::Student(string nam, string surnam, string ind)
:name(nam), surname(surnam), index(ind)
{
    cout << "Student created: " << this->name << " " << this->surname << " " << this->index << endl;
}

Student::~Student()
{
    cout << "Student deleted: " << this->name << " " << this->surname << " " << this->index << endl;
}

void S_group::set_min_max()
{
    if(if_min_max==false)
    {
        if(size==0)
        {
            max_val="0";
            min_val="0";
        }
        else
        {
            min_val=p[0]->index;
            max_val=p[0]->index;
        }

        for (unsigned int i=1; i<size; i++)
        {
            if(min_val>p[i]->index)
            {
                min_val=p[i]->index;
            }

            if(max_val<p[i]->index)
            {
                max_val=p[i]->index;
            }
        }
        if_min_max=true;
    }
}

void S_group::display_min_max()
{
    if(if_min_max==false)
    {
        this->set_min_max();
    }

    cout << "Min value: " << min_val;
    cout << "  Max value: " << max_val << endl;
}

void S_group::cpy_nalloc_ptr(S_group& gr)
{
    if(this!=&gr)
    {
        if_min_max=gr.if_min_max;
        for(unsigned int i=0; i<gr.size; i++)
        {
            p[i]=gr.p[i];
        }
    }

    cout << "S_group copied (CNP): " << gr.name << endl;
}

bool connect(S_group& gr, Student& st)
{
    for (unsigned int i=0; i<gr.size; i++)
    {
        if(gr.p[i]==&st)
        {
            return true;
        }
    }

    S_group temp(gr);
    delete [] gr.p;
    gr.p=nullptr;
    gr.allocate(temp.size+1);
    gr.cpy_nalloc_ptr(temp);
    gr.p[gr.size-1]=&st;

    return false;
}


#endif
