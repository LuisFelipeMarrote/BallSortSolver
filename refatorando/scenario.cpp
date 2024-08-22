#include "Scenario.h"

Scenario::Scenario()
{
    //table(int numero_provetas, int tamanho_proveta, vec_vec provetas);
    table table1(3,4,{{1,1,1,1},{2,2,2},{2}});
    table table2(7,4,{{4,3,2,1},{5,2,3,3},{1,2,4,5},{1,2,1,5},{4,5,3,4},{},{}});
    table table3(3,4,{{1,1,1,1},{2,2,2},{3}});
    tables.push_back(table1);
    tables.push_back(table2);
    tables.push_back(table3);
}

void Scenario::insert_new()
{
    int tamanho_proveta = 0;
    int numero_provetas = 0;
    std::cout << "Tamanho da proveta: " << std::endl;
    std::cin >> tamanho_proveta;
    std::cout << "Numero de provetas: " << std::endl;
    std::cin >> numero_provetas;    
    table table(numero_provetas,tamanho_proveta);
    tables.push_back(table);
}

void Scenario::insert_table(table table)
{
    tables.push_back(table);
}

table Scenario::random_game()
{
    int numero_provetas = 0;
    int tamanho_proveta = 0;
    std::cout << "Tamanho da proveta: " << std::endl;
    std::cin >> tamanho_proveta;
    std::cout << "Numero de provetas: " << std::endl;
    std::cin >> numero_provetas;
    table table(numero_provetas,tamanho_proveta);
    return table;
}

void Scenario::print_all()
{
    int i = 0;
    for(std::list<table>::iterator it = tables.begin(); it != tables.end();++it)
    {
        std::cout << "Table " << i + 1 << ":" << std::endl;
        it->print_table();
        std::cout << std::endl;
        i++;
    }
}

int Scenario::choose_table()
{
    int table_escolhida;
    print_all();
    std::cout << "Qual a table sera escolhida (1-" << tables.size() << ")?" << std::endl;
    std::cin >> table_escolhida;
    return table_escolhida - 1;
}

std::list<table>::iterator Scenario::find_table(int table_escolhida)
{        
    int i = 0;
    std::list<table>::iterator it = tables.begin(); 
    
    while(i != table_escolhida)
    {
        ++it;
        i++;
    }
    return it;
}

table Scenario::get_table()
{
    int table_escolhida = choose_table();
    std::list<table>::iterator tables_aux = find_table(table_escolhida);
    return *tables_aux;
}

void Scenario::delete_table()
{
    int table_escolhida = choose_table();
    std::list<table>::iterator tables_aux =  find_table(table_escolhida);
    tables.erase(tables_aux);
}
