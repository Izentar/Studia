/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 14.03.2018
*/

/*
+ stworzenie funkcji mogącej usuwać przypisanie studenta do grupy
+ ogólne powtórzenie studenta, grupy
+ sprawdzenie powtórzenia w grupie studenta
+ wyświetlanie do kogo student, grupa jest przypisany
+ zmiana nazw
+ dodaj grupę
+ wypisywanie wszystkich grup/studentów
+ zmienić index z int na string
+ czy numer indeksu/grupy sie nie powtarza
+ możliwość zmiany parametrów studenta
+ wyświetlanie min-max
*/

#ifndef STUDENT_CPP
#define STUDENT_CPP
#define DEBUG

#include <iostream>
#include <limits>
#include <fstream>
#include "../headers/student.h"

static vector <Student *> stud_all;
static vector <S_group *> gr_all;
static unsigned long int MAX_STUD = stud_all.max_size()/LESS_VECTOR;
static unsigned long int MAX_GR = gr_all.max_size()/LESS_VECTOR;

//declaration

inline int find_v(const vector <Student *> st, const Student& what);
inline int find_v(const vector <S_group *> gr, const S_group& what);

//overload

ostream & operator<< (ostream& outgo, const Student &st)
{
    return outgo << "~Name: " << st.name << " ~Surname: " << st.surname << " ~Index: " << st.index;
}

ostream & operator<< (ostream& outgo, const S_group &gr)
{
    return outgo << "~Name: " << gr.name;
}

ostream & operator<< (ostream& outgo, const vector <Student *> &st)
{
    for (unsigned int i=0; i<st.size(); i++)
    {
        cout << "~Name: " << st[i]->name << " ~Surname: " << st[i]->surname << " ~Index: " << st[i]->index << endl;
    }

    return outgo << "End" << endl;
}

ostream & operator<< (ostream& outgo, const vector <S_group *> &gr)
{
    for (unsigned int i=0; i<gr.size(); i++)
    {
        cout << "~Name: " << gr[i]->name << endl;
    }

    return outgo << "End" << endl;
}

S_group & S_group::operator= (const S_group &gr)
{
    if_min_max=false;

    pnt_child.clear();

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)
    {
        pnt_child.push_back(gr.pnt_child[i]);
    }

    return *this;
}

S_group & S_group::operator+ (const S_group &gr)
{
    S_group tmp;
    Student *ind;

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)     //copy
    {
        tmp.pnt_child.push_back(gr.pnt_child[i]);
        ind=gr.pnt_child[i];
        ind->pnt_belong.push_back(&tmp);
    }

    for (unsigned int i=0; i<pnt_child.size(); i++)     // find the same pointers
    {
        if(find_v(gr.pnt_child, *pnt_child[i])==-1)  // not found
        {
            tmp.pnt_child.push_back(pnt_child[i]);
            ind=pnt_child[i];
            ind->pnt_belong.push_back(&tmp);
        }
    }

    return tmp;
}

S_group & S_group::operator+= (const S_group &gr)   //???
{
    Student *ind;
    if_min_max=false;

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)
    {
        if(find_v(pnt_child, *gr.pnt_child[i])==-1)  // not found
        {
            pnt_child.push_back(gr.pnt_child[i]);
            ind=gr.pnt_child[i];
            ind->pnt_belong.push_back(this);
        }
    }
    return *this;
}

S_group & S_group::operator* (const S_group &gr)
{
    S_group tmp;
    Student *ind;

    for (unsigned int i=0; i<pnt_child.size(); i++)     // find the same pointers
    {
        if(find_v(gr.pnt_child, *pnt_child[i])!=-1)  // found
        {
            tmp.pnt_child.push_back(pnt_child[i]);
            ind=pnt_child[i];
            ind->pnt_belong.push_back(&tmp);
        }
    }

    return tmp;
}

S_group & S_group::operator*= (const S_group &gr)   //???
{
    Student *ind;
    if_min_max=false;

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)
    {
        if(find_v(pnt_child, *gr.pnt_child[i])!=-1)  // found
        {
            pnt_child.push_back(gr.pnt_child[i]);
            ind=gr.pnt_child[i];
            ind->pnt_belong.push_back(this);
        }
    }
    return *this;
}


//file functions
#ifdef FILES
bool total_saving()     // first student then S_group
{
    fstream file;
    file.open("Save", ios::out | ios::trunc | ios::binary);

    if(file.good()==true)
    {
        #ifdef DEBUG
        cout << "Enter the file" << endl;
        #endif
    }


    for (unsigned int i=0; i<stud_all.size(); i++)
    {
        file.write(stud_all[i], sizeof(stud_all[i]));
    }

    for (unsigned int i=0; i<gr_all.size(); i++)
    {
        file.write(gr_all[i], sizeof(gr_all[i]));
    }

    file.close();
    #ifdef DEBUG
    cout << "File saved" << endl;
    #endif
}

bool total_reading()        // first student then S_group
{
    fstream file;
    file.open("Save", ios::in | ios::binary);

    if(file.good()==true)
    {
        #ifdef DEBUG
        cout << "Enter the file" << endl;
        #endif
    }

    for (unsigned int i=0; i<stud_all.size(); i++)
    {

    }

    file.close();
    #ifdef DEBUG
    cout << "File saved" << endl;
    #endif
}
#endif
//functions

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

bool load_again(string& tmp)
{
    if(tmp=="NULL")
    {
        #ifdef DEBUG
        cout << "load_again(string& tmp): Fail: NULL" << endl;
        #endif
        return true;
    }
    while(!cin)
    {
        cin.clear();
        sweep();

        cout << "Something went wrong, try again (or end program writing 'NULL'): ";
        cin >> tmp;
        if(cin && tmp=="NULL")
        {
            #ifdef DEBUG
            cout << "load_again(string* const tmp): Fail" << endl;
            #endif
            return true;
        }
        pop_space(tmp);
    }
    #ifdef DEBUG
    cout << "load_again(string& tmp): Succeed" << endl;
    #endif

    return false;
}

inline bool load(string& str, string problem)
{
    getline(cin, str);
    pop_space(str);
    if(load_again(str))
    {
        #ifdef DEBUG
        cout << problem << ": Fail" << endl;
        #endif
        return true;
    }
    return false;
}

inline int find_v(const vector <Student *> st,const  Student& what)     	//particularly
{
    for (unsigned int i=0; i<st.size(); i++)
    {
        if(st[i]==&what)
        {
            #ifdef DEBUG
            cout << "find_v(const vector <Student *> st, const Student& what): Founded " << i << endl;
            #endif
            return i;
        }
    }
    #ifdef DEBUG
    cout << "find_v(const vector <Student *> st, const Student& what): NOT founded "<< endl;
    #endif
    return -1;
}

inline int find_v(const vector <S_group *> gr, const S_group& what)     	//particularly
{
    for (unsigned int i=0; i<gr.size(); i++)
    {
        if(gr[i]==&what)
        {
            #ifdef DEBUG
            cout << "find_v(const vector <S_group *> gr, const S_group& what): Founded " << i << endl;
            #endif
            return i;
        }
    }
    #ifdef DEBUG
    cout << "find_v(const vector <S_group *> gr, const S_group& what): NOT founded "<< endl;
    #endif

    return -1;
}

int if_repeated (const string& ind, int trash_student_index)      // generally
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

int if_repeated (const string& na, string trash_group_name)     // generally
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

//
//

bool entitle (string& name, string& surname, string& index)        // general function
{
    do
    {
        cout << "Please specify:" << endl;
        cout << "Name: ";
        if(load(name, "entitle (string& name, string& surname, string& index)"))
        {
            return true;
        }

        cout << "surnamee: ";
        if(load(surname, "entitle (string& name, string& surname, string& index)"))
        {
            return true;
        }

        cout << "Index: ";
        if(load(index, "entitle (string& name, string& surname, string& index)"))
        {
            return true;
        }
    }
    while(if_repeated(index, 2)!=-1);



    #ifdef DEBUG
    cout << "entitle (string& name, string& surname, string& index): Succeed" << endl;
    #endif

    return false;
}

// class functions

inline void S_group::rename(string& na)
{
    string tmp;
    tmp=na;
    cout << "Enter the name: ";
    if(load(na, "Program cannot perform rename operation (names set to default)"))
    {
        if(if_repeated(na, "blabla")!=-1)
        {
            cout << "This name is occupied" << endl;
            na=tmp;
        }
    }

    #ifdef DEBUG
    cout << "rename: Succeed" << endl;
    #endif
    return;
}

bool Student::delete_student_dirty(string &inde)
{
    int tmp;
    if((tmp=if_repeated(inde, 2))!=-1)
    {
        delete stud_all[tmp];
    }
    else
    {
        cout << "Cannot find student" << endl;
        return true;
    }

    #ifdef DEBUG
    cout << "delete_student: Succeed" << endl;
    #endif

    return false;
}

bool S_group::delete_group_dirty(string &na)
{
    int tmp;
    if((tmp=if_repeated(na,"blabla"))!=-1)
    {
        delete gr_all[tmp];
    }
    else
    {
        cout << "Cannot find student" << endl;
        return true;
    }

    #ifdef DEBUG
    cout << "Succeed: delete_student" << endl;
    #endif

    return false;
}

bool connect(Student& st, S_group& sgr)
{
    if(find_v(sgr.pnt_child, st)!=-1)
    {
        cout << "It is already connected student/group" << endl;
        return true;
    }


    st.pnt_belong.push_back(&sgr);
    sgr.pnt_child.push_back(&st);

    sgr.if_min_max=false;

    #ifdef DEBUG
    cout << "connect(Student *st, S_group *sgr): Succeed" << endl;
    #endif

    return false;
}

void disconnect (Student& st, S_group& sgr)
{
    int tmpst, tmpgr;

    if((tmpgr=find_v(sgr.pnt_child, st))==-1)
    {
        #ifdef DEBUG
        cout << "disconnect (Student& st, S_group& sgr): Cannot find connection" << endl;
        #endif
    }
    else
    {
        sgr.pnt_child.erase(sgr.pnt_child.begin()+tmpgr);

        #ifdef DEBUG
        cout << "disconnect (Student& st, S_group& sgr): Delete Student pointer in group" << endl;
        #endif
    }

    if((tmpst=find_v(st.pnt_belong, sgr))==-1)
    {
        #ifdef DEBUG
        cout << "disconnect (Student& st, S_group& sgr): Cannot find connection" << endl;
        #endif
    }
    else
    {
        st.pnt_belong.erase(st.pnt_belong.begin()+tmpst);

        #ifdef DEBUG
        cout << "disconnect (Student& st, S_group& sgr): Delete Group pointer in Student" << endl;
        #endif
    }

    return;
}

void S_group::index_min_max()
{
    if(if_min_max==true)
    {
        cout << "The data is current" << endl;
        return;
    }

    if(pnt_child.size()==0)
    {
        cout << "The are no students in this group" << endl;
        return;
    }

    if_min_max=true;

    min_val=pnt_child[0]->index;
    max_val=pnt_child[0]->index;

    for (unsigned int i=0; i<pnt_child.size(); i++)
    {
        if(pnt_child[i]->index>max_val)
        {
            max_val=pnt_child[i]->index;
        }
        if(pnt_child[i]->index<min_val)
        {
            min_val=pnt_child[i]->index;
        }
    }

    #ifdef DEBUG
    cout << "S_group::index_min_max(): Succeed" << endl;
    #endif

    return;
}

Student* create (S_group& sgr)
{
    if(stud_all.size()>MAX_STUD)
    {
        cout << "Max capacity" << endl;
        return nullptr;
    }

    Student *tmp;
    tmp=new Student;

    if(connect(*tmp, sgr))
    {
        delete tmp;
        return nullptr;
    }

    #ifdef DEBUG
    cout << "create (S_group *sgr): Succeed" << endl;
    #endif

    return tmp;
}

Student::Student(string n, string sn, string ix)
{
    if(stud_all.size()>MAX_STUD)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    string nt, snt, ixt;
    if(entitle(nt, snt, ixt))
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

    cout << "Created Student:" << "Name-> " << name << " Surname-> " << surname << " Index-> " << index << endl;
    #ifdef DEBUG
    cout << "VECTOR STUD_ALL " << stud_all[stud_all.size()-1]->name << endl;
    #endif
}

Student::~Student()
{
    int tmp;
    if((tmp=find_v(stud_all, *this))!=-1)
    {
        #ifdef DEBUG
        cout << endl << "VECTOR STUD_ALL ERASE " << stud_all[tmp]->name << endl;
        #endif
        stud_all.erase(stud_all.begin()+tmp);
    }
    else
    {
        #ifdef DEBUG
        cout << "~Student(): ERROR could not find a pair" << endl;
        #endif
    }

    S_group *tmpgr;

    for (unsigned int i=0; i<this->pnt_belong.size(); i++)
    {
        tmpgr=this->pnt_belong[i];
        tmpgr->if_min_max=false;

        if((tmp=find_v(tmpgr->pnt_child, *this))!=-1)
        {
            #ifdef DEBUG
            cout << "Delete Student pointer in group" << endl;
            #endif
            tmpgr->pnt_child.erase(tmpgr->pnt_child.begin()+tmp);
        }
        else
        {
            #ifdef DEBUG
            cout << "ERROR Unable to delete Student pointer in group" << endl;
            #endif
        }
    }

    cout << "Delete Student:" << name << " " << surname << " " << index << endl;
}

S_group::S_group(string n)
:if_min_max(false), min_val(0), max_val(0)
{
    if(gr_all.size()>MAX_GR)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    string tmp;
    cout << "Enter the name: ";
    getline(cin, tmp);
    if(load_again(tmp))
    {
        cout << "Program can not perform this operation (names set to default)" << endl;
        name=n;
    }
    else
    {
        if(if_repeated(tmp, "blabla")!=-1)
        {
            cout << "This name is occupied (names set to default)" << endl;
            name=n;
        }

        name=tmp;
    }

    gr_all.push_back(this);

    cout << "Created S_group :" << name << endl;
}

S_group::~S_group()
{
    int tmp;
    if((tmp=find_v(gr_all, *this))!=-1)
    {
        #ifdef DEBUG
        cout << endl << "VECTOR GR_ALL ERASE " << gr_all[tmp]->name << endl;
        #endif
        gr_all.erase(gr_all.begin()+tmp);
    }
    else
    {
        #ifdef DEBUG
        cout << "~S_group(): ERROR could not find a pair" << endl;
        #endif
    }

    Student *tmpst;

    for (unsigned int i=0; i<this->pnt_child.size(); i++)
    {
        tmpst=this->pnt_child[i];

        if((tmp=find_v(tmpst->pnt_belong, *this))!=-1)
        {
            #ifdef DEBUG
            cout << "Delete Group pointer in student" << endl;
            #endif
            tmpst->pnt_belong.erase(tmpst->pnt_belong.begin()+tmp);
        }
        else
        {
            #ifdef DEBUG
            cout << "ERROR Unable to delete Group pointer in student" << endl;
            #endif
        }
    }

    cout << "Delete S_group:" << name << endl;
}

inline void delete_all()
{
    for (unsigned int i=0; i<stud_all.size(); i++)
    {
        delete stud_all[i];
    }

    for (unsigned int i=0; i<gr_all.size(); i++)
    {
        delete gr_all[i];
    }
    return;
}

//user functions

inline void create_gr()
{
    S_group *tmp;
    tmp=new S_group;
}

inline void create_st()
{
    Student *tmp;
    tmp=new Student;
}

inline void display_sts()
{
    cout << endl << "Students:" << endl;
    for (unsigned int i=0; i<stud_all.size(); i++)
    {
        cout << *stud_all[i] << endl;
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

inline void connecT ()
{
    string gr, stindex;
    int tmpgr, tmpst;

    cout << "Chose group: ";
    if(load(gr, "connecT ()"))
    {
        return;
    }

    if((tmpgr=if_repeated(gr, "blabla"))==-1)
    {
        cout << "Cannot find it" << endl;
        return;
    }

    cout << "Chose student (index): ";
    if(load(stindex, "connecT ()"))
    {
        return;
    }

    if((tmpst=if_repeated(stindex, 2))==-1)
    {
        cout << "Cannot find it" << endl;
        return;
    }

    connect(*stud_all[tmpst], *gr_all[tmpgr]);
    return;
}

inline void display_st_pnt()
{
    string ix;
    int tmp;

    cout << "Which student`s indicators would you like to see? (student index)";
    if(load(ix, "display_st_pnt()"))
    {
        return;
    }

    if((tmp=if_repeated(ix, 2))==-1)
    {
        cout << "There is no such student" << endl;
        return;
    }

    cout << stud_all[tmp]->pnt_belong << endl;

    return;
}

inline void display_gr_pnt()
{
    string na;
    int tmp;
    cout << "Which group`s indicators would you like to see? (group name)";
    if(load(na, "display_gr_pnt()"))
    {
        return;
    }

    if((tmp=if_repeated(na, "blabla"))==-1)
    {
        cout << "There is no such student" << endl;
        return;
    }

    cout << gr_all[tmp]->pnt_child << endl;

    return;
}

inline void display_st()
{
    string ix;
    int tmp;

    cout << "Which student would you like to see? (index)";
    if(load(ix, "display_st()"))
    {
        return;
    }

    if((tmp=if_repeated(ix, 2))==-1)
    {
        cout << "There is no such student" << endl;
        return;
    }

    cout << *stud_all[tmp] << endl;
    return;
}

inline void display_gr()
{
    string na;
    int tmp;

    cout << "Which group would you like to see? (name)";
    if(load(na, "display_gr()"))
    {
        return;
    }

    if((tmp=if_repeated(na, "blabla"))==-1)
    {
        cout << "There is no such student" << endl;
        return;
    }

    cout << *gr_all[tmp] << endl;

    return;
}

bool sum_log_ind(string &gr1, string &gr2, string &gr3, int &tmpgr1, int &tmpgr2)
{
    cout << "Which of the two groups would you like to it?" << endl;
    if(load(gr1, "sum_gr() / logical_gr()"))
    {
        return true;
    }
    cout << "And?" << endl;

    if(load(gr2, "sum_gr() / logical_gr()"))
    {
        return true;
    }

    cout << "Write a name of the group where you would like to save the data (it also could be " << gr1 << " or " << gr2 << ")" << endl;

    if(load(gr3, "sum_gr() / logical_gr()"))
    {
        return true;
    }

    if((tmpgr1=if_repeated(gr1, "blabla"))==-1)
    {
        cout << "sum_log_ind(): Cannot find group " << gr1 << endl;
        return true;
    }
    if((tmpgr2=if_repeated(gr2, "blabla"))==-1)
    {
        cout << "sum_log_ind(): Cannot find group " << gr2 << endl;
        return true;
    }
    return false;
}

inline void sum_gr()
{
    string gr1, gr2, gr3;
    int tmpgr1, tmpgr2;

    if(sum_log_ind(gr1, gr2, gr3, tmpgr1, tmpgr2)==true)
    {
        return;
    }

    if(gr3==gr2)
    {
        *gr_all[tmpgr2]+=*gr_all[tmpgr1];
    }
    else
    if(gr3==gr1)
    {
        *gr_all[tmpgr1]+=*gr_all[tmpgr2];
    }
    else
    {
        S_group *tmp;
        tmp=new S_group;

        tmp->name=gr3;

        *tmp=*gr_all[tmpgr1]+*gr_all[tmpgr2];
    }

    return;
}

inline void logical_gr()
{
    string gr1, gr2, gr3;
    int tmpgr1, tmpgr2;

    if(sum_log_ind(gr1, gr2, gr3, tmpgr1, tmpgr2)==true)
    {
        return;
    }

    if(gr3==gr2)
    {
        *gr_all[tmpgr2]*=*gr_all[tmpgr1];
    }
    else
    if(gr3==gr1)
    {
        *gr_all[tmpgr1]*=*gr_all[tmpgr2];
    }
    else
    {
        S_group *tmp;
        tmp=new S_group;

        tmp->name=gr3;

        *tmp=*gr_all[tmpgr1]**gr_all[tmpgr2];
    }

    return;
}

inline void change_gr_name()
{
    string na;
    int tmp;

    cout << "Which group? : ";
    if(load(na, "change_gr_name()"))
    {
        return;
    }

    if((tmp=if_repeated(na, "blabla"))==-1)
    {
        cout << "Could not find" << endl;
    }

    cout << "New name: ";

    if(load(na, "change_gr_name()"))
    {
        return;
    }

    if(if_repeated(na, "blabla")!=-1)
    {
        cout << "This name is occupied" << endl;
        return;
    }

    (*gr_all[tmp]).rename(na);
    cout << endl;
    return;
}

inline void change_st_name()
{
    string na;
    int tmp;
    cout << "Which student (index)? : ";
    if(load(na, "change_gr_name()"))
    {
        return;
    }

    if((tmp=if_repeated(na, 2))==-1)
    {
        cout << "Could not find" << endl;
    }

    cout << "New name (or NULL to do nothing): ";
    if(load(na, "change_gr_name()"))
    {
        return;
    }

    if(na!="NULL")
    {
        stud_all[tmp]->name=na;
    }


    cout << "New surname (or NULL to do nothing): ";
    if(load(na, "change_gr_name()"))
    {
        return;
    }

    if(na!="NULL")
    {
        stud_all[tmp]->surname=na;
    }

    cout << "New index (or NULL to do nothing): ";
    if(load(na, "change_gr_name()"))
    {
        return;
    }

    if(if_repeated(na, 2)!=-1)
    {
        cout << "This name is occupied" << endl;
        return;
    }

    if(na!="NULL")
    {
        stud_all[tmp]->index=na;
    }
    return;
}

inline void display_min_max()
{
    string na;
    int tmp;
    cout << "Which group?" << endl;
    if(load(na, "display_min_max()"))
    {
        return;
    }

    if((tmp=if_repeated(na, "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    cout << "Min: " << gr_all[tmp]->min_val << "Max: " << gr_all[tmp]->max_val << endl;
    return;
}

inline void help()
{
    cout << "Normal functions:" << endl;
    cout << "+ display" << endl;
    cout << "+ connect" << endl;
    cout << "+ logic" << endl;
    cout << "+ sum" << endl;
    cout << "+ exit / quit / Exit / q" << endl;

    cout << endl << "Student functions: " << endl;
    cout << "+ create student / add student" << endl;
    cout << "+ display students" << endl;
    cout << "+ display student" << endl;
    cout << "+ student indicators" << endl;
    cout << "+ change student name" << endl;

    cout << endl << "Group functions: " << endl;
    cout << "+ create group / add group" << endl;
    cout << "+ display groups" << endl;
    cout << "+ display group" << endl;
    cout << "+ group indicators" << endl;
    cout << "+ change group name" << endl;
    cout << "+ min max" << endl;

    return;
}

void menu()
{
    string buf;
    cout << "Welcome to S-G creator!" << endl << endl;

    #ifdef FILES
    if(total_saving()==true)
    {
        cout << "Data could not be read. Restart program or choose different file." << endl;
    }
    #endif

    while(1)
    {
        cout << endl << "$$";
        getline(cin, buf);
        pop_space(buf);
        //sweep();

        if(buf=="create student"||buf=="add student")
        {
            create_st();
        }
        else
        if(buf=="create group"||buf=="add group")
        {
            create_gr();
        }
        else
        if(buf=="display")
        {
            display_grs();
            display_sts();
        }
        else
        if(buf=="display students")
        {
            display_sts();
        }
        else
        if(buf=="display groups")
        {
            display_grs();
        }
        else
        if(buf=="display group")
        {
            display_gr();
        }
        else
        if(buf=="display student")
        {
            display_st();
        }
        else
        if(buf=="connect")
        {
            connecT();
        }
        else
        if(buf=="student indicators")
        {
            display_st_pnt();
        }
        else
        if(buf=="group indicators")
        {
            display_gr_pnt();
        }
        else
        if(buf=="sum")
        {
            sum_gr();
        }
        else
        if(buf=="logic")
        {
            logical_gr();
        }
        else
        if(buf=="min max")
        {
            display_min_max();
        }
        else
        if(buf=="change group name")
        {
            change_gr_name();
        }
        else
        if(buf=="change student name")
        {
            change_st_name();
        }

        else
        if(buf=="exit"||buf=="quit"||buf=="Exit"||buf=="q")
        {
            #ifdef FILES
            if(total_saving()==true)
            {
                cout << "Data could not be save." << endl;
            }
            #endif

            delete_all();
            return;
        }
        else
        if(buf=="help")
        {
            help();
        }
        else
        {
            cout << "Unknown command" << endl;
        }
    }

}

#endif // STUDENT_CPP

