/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 20.03.2018
*/

#ifndef STUDENT_H
#define STUDENT_H

#define INDEX 12
//#define DEBUG

#include <iostream>

using namespace std;

class S_group;

class Student
{
    string name;
    string surname;
    string index;

    public:
        Student(string, string, string);
        ~Student();

        friend class S_group;

        friend ostream & operator<< (ostream& outgo, const Student &st);
        friend bool connect(S_group& gr, Student& st);

};


class S_group
{
    bool if_min_max;    // false - not sorted
    string name;
    Student** p;
    string min_val;
    string max_val;
    unsigned int size;
    void allocate(unsigned int siz) {p=new Student*[size=siz];}

    public:
        S_group(string);
        S_group(const S_group& gr);
        ~S_group();



        friend ostream & operator<< (ostream& outgo, const S_group &gr);
        friend bool connect(S_group& gr, Student& st);

        S_group& operator= (const S_group &gr);
        S_group operator+ (const S_group &gr) const;
        S_group& operator+= (const S_group &gr);
        S_group operator* (const S_group &gr) const;
        S_group& operator*= (const S_group &gr);


        void set_min_max();
        void display_min_max();
        void cpy_nalloc_ptr(S_group& gr);       // copy only pointers without allocation

};



#endif
