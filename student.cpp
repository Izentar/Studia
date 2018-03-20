/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 20.03.2018
*/


#ifndef STUDENT_CPP
#define STUDENT_CPP

#define DEBUG

#include <iostream>
#include <cstring>
#include "student.h"


ostream & operator<< (ostream& outgo, const Student &st)
{
    return outgo << "~Name: " << st.name << " ~Surname: " << st.surname << " ~Index: " << st.index;
}

ostream & operator<< (ostream& outgo, const S_group &gr)
{
    cout << "~Name: " << gr.name << endl;
    for (unsigned int i=0; i<gr.size; i++)
    {
        outgo << (gr.p[i]) << endl;
    }
    return outgo << "End" << endl;
}

S_group& S_group::operator= (const S_group &gr)
{
    if(this!=&gr)
    {
        if_min_max=gr.if_min_max;
        delete [] this->p;
        allocate(gr.size);
        for (unsigned int i=0; i<gr.size; i++)
        {
            p[i]=gr.p[i];
        }
    }
    return *this;
}

S_group S_group::operator+ (const S_group &gr) const
{
    unsigned int a=0;
    S_group temp("");
    temp.if_min_max=false;
    Student** pnt=new Student*[gr.size];
    for (unsigned int i=0; i<gr.size; i++)      // find the same
    {
        for (unsigned int j=0; j<size; j++)
        {
            if(gr.p[i]!=p[j])
            {
                pnt[a]=gr.p[i];
                a++;
                break;
            }
        }
    }
    temp.allocate(size+a);
    for (unsigned int i=0; i<size; i++) // copy
    {
        temp.p[i]=p[i];
    }

    for (unsigned int i=0; i<a; i++)
    {
        temp.p[size+i]=pnt[i];
    }

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
    S_group temp("");
    temp.if_min_max=false;
    Student** pnt=new Student*[gr.size];
    for (unsigned int i=0; i<gr.size; i++)      // find the same
    {
        for (unsigned int j=0; j<size; j++)
        {
            if(gr.p[i]==p[j])
            {
                pnt[a]=gr.p[i];
                a++;
                break;
            }
        }
    }
    temp.allocate(size+a);

    for (unsigned int i=0; i<a; i++)
    {
        temp.p[i]=pnt[i];
    }

    return temp;
}

S_group& S_group::operator*= (const S_group &gr)
{
    *this=(*this*gr);
    return *this;
}

S_group::S_group(string na)
:if_min_max(false), name(na), p(nullptr), min_val(""), max_val(""), size(0)
{
    cout << "S_group created: " << na << endl;
}

S_group::S_group(const S_group& gr)
{
    if(this!=&gr)
    {
        delete this->p;
        if_min_max=gr.if_min_max;
        allocate(gr.size);
        for(unsigned int i=0; i<gr.size; i++)
        {
            p[i]=gr.p[i];
        }
        name=gr.name;
    }

    cout << "S_group copied: " << gr.name << endl;
}

S_group::~S_group()
{
    cout << "S_group delete: " << name << endl;
    delete [] p;
}

Student::Student(string nam, string surnam, char* ind)
:name(nam), surname(surnam)
{
    allocate();
    strcpy(index, ind);
    cout << "Student created: " << this->name << " " << this->surname << " " << this->index << endl;
}

Student::~Student()
{
    cout << "Student deleted: " << this->name << " " << this->surname << " " << this->index << endl;
    delete index;
}

void S_group::set_min_max()
{
    if(if_min_max==false)
    {
        char min_v[INDEX];
        char max_v[INDEX];

        if(size==0)
        {
            max_v[0]='\0';
            min_v[0]='\0';
        }
        else
        {
            strcpy(min_v, p[0]->index);
            strcpy(max_v, p[0]->index);
        }

        for (unsigned int i=1; i<size; i++)
        {
            if(strcmp(min_v, p[i]->index)>0)
            {
                strcpy(min_v, p[i]->index);
            }

            if(strcmp(max_v, p[i]->index)<0)
            {
                strcpy(max_v, p[i]->index);
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

    cout << "Min value: ";
    for (unsigned int i=0; min_val[i]!='\0'; i++)
    {
        cout << min_val[i];
    }

    cout << "  Max value: ";
    for (unsigned int i=0; max_val[i]!='\0'; i++)
    {
        cout << max_val[i];
    }
}

void S_group::cpy_nalloc(S_group& gr)
{
    if(this!=&gr)
    {
        if_min_max=false;
        for(unsigned int i=0; i<gr.size; i++)
        {
            p[i]=gr.p[i];
        }
    }

    cout << "S_group copied (NK): " << gr.name << endl;
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
    gr.allocate(temp.size+1);
    gr.cpy_nalloc(temp);
    gr.p[gr.size]=&st;
    gr.size++;

    return false;
}


#endif
