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


void menu();
void help();

bool total_saving();
bool total_reading();

class S_group;

class Student
{
    string name;
    string surname;
    string index;
    vector <S_group *> pnt_belong;

    // functions dont needed for student (but they need variables)

    friend int if_repeated (const string& ind, int trash_student_index) ;
    friend S_group  operator+ (const S_group &gr, const S_group &gr2);


    public:
        Student(string="Undef", string="Undef", string="0");
        ~Student();

        friend class S_group;
        friend ostream & operator<< (ostream& outgo, const Student &st);
        friend ostream & operator<< (ostream& outgo, const vector <Student *> &st);

        friend bool connect(Student& st, S_group& sgr);
        friend Student* create (S_group &sgr);
        friend bool entitle (string& n, string& sn, string& ix);
        friend void disconnect (Student& st, S_group& sgr);
        bool delete_student(string &inde);

        friend inline void display_st_pnt();
        friend inline void display_st();
        friend inline void change_st_name();

        #ifdef FILES
        friend bool total_saving();
        friend bool total_reading();
        #endif
};

class S_group
{
    bool if_min_max;    // false - not sorted
    string name;
    vector <Student *> pnt_child;
    string min_val;
    string max_val;


    // functions dont needed for S_group (but they need variables)

    friend int if_repeated (const string& na, string trash_group_name);

    public:


        S_group(string="S_Undef");
        S_group(string, int);
        S_group(vector <Student *> &st, string);
        ~S_group();

        friend Student::~Student();
        friend ostream & operator<< (ostream& outgo, const S_group &gr);
        friend ostream & operator<< (ostream& outgo, const vector <S_group *> &gr);

        S_group &operator= (const S_group &gr);
        S_group operator+ (const S_group &gr) const;
        S_group &operator+= (const S_group &gr);
        S_group operator* (const S_group &gr) const;
        S_group &operator*= (const S_group &gr);

        /*S_group & operator= (const S_group &gr);
        S_group & operator+ (const S_group &gr);
        S_group & operator+= (const S_group &gr);
        S_group & operator* (const S_group &gr);
        S_group & operator*= (const S_group &gr);*/


        friend bool connect(Student& st, S_group& sgr);
        friend Student* create (S_group &sgr);
        friend void disconnect (Student& st, S_group& sgr);
        friend void delete_all();
        void index_min_max ();
        bool delete_group(string &na);
        inline void rename(string na);

        friend inline void display_gr_pnt();
        friend inline void display_gr();
        friend inline void sum_gr();
        friend inline void logical_gr();
        friend inline void change_gr_name();
        friend inline void display_min_max();

        #ifdef FILES
        friend bool total_saving();
        friend bool total_reading();
        #endif
};

#endif // STUDENT_H
