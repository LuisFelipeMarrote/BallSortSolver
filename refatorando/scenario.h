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
private:
    int choose_table();    
    std::list<table>::iterator find_table(int table_escolhida);
public:
    scenario();
    void insert_new();
    void insert_table(table table);
    table random_game();
    void print_all();
    table get_table ();
    void delete_table();
};