/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 14.03.2018
*/

#ifndef STUDENT_H
#define STUDENT_H

#define LESS_VECTOR 1000

#include <iostream>
#include <vector>

using namespace std;



int load_again(unsigned int *tmp);
int load_again(string *tmp);

class S_group;

class Student
{
    string name;
    string surname;
    unsigned int index;
    vector <S_group *> pnt_belong;

    public:
        Student(string="Undef", string="Undef", unsigned int=0);
        ~Student();

        friend int connect(Student *st, S_group *sgr);
        friend Student* create (S_group *sgr);
        friend int entitle (string* const n, string* const sn, unsigned int* const ix);
};

class S_group
{
    string name;
    vector <Student *> pnt_child;

    public:
        S_group(string="S_Undef");
        ~S_group();

        friend int connect(Student *st, S_group *sgr);
        friend Student* create (S_group *sgr);
        unsigned int index_min_max ();
        //int cpm();

};

bool operator==(const Student &st, const Student &st2);

/*
vector <Student *> stud_all;
vector <S_group *> gr_all;
const unsigned long int MAX_STUD = stud_all.max_size();
const unsigned long int MAX_GR = gr_all.max_size();
*/
#endif // STUDENT_H
