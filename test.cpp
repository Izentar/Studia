#ifndef TEST_CPP
#define TEST_CPP


#include <iostream>
#include <fstream>
/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 23.03.2018
*/

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
int int_tmp_gr, int_tmp_st;


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

    cout << "Allocation complete" << endl;

    for (unsigned int i=0; i<repeat; i++)
    {
        connect(*sgp[i], *sp[i]);
    }

    cout << "Connect complete" << endl;

    for (unsigned int i=0; i<repeat-1; i++)
    {
        *sgp[repeat+i]+=*sgp[i];
        *sgp[repeat+i]=*sgp[i]+*sgp[i+1];
        *sgp[repeat+i]*=*sgp[i];
        *sgp[repeat+i]=*sgp[i]**sgp[i+1];
    }

    cout << "Logic and sum complete" << endl;

    for (unsigned int i=0; i<repeat; i++)
    {
        cout << *sgp[i] << " " << *sp[i] << endl;
    }

    cout << "Cout complete" << endl;

    for (unsigned int i=0; i<repeat; i++)
    {
        sgp[i]->display_min_max();
    }

    cout << "Min-Max complete" << endl;

    for (unsigned int i=0; i<repeat; i++)
    {
        delete sp[i];
        delete sgp[i];
    }

    for (unsigned int i=0; i<repeat; i++)
    {
        delete sgp[repeat+i];
    }

    cout << "Delete complete" << endl;

    return false;
}

//  exist only here
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
//

inline void sweep ()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

inline void pop_space(string& tmp)
{
    if(tmp.size()==0)
    {
        return;
    }

    for (unsigned int i=tmp.size()-1; i>=0; i--)
    {
        if(tmp[i]==' ')
        {
            tmp.pop_back();
        }
        else
        {
            return;
        }
    }
    return;
}

int if_repeated_st (const string& ind)      // generally
{
    for (unsigned int i=0; i<stud_all.size(); i++)
    {
        if(stud_all[i]->index==ind)
        {
            #ifdef DEBUG
            cout << "This person already exist here: " << ind << endl;
            #endif
            return i;
        }
    }

    #ifdef DEBUG
    cout << "Succeed: if_repeated" << endl;
    #endif

    return -1;
}

int if_repeated_gr (const string& na)     // generally
{
    for (unsigned int i=0; i<gr_all.size(); i++)
    {
        if(gr_all[i]->name==na)
        {
            #ifdef DEBUG
            cout << "This person already exist here: " << na << endl;
            #endif
            return i;
        }
    }

    #ifdef DEBUG
    cout << "Succeed: if_repeated" << endl;
    #endif

    return -1;
}

/*bool load_again(string &tmp)
{
    while(!cin)
    {
        cin.clear();
        sweep();    //must be

        cout << "Something went wrong, try again (or end program writing 'NULL'): ";
        cin >> tmp;
        if(cin && tmp=="NULL")
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
}*/

inline bool indEX()    // int_tmp_st
{
    cout << "Index: ";
    getline(cin, ind);
    pop_space(ind);
    /*if(load_again(ind))
    {
        return true;
    }*/

    if((int_tmp_st=if_repeated_st(ind))==-1)
    {
        return true;
    }

    return false;
}

inline bool gr_naME()  // int_tmp_gr
{
    cout << "Group name: ";
    getline(cin, gr_na);
    pop_space(gr_na);
    /*if(load_again(gr_na))
    {
        return true;
    }*/

    if((int_tmp_gr=if_repeated_gr(gr_na))==-1)
    {
        return true;
    }
    return false;
}

inline bool naME()
{
    cout << "Student name: ";
    getline(cin, na);
    pop_space(na);
    /*if(load_again(na))
    {
        return true;
    }*/
    return false;
}

inline bool surnaME()
{
    cout << "Student surname: ";
    getline(cin, surna);
    pop_space(surna);
    /*if(load_again(surna))
    {
        return true;
    }*/
    return false;
}

inline void conn()
{
    if(gr_naME())
    {
        cout << "Cannot found" << endl;
        return;
    }

    if(indEX())
    {
        cout << "Cannot found" << endl;
        return;
    }
    if(connect(*gr_all[int_tmp_gr], *stud_all[int_tmp_st]))
    {
        cout << "Already connected" << endl;
    }

    #ifdef DEBUG
    cout << "Succeed: connect(Student *st, S_group *sgr)" << endl;
    #endif

    return;
}

inline void create_group()
{
    if(gr_all.size()>MAX_GR)
    {
        cout << "You are approaching the border of memory" << endl;
        return;
    }
    if(gr_naME())
    {
        gr=new S_group(gr_na);
        gr_all.push_back(gr);
    }
    else
    {
        cout << "Group already exist" << endl;
    }
}

inline void create_student()
{
    if(stud_all.size()>MAX_STUD)
    {
        cout << "You are approaching the border of memory" << endl;
        return;
    }
    if(indEX())
    {
        naME();
        surnaME();

        st=new Student(na, surna, ind);
        stud_all.push_back(st);
    }
    else
    {
        cout << "Student already exist" << endl;
    }
}

inline void d_min_max ()
{
    if(gr_naME())
    {
        cout << "There is no such a group" << endl;
        return;
    }

    gr_all[int_tmp_gr]->display_min_max();
}

inline void display_group()
{
    cout << "Which group would you like to see? ";
    if(gr_naME())
    {
        cout << "There is no such a group" << endl;
        return;
    }

    cout << *gr_all[int_tmp_gr] << endl;
}

bool load_gr_3(string & tmp_gr_name, string & tmp_gr_name2, int & int_tmp, int & int_tmp2)
{
    if(gr_naME())
    {
        cout << "Cannot find it" << endl;
        return true;
    }
    tmp_gr_name=gr_na;
    int_tmp=int_tmp_gr;

    cout << "and ";
    if(gr_naME())
    {
        cout << "Cannot find it" << endl;
        return true;
    }
    tmp_gr_name2=gr_na;
    int_tmp2=int_tmp_gr;

    if(tmp_gr_name==tmp_gr_name2)
    {
        cout << "Same groups" << endl;
        return true;
    }
    return false;
}

inline void sum()
{
    string tmp_gr_name, tmp_gr_name2;
    int int_tmp, int_tmp2;

    if(load_gr_3(tmp_gr_name, tmp_gr_name2, int_tmp, int_tmp2))
    {
        return;
    }

    cout << "Where want you store it?" << endl;

    if(gr_naME())
    {
        if(gr_all.size()>MAX_GR)
        {
            cout << "You are approaching the border of memory" << endl;
            return;
        }

        gr=new S_group(gr_na);
        gr_all.push_back(gr);

        *gr=*gr_all[int_tmp]+*gr_all[int_tmp2];
    }
    else
    {
        if(gr_na==tmp_gr_name)
        {
            *gr_all[int_tmp]+=*gr_all[int_tmp2];
        }
        else
        if(gr_na==tmp_gr_name2)
        {
            *gr_all[int_tmp2]+=*gr_all[int_tmp];
        }
    }

}

inline void logic()
{
    string tmp_gr_name, tmp_gr_name2, enter;
    int int_tmp, int_tmp2;

    if(load_gr_3(tmp_gr_name, tmp_gr_name2, int_tmp, int_tmp2))
    {
        return;
    }

    cout << "Where want you store it?" << endl;

    if(gr_naME())
    {
        if(gr_all.size()>MAX_GR)
        {
            cout << "You are approaching the border of memory" << endl;
            return;
        }

        gr=new S_group(gr_na);
        gr_all.push_back(gr);

        *gr=*gr_all[int_tmp]**gr_all[int_tmp2];
    }
    else
    {
        if(gr_na==tmp_gr_name)
        {
            *gr_all[int_tmp]*=*gr_all[int_tmp2];
        }
        else
        if(gr_na==tmp_gr_name2)
        {
            *gr_all[int_tmp2]*=*gr_all[int_tmp];
        }
    }
}

inline void display_grs()
{
    cout << endl << "Groups:" << endl;
    for (unsigned int i=0; i<gr_all.size(); i++)
    {
        cout << *gr_all[i] << endl;
    }
}

inline void display_sts()
{
    cout << endl << "Students:" << endl;
    for (unsigned int i=0; i<stud_all.size(); i++)
    {
        cout << *stud_all[i] << endl;
    }
}

inline void delete_all()
{
    int tmpgr, tmpst;
    tmpst=stud_all.size();
    tmpgr=gr_all.size();

    for (int i=0; i<tmpst; i++)
    {
        #ifdef DEBUG
        cout << *stud_all[i] << endl;
        #endif
        delete stud_all[i];
    }

    for (int i=0; i<tmpgr; i++)
    {
        #ifdef DEBUG
        cout << *gr_all[i] << endl;
        #endif
        delete gr_all[i];
    }
    return;
}

void help()
{
    cout << "+ create group" << endl;
    cout << "+ create student" << endl;
    cout << "+ connect" << endl;
    cout << "+ min max" << endl;
    cout << "+ display group" << endl;
    cout << "+ sum" << endl;
    cout << "+ display" << endl;
    cout << "+ display students" << endl;
    cout << "+ logic" << endl;
    cout << "+ exit" << endl;
}



void menu()
{
    string buf;

    cout << "Welcome to S-G creator!" << endl << endl;

    while(1)
    {
        cout << "$$:";
        getline(cin, buf);
        pop_space(buf);

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
        else
        if(buf=="display"||buf=="d")
        {
            display_grs();
        }
        else
        if(buf=="display students"||buf=="ds")
        {
            display_sts();
        }
        else
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
        if(buf=="help")
        {
            help();
        }
        else
        if(buf=="q"||buf=="quit"||buf=="exit")
        {
            delete_all();
            return;
        }
        else
        {
            cout << "Unknown command" << endl;
        }
    }
}

#endif
