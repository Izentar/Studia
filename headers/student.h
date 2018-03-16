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
int load_again(int* tmp);
int load_again(string *tmp);
void menu();
void help();

bool total_saving();
bool total_reading();

class S_group;

class Student
{
    string name;
    string surname;
    unsigned int index;
    vector <S_group *> pnt_belong;

    // functions dont needed for student (but they need variables)

    friend int if_repeated (string na, string surna, unsigned int ind);
    friend int if_repeated (unsigned int ind);
    friend S_group  operator+ (const S_group &gr, const S_group &gr2);


    public:
        Student(string="Undef", string="Undef", unsigned int=0);
        ~Student();

        friend class S_group;
        friend ostream & operator<< (ostream& outgo, const Student &st);
        friend ostream & operator<< (ostream& outgo, const vector <Student *> &st);

        friend int connect(Student *st, S_group *sgr);
        friend Student* create (S_group *sgr);
        friend int entitle (string* n, string* sn, unsigned int* ix);
        friend int if_repeated_gr (S_group const gr, Student* const st);
        friend void disconnect (Student* const st, S_group* const sgr);
        friend void delete_all();
        int delete_student(string &name, string &surname, unsigned int &index);

        friend inline void display_st_pnt();
        friend inline void display_st();

        friend bool total_saving();
        friend bool total_reading();

};

class S_group
{
    string name;
    vector <Student *> pnt_child;
    unsigned int min_val;
    unsigned int max_val;
    bool if_min_max;    // false - not sorted

    // functions dont needed for S_group (but they need variables)

    friend int if_repeated (string na);

    public:


        S_group(string="S_Undef");
        ~S_group();

        friend Student::~Student();
        friend ostream & operator<< (ostream& outgo, const S_group &gr);
        friend ostream & operator<< (ostream& outgo, const vector <S_group *> &gr);
        S_group & operator= (const S_group &gr);
        S_group & operator+ (const S_group &gr);
        S_group & operator+= (const S_group &gr);
        S_group & operator* (const S_group &gr);
        S_group & operator*= (const S_group &gr);


        friend int connect(Student *st, S_group *sgr);
        friend Student* create (S_group *sgr);
        friend int if_repeated_gr (S_group const gr, Student* const st);
        friend void disconnect (Student* const st, S_group* const sgr);
        friend void delete_all();
        void index_min_max ();
        int delete_group(string &na);
        inline void rename(string* const na);

        friend inline void display_gr_pnt();
        friend inline void display_gr();
        friend inline void sum_gr();
        friend inline void logical_gr();

        friend bool total_saving();
        friend bool total_reading();

        //int cpm();

};

#endif // STUDENT_H
