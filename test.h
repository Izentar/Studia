/*
    * About:  Students group creator
    * Author: Mateusz Kordowski
    * Leader: Aleksandra Paśnikowska
    * Update: 23.03.2018
*/

#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "student.h"

#define LESS_VECTOR 1000

bool test(unsigned int repeat);

void menu();

// extra

inline void sweep ();

inline void pop_space(string& tmp);

int if_repeated_st (const string& ind);      // generally

int if_repeated_gr (const string& na);     // generally

inline bool indEX();

inline bool gr_naME();

inline bool naME();

inline bool surnaME();

inline void conn();

inline void create_group();

inline void create_student();

inline void d_min_max ();

inline void display_group();

bool load_gr_3(string & tmp_gr_name, string & tmp_gr_name2, int & int_tmp, int & int_tmp2);

inline void sum();

inline void logic();

inline void display_grs();

inline void display_sts();

inline void delete_all();

void help();


#endif
