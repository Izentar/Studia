/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 19.03.2018
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

#define TEST_VALUE 1000
//#define DEBUG

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include "../headers/student.h"

static vector <Student *> stud_all;
static vector <S_group *> gr_all;
static unsigned long int MAX_STUD = stud_all.max_size()/LESS_VECTOR;
static unsigned long int MAX_GR = gr_all.max_size()/LESS_VECTOR;



//declaration

inline int find_v(const vector <Student *> st, const Student& what);
inline int find_v(const vector <S_group *> gr, const S_group& what);
bool load_again(string& tmp);
inline bool load(string& str, string problem);
int if_repeated (const string& na, string trash_group_name);

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
        cout << *st[i] << endl;
    }
    return outgo << "End" << endl;
}

ostream & operator<< (ostream& outgo, const vector <S_group *> &gr)
{
    for (unsigned int i=0; i<gr.size(); i++)
    {
        cout << *gr[i] << endl;
    }
    return outgo << "End" << endl;
}

S_group::S_group(char allocation, vector <Student *> &st, string nam)       // needed only for operators
:if_min_max(false), min_val("0"), max_val("0")
{
    if(gr_all.size()>MAX_GR)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    name=nam;

    if(allocation=='I')
    {
        gr_all.push_back(this);
    }

    for (unsigned int i=0; i<st.size(); i++)
    {
        pnt_child.push_back(st[i]);

        st[i]->pnt_belong.push_back(this);
    }



    cout << "Created S_group :" << name << endl;
}

void S_group::operator= (const S_group &gr)
{
    string tmp;
    Student *st;
    int v_find;
    if_min_max=false;
    #ifdef DEBUG
    cout << "operator= : begin" << endl;
    #endif // DEBUG

    for (unsigned int i=0; i<pnt_child.size(); i++)     // delete pointers from students
    {
        st=pnt_child[i];
        if((v_find=find_v(st->pnt_belong, *this))!=-1)
        {
            st->pnt_belong.erase(st->pnt_belong.begin()+v_find);
        }
    }

    #ifdef DEBUG
    cout << "operator= : en of 1 loop" << endl;
    #endif // DEBUG

    pnt_child.clear();

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)      // add pointers to students
    {
        pnt_child.push_back(gr.pnt_child[i]);
        gr.pnt_child[i]->pnt_belong.push_back(this);

    }

    #ifdef DEBUG
    cout << "operator= : en of 2 loop" << endl;
    #endif // DEBUG

    #ifdef DEBUG
    cout << "end of operator=" << endl;
    #endif // DEBUG

    return;
}

S_group S_group::operator+ (const S_group &gr) const
{
    vector <Student *> st;

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)     //copy
    {
        st.push_back(gr.pnt_child[i]);
    }

    for (unsigned int i=0; i<pnt_child.size(); i++)     // find different pointers
    {
        if(find_v(gr.pnt_child, *pnt_child[i])==-1)  // not found
        {
            st.push_back(pnt_child[i]);
        }
    }

    #ifdef DEBUG
    cout << "operator+: Succeed" << endl;
    #endif

    return S_group('N', st, "NOT KNOWN");
}

void S_group::operator+= (const S_group &gr)
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
}

S_group S_group::operator* (const S_group &gr) const
{
    vector <Student *> st;

    for (unsigned int i=0; i<pnt_child.size(); i++)     // find the same pointers
    {
        if(find_v(gr.pnt_child, *pnt_child[i])!=-1)  // found
        {
            st.push_back(pnt_child[i]);
        }
    }

    return S_group('N', st, "NOT KNOWN");
}

void S_group::operator*= (const S_group &gr)
{
    Student *ind;
    int distance;
    vector <Student *> st;
    if_min_max=false;

    for (unsigned int i=0; i<pnt_child.size(); i++)
    {
        st.push_back(pnt_child[i]);

        if((distance=find_v(pnt_child[i]->pnt_belong, *this))!=-1)  // found
        {
            pnt_child[i]->pnt_belong.erase(pnt_child[i]->pnt_belong.begin()+distance);
        }
    }

    this->pnt_child.clear();

    for (unsigned int i=0; i<gr.pnt_child.size(); i++)
    {
        if(find_v(st, *gr.pnt_child[i])!=-1)  // found
        {
            pnt_child.push_back(gr.pnt_child[i]);
            ind=gr.pnt_child[i];
            ind->pnt_belong.push_back(this);
        }
    }
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
    int tmp=-1;
    do
    {
        if(tmp!=-1)
        {
            cout << "Already exist. Try again" << endl;
        }
        cout << "Please specify:" << endl;
        cout << "Name: ";
        if(load(name, "entitle (string& name, string& surname, string& index)"))
        {
            return true;
        }

        cout << "surname: ";
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
    while((tmp=if_repeated(index, 2))!=-1);



    #ifdef DEBUG
    cout << "entitle (string& name, string& surname, string& index): Succeed" << endl;
    #endif

    return false;
}

// class functions

inline void S_group::rename(string na)
{
    cout << "Enter the new name: ";
    if(load(na, "Program cannot perform rename operation (names set to default)"))
    {
        return;
    }

    if(if_repeated(na, "blabla")!=-1)
    {
        cout << "This name is occupied" << endl;
    }
    else
    {
        name=na;
        #ifdef DEBUG
        cout << "Changed name" << endl;
        #endif
    }

    #ifdef DEBUG
    cout << "rename(): Succeed" << endl;
    #endif
    return;
}

bool Student::delete_student(string &inde)
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

bool S_group::delete_group(string &na)
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
    tmp=new Student('I');

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

Student::Student(char allocation, string n, string sn, string ix)
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

    if(allocation=='I')
    {
        stud_all.push_back(this);
    }

    cout << "Created Student:" << "Name: " << name << " Surname: " << surname << " Index: " << index << endl;
    #ifdef DEBUG
    cout << "VECTOR STUD_ALL " << stud_all[stud_all.size()-1]->name << endl;
    #endif
}

Student::Student(char allocation, string n, string sn, string ix, string trash_must_have_names)
{
    if(stud_all.size()>MAX_STUD)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    name=n;
    surname=sn;
    index=ix;

    if(allocation=='I')
    {
        stud_all.push_back(this);
    }

    cout << "Created Student:" << "Name: " << name << " Surname: " << surname << " Index: " << index << endl;
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

    for (unsigned int i=0; i<pnt_belong.size(); i++)
    {
        tmpgr=pnt_belong[i];
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

S_group::S_group(char allocation, string n)
:if_min_max(false), min_val("0"), max_val("0")
{
    if(gr_all.size()>MAX_GR)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    string tmp;
    cout << "Enter the name: ";
    if(load(tmp, "Program can not perform this operation (names set to default)"))
    {
        name=n;
    }
    else
    {
        if(if_repeated(tmp, "blabla")!=-1)
        {
            cout << "This name is occupied (names set to default)" << endl;
            name=n;
        }
        else
        {
            name=tmp;
        }


    }

    if(allocation=='I')
    {
        gr_all.push_back(this);
    }

    cout << "Created S_group :" << name << endl;
}

S_group::S_group(char allocation, string only_in_function, int trash)
:if_min_max(false), min_val("0"), max_val("0")
{
    if(gr_all.size()>MAX_GR)
    {
        cout << "You are approaching the border of memory" << endl;
    }

    name=only_in_function;

    if(allocation=='I')
    {
        gr_all.push_back(this);
    }

    cout << "Created S_group :" << name << endl;
}

S_group::~S_group()
{
    int tmp;

    #ifdef DEBUG
    cout << endl;
    #endif

    if((tmp=find_v(gr_all, *this))!=-1)
    {
        #ifdef DEBUG
        cout << "VECTOR GR_ALL ERASE " << gr_all[tmp]->name << endl;
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

        #ifdef DEBUG
        cout << tmpst->index << endl;
        #endif

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
    int tmpgr, tmpst;
    tmpst=stud_all.size();
    tmpgr=gr_all.size();

    for (int i=0; i<tmpst; i++)
    {
        #ifdef DEBUG
        cout << *stud_all[i] << endl;
        #endif
        delete stud_all[0];
    }

    for (int i=0; i<tmpgr; i++)
    {
        #ifdef DEBUG
        cout << *gr_all[i] << endl;
        #endif
        delete gr_all[0];
    }
    return;
}

//user functions

inline int absorb(string &str, string what_if_problem, string trash_group)
{
    int tmp;
    if(load(str, what_if_problem))
    {
        return -1;
    }

    if((tmp=if_repeated(str, trash_group))==-1)
    {
        return -1;
    }
    #ifdef DEBUG
    cout << "absorb(group): Succeed" << endl;
    #endif // DEBUG

    return tmp;
}

inline int absorb(string &str, string what_if_problem, int trash_student)
{
    int tmp;
    if(load(str, what_if_problem))
    {
        return -1;
    }

    if((tmp=if_repeated(str, trash_student))==-1)
    {
        return -1;
    }
    #ifdef DEBUG
    cout << "absorb(student): Succeed" << endl;
    #endif // DEBUG

    return tmp;
}

bool sum_log_ind(string &gr1, string &gr2, string &gr3, int &tmpgr1, int &tmpgr2)
{
    cout << "Which of the two groups would you like to it?" << endl;
    if((tmpgr1=absorb(gr1, "sum_gr() / logical_gr()", "blabla"))==-1)
    {
        #ifdef DEBUG
        cout << "sum_log_ind(): Cannot find group " << gr1 << endl;
        #endif // DEBUG
        cout << "Could not find" << endl;
        return true;
    }
    cout << "And?" << endl;
    if((tmpgr2=absorb(gr2, "sum_gr() / logical_gr()", "blabla"))==-1)
    {
        #ifdef DEBUG
        cout << "sum_log_ind(): Cannot find group " << gr2 << endl;
        #endif // DEBUG
        cout << "Could not find" << endl;
        return true;
    }

    cout << "Write a name of the group where you would like to save the data (it also could be " << gr1 << " or " << gr2 << ")" << endl;

    if(load(gr3, "sum_gr() / logical_gr()"))
    {
        return true;
    }

    #ifdef DEBUG
    cout << "sum_log_ind(): Succeed" << endl;
    #endif

    return false;
}

inline void create_gr()
{
    new S_group('I');
}

inline void create_st()
{
    new Student('I');
}

inline void add_st()
{
    string na;
    int tmp;

    cout << "Which group? : ";
    if((tmp=absorb(na, "add_st()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }
    create(*gr_all[tmp]);
    return;
}

inline void display_sts()
{
    cout << endl << "Students:" << endl;
    cout << stud_all << endl;
    return;
}

inline void display_grs()
{
    cout << endl << "Groups:" << endl;
    cout << gr_all << endl;

    return;
}

inline void connecT ()
{
    string gr, stindex;
    int tmpgr, tmpst;

    cout << "Chose group: ";
    if((tmpgr=absorb(gr, "connecT ()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    cout << "Chose student (index): ";
    if((tmpst=absorb(stindex, "connecT ()", 2))==-1)
    {
        cout << "Could not find" << endl;
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
    if((tmp=absorb(ix, "display_st_pnt()", 2))==-1)
    {
        cout << "Could not find" << endl;
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
    if((tmp=absorb(na, "display_gr_pnt()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
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
    if((tmp=absorb(ix, "display_st()", 2))==-1)
    {
        cout << "Could not find" << endl;
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
    if((tmp=absorb(na, "display_gr()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    cout << *gr_all[tmp] << endl;

    return;
}

inline void sum_gr()
{
    string gr1, gr2, gr3;
    int tmpgr1, tmpgr2, if_reap;

    if(sum_log_ind(gr1, gr2, gr3, tmpgr1, tmpgr2)==true)
    {
        return;
    }

    if(gr3==gr2)
    {
        #ifdef DEBUG
        cout << "sum_gr(): using overload operator 1" << endl;
        #endif

        *gr_all[tmpgr2]+=*gr_all[tmpgr1];

         gr_all[tmpgr2]->name=gr3;
    }
    else
    if(gr3==gr1)
    {
        #ifdef DEBUG
        cout << "sum_gr(): using overload operator 2" << endl;
        #endif

        *gr_all[tmpgr1]+=*gr_all[tmpgr2];

         gr_all[tmpgr1]->name=gr3;
    }
    else
    if((if_reap=if_repeated(gr3, "blabla"))==-1)
    {
        S_group *tmp;
        tmp=new S_group('I', gr3, 2);

        tmp->name=gr3;

        #ifdef DEBUG
        cout << "sum_gr(): using overload operator 3" << endl;
        #endif

        *tmp=(*gr_all[tmpgr1]+*gr_all[tmpgr2]);
    }
    else
    {
        #ifdef DEBUG
        cout << "sum_gr(): using overload operator 4" << endl;
        #endif

        *gr_all[if_reap]=(*gr_all[tmpgr1]+*gr_all[tmpgr2]);

        gr_all[if_reap]->name=gr3;
    }

    #ifdef DEBUG
    cout << "sum_gr(): Succeed" << endl;
    #endif

    return;
}

inline void logical_gr()
{
    string gr1, gr2, gr3;
    int tmpgr1, tmpgr2, if_reap;

    if(sum_log_ind(gr1, gr2, gr3, tmpgr1, tmpgr2)==true)
    {
        return;
    }

    if(gr3==gr2)
    {
        #ifdef DEBUG
        cout << "logical_gr(): using overload operator 1" << endl;
        #endif

        *gr_all[tmpgr2]*=*gr_all[tmpgr1];
    }
    else
    if(gr3==gr1)
    {
        #ifdef DEBUG
        cout << "logical_gr(): using overload operator 2" << endl;
        #endif

        *gr_all[tmpgr1]*=*gr_all[tmpgr2];
    }
    else
    if((if_reap=if_repeated(gr3, "blabla"))==-1)
    {
        S_group *tmp;
        tmp=new S_group('I', gr3, 2);

        tmp->name=gr3;

        #ifdef DEBUG
        cout << "logical_gr(): using overload operator 3" << endl;
        #endif

        *tmp=*gr_all[tmpgr1]**gr_all[tmpgr2];
    }
    else
    {
        #ifdef DEBUG
        cout << "sum_gr(): using overload operator 4" << endl;
        #endif

        *gr_all[if_reap]=(*gr_all[tmpgr1]**gr_all[tmpgr2]);

        gr_all[if_reap]->name=gr3;
    }

    #ifdef DEBUG
    cout << "logical_gr(): Succeed" << endl;
    #endif

    return;
}

inline void change_gr_name()
{
    string na;
    int tmp;

    cout << "Which group? : ";
    if((tmp=absorb(na, "change_gr_name()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
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
    if((tmp=absorb(na, "change_st_name()", 2))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    cout << "New name (or OK to do nothing): ";
    if(load(na, "change_st_name()"))
    {
        cout << "Could not find" << endl;
        return;
    }

    if(na!="OK")
    {
        stud_all[tmp]->name=na;
    }


    cout << "New surname (or OK to do nothing): ";
    if(load(na, "change_st_name()"))
    {
        return;
    }

    if(na!="OK")
    {
        stud_all[tmp]->surname=na;
    }

    cout << "New index (or OK to do nothing): ";
    if((absorb(na, "change_st_name()", 2))!=-1)
    {
        cout << "This name is occupied" << endl;
        return;
    }

    if(na!="OK")
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
    if((tmp=absorb(na, "display_min_max()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    if(gr_all[tmp]->if_min_max==false)
    {
        gr_all[tmp]->index_min_max();
    }

    cout << "Min: " << gr_all[tmp]->min_val << "Max: " << gr_all[tmp]->max_val << endl;
    return;
}

inline void delete_st()
{
    string na;
    int tmp;

    cout << "Which student? (Index): ";
    if((tmp=absorb(na, "delete_st()", 2))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    delete stud_all[tmp];
    return;
}

inline void delete_gr()
{
    string na;
    int tmp;

    cout << "Which group? : ";
    if((tmp=absorb(na, "delete_gr()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    delete gr_all[tmp];
}

inline void sort_gr()
{
    string na;
    int tmp;

    cout << "Which group? : ";
    if((tmp=absorb(na, "sort_gr()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }
    gr_all[tmp]->index_min_max();

    return;
}

inline void delete_connection()
{
    string gr, st;
    int tmpgr, tmpst;
    cout << "Which group?" << endl;
    if((tmpgr=absorb(gr, "delete_connection()", "blabla"))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    cout << "Which student?" << endl;
    if((tmpst=absorb(st, "delete_connection()", 2))==-1)
    {
        cout << "Could not find" << endl;
        return;
    }

    for (unsigned int i=0; i<gr_all[tmpgr]->pnt_child.size(); i++)
    {
        if(gr_all[tmpgr]->pnt_child[i]==stud_all[tmpst])
        {
            gr_all[tmpgr]->pnt_child.erase(gr_all[tmpgr]->pnt_child.begin()+i);
            break;
        }
    }

    for (unsigned int i=0; i<stud_all[tmpst]->pnt_belong.size(); i++)
    {
        if(stud_all[tmpst]->pnt_belong[i]==gr_all[tmpgr])
        {
            stud_all[tmpst]->pnt_belong.erase(stud_all[tmpst]->pnt_belong.begin()+i);
            break;
        }
    }

    return;

}

inline void help()
{
    cout << "Normal functions:" << endl;
    cout << "+ display" << endl;
    cout << "+ connect" << endl;
    cout << "+ logic" << endl;
    cout << "+ sum" << endl;
    cout << "+ delete connection" << endl;
    cout << "+ exit / quit / Exit / q" << endl;

    cout << endl << "Student functions: " << endl;
    cout << "+ create student" << endl;
    cout << "+ display students" << endl;
    cout << "+ display student" << endl;
    cout << "+ student pointers" << endl;
    cout << "+ change student name" << endl;
    cout << "+ delete student" << endl;

    cout << endl << "Group functions: " << endl;
    cout << "+ create group" << endl;
    cout << "+ display groups" << endl;
    cout << "+ display group" << endl;
    cout << "+ group pointers" << endl;
    cout << "+ change group name" << endl;
    cout << "+ min max" << endl;
    cout << "+ sort" << endl;
    cout << "+ add student" << endl;
    cout << "+ delete group" << endl;

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
        cout << endl << "$$:";
        getline(cin, buf);
        pop_space(buf);

        if(buf=="create student"||buf=="cs")
        {
            create_st();
        }
        else
        if(buf=="create group"||buf=="cg")
        {
            create_gr();
        }
        else
        if(buf=="add student")
        {
            add_st();
        }
        else
        if(buf=="delete student")
        {
            delete_st();
        }
        else
        if(buf=="delete group")
        {
            delete_gr();
        }
        else
        if(buf=="sort")
        {
            sort_gr();
        }
        else
        if(buf=="display"||buf=="d")
        {
            display_grs();
            display_sts();
        }
        else
        if(buf=="display students"||buf=="dss")
        {
            display_sts();
        }
        else
        if(buf=="display groups"||buf=="dgs")
        {
            display_grs();
        }
        else
        if(buf=="display group"||buf=="dg")
        {
            display_gr();
        }
        else
        if(buf=="display student"||buf=="ds")
        {
            display_st();
        }
        else
        if(buf=="connect"||buf=="cn")
        {
            connecT();
        }
        else
        if(buf=="student pointers"||buf=="sp")
        {
            display_st_pnt();
        }
        else
        if(buf=="group pointers"||buf=="gp")
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
        if(buf=="delete connection"||buf=="dc")
        {
            delete_connection();
        }
        else
        if(buf=="min max")
        {
            display_min_max();
        }
        else
        if(buf=="change group name"||buf=="cgn")
        {
            change_gr_name();
        }
        else
        if(buf=="change student name"||buf=="csn")
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

bool test()
{
    string a, b, t;
    Student ABE('N', "Ala", "ma", "252", "blabla");
    S_group ISC('N', "jak", 2);

    Student *sp[TEST_VALUE];
    S_group *sgp[TEST_VALUE+TEST_VALUE];

    for (int i=0; i<TEST_VALUE; i++)
    {
        a="S";
        b="G";
        t=to_string(i);
        a+=t;
        b+=t;
        sp[i]=new Student('I', a, a, a, a);
        sgp[i]=new S_group('I', b, 2);
    }

    for (int i=0; i<TEST_VALUE-100; i++)
    {
        connect(*sp[i], *sgp[i+30]);
        connect(*sp[i], *sgp[i+40]);
        connect(*sp[i+10], *sgp[i]);
        connect(*sp[i+50], *sgp[i]);
        connect(*sp[i+70], *sgp[i+33]);
    }

    for (int i=0; i<TEST_VALUE/10; i++)
    {
        disconnect(*sp[i*2], *sgp[i*5]);
    }

    for (int i=0; i<TEST_VALUE; i++)
    {
        sgp[i]->index_min_max();
    }

    for (int i=0; i<TEST_VALUE-1; i++)
    {
        *sgp[i]+=*sgp[i+1];
    }
    for (int i=0; i<TEST_VALUE-1; i++)
    {
        *sgp[i]*=*sgp[i+1];
    }

    for (int i=TEST_VALUE; i<2*TEST_VALUE; i++)
    {
        b="G";
        t=to_string(i);
        b+=t;
        sgp[i]=new S_group('I', b, 2);
    }

    for (int i=0; i<TEST_VALUE-1; i++)      // sgp[TEST_VALUE+i] not declared
    {
        *sgp[TEST_VALUE+i]=*sgp[i]+*sgp[i+1];
    }

    for (int i=0; i<TEST_VALUE-1; i++)          // sgp[TEST_VALUE+i] not declared
    {
        *sgp[TEST_VALUE+i]=*sgp[i]**sgp[i+1];
    }




    delete_all();
    return false;
}


#endif // STUDENT_CPP

