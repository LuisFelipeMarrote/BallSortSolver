// Essa vai ser classe 
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> vec_vec;

#pragma once

class table
{

/****************************************************************/
//Variables

private:
    int numero_provetas = 0;
    int tamanho_proveta = 0; 
    vec_vec provetas;

/****************************************************************/
//Funticions

public:
    table();
    table(int numero_provetas, int tamanho_proveta);
    table(int numero_provetas, int tamanho_proveta, vec_vec provetas);
    void create_table();
    void print_table();
    void update_table();
    vec_vec get_proveta();
    int get_numero_provetas();
    int get_tamanho_proveta();
};