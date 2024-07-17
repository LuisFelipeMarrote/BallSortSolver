#include "scenario.h"

void scenario::insert()
{
    int numero_provetas = 0;
    int tamanho_proveta = 0;
    std::cout << "Tamanho da proveta: " << std::endl;
    std::cin >> tamanho_proveta;
    std::cout << "Numero de provetas: " << std::endl;
    std::cin >> numero_provetas;    
    table table(numero_provetas,tamanho_proveta);
    tables.push_back(table);
}

table scenario::random_game()
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

void scenario::print_all()
{
    for(std::list<table>::iterator it = tables.begin(); it != tables.end();++it)
    {
        it->print_table();
    }
}

int scenario::choose_table()
{
    int table_escolhida;
    print_all();
    std::cout << "Qual a table sera escolhida (1-" << tables.size() << ")?" << std::endl;
    std::cin >> table_escolhida;
    return table_escolhida;
}

std::list<table>::iterator scenario::find_table(int table_escolhida)
{        
    int i = 0;
    std::list<table>::iterator it = tables.begin(); 
    
    while(i != table_escolhida)
    {
        ++it;
    }
    return it;
}

table scenario::get_table()
{
    int table_escolhida = choose_table();
    std::list<table>::iterator tables_aux = find_table(table_escolhida);
    return *tables_aux;
}

void scenario::delete_table()
{
    int table_escolhida = choose_table();
    std::list<table>::iterator tables_aux =  find_table(table_escolhida);
    tables.erase(tables_aux);
}
