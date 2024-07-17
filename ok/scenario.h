#include "table.h"
#include <list>

#pragma once

class scenario
{

/****************************************************************/
//Variables

private:
    std::list<table> tables;

/****************************************************************/
//Funticions

public:
    void insert();
    table random_game();
    void print_all();
    int choose_table();
    std::list<table>::iterator find_table(int table_escolhida);
    table get_table ();
    void delete_table();
};