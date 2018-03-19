/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 19.03.2018
*/

#ifndef STUDENT_H
#define STUDENT_H

#define LESS_VECTOR 1000
//#define DEBUG

#include <iostream>
#include <vector>

using namespace std;

#ifdef FILES
//file functions

bool total_saving();
bool total_reading();
#endif // FILES


// menu functions

void menu();
inline void help();
inline void delete_all();
inline void create_gr();
inline void create_st();
inline void add_st();
inline void display_sts();
inline void display_grs();
inline void connecT ();
inline void display_st_pnt();
inline void display_gr_pnt();
inline void display_st();
inline void display_gr();
inline void sum_gr();
inline void logical_gr();
inline void change_gr_name();
inline void change_st_name();
inline void display_min_max();
inline void delete_st();
inline void delete_gr();
inline void sort_gr();
inline void delete_connection();






class S_group;

class Student
{
    string name;
    string surname;
    string index;
    vector <S_group *> pnt_belong;

    // functions do not needed for student (but they need variables)

    friend int if_repeated (const string& ind, int trash_student_index) ;
    friend S_group  operator+ (const S_group &gr, const S_group &gr2);


    public:
        Student(char, string="Undef_name", string="Undef_surname", string="0_Index");
        Student(char, string, string, string, string="Trash");
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
        friend inline void delete_connection();
        friend bool test();

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


    // functions do not needed for S_group (but they need variables)

    friend int if_repeated (const string& na, string trash_group_name);

    public:


        S_group(char, string="S_Undef");
        S_group(char, string, int);
        S_group(char, vector <Student *> &st, string);
        ~S_group();

        friend Student::~Student();
        friend ostream & operator<< (ostream& outgo, const S_group &gr);
        friend ostream & operator<< (ostream& outgo, const vector <S_group *> &gr);

        void operator= (const S_group &gr);
        S_group operator+ (const S_group &gr) const;
        void operator+= (const S_group &gr);
        S_group operator* (const S_group &gr) const;
        void operator*= (const S_group &gr);

        friend bool connect(Student& st, S_group& sgr);
        friend Student* create (S_group &sgr);
        friend void disconnect (Student& st, S_group& sgr);
        void index_min_max ();
        bool delete_group(string &na);
        inline void rename(string na);

        friend inline void display_gr_pnt();
        friend inline void display_gr();
        friend inline void sum_gr();
        friend inline void logical_gr();
        friend inline void change_gr_name();
        friend inline void display_min_max();
        friend inline void delete_connection();
        friend bool test();

        #ifdef FILES
        friend bool total_saving();
        friend bool total_reading();
        #endif
};


ostream & operator<< (ostream& outgo, const Student &st);
ostream & operator<< (ostream& outgo, const vector <Student *> &st);
bool connect(Student& st, S_group& sgr);
Student* create (S_group &sgr);
bool entitle (string& n, string& sn, string& ix);
void disconnect (Student& st, S_group& sgr);

bool test();


#endif // STUDENT_H
