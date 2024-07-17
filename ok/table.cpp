#include "table.h"

table::table(){
    std::cout << "oi";
}

table::table(int numero_provetas, int tamanho_proveta)
{
    this->numero_provetas = numero_provetas;
    this->tamanho_proveta = tamanho_proveta;
    std::vector<int> aux (0,0);
    this->provetas.resize(numero_provetas,aux);  
    create_table();
}

table::table(int numero_provetas, int tamanho_proveta, vec_vec provetas)
{
    this->numero_provetas = numero_provetas;
    this->tamanho_proveta = tamanho_proveta;
    this->provetas.resize(numero_provetas);        
    for (int n = 0; n < this->numero_provetas; n++)
        std::copy(provetas[n].begin(),provetas[n].end(),std::back_inserter(this->provetas[n]));    
}

void table::create_table()
{
    int aux;
    for (int n = 0; n < numero_provetas; n++)
    {
        for (int m = 0; m < tamanho_proveta; m++)
        {        
            std::cout << "Insira na posição da proveta " << n << " ou digite 0 para acabar: " << std::endl;
            std::cin >> aux;    
            if(aux == 0)
                break;
            provetas[n][m] = aux;
        }
    }
}

// vou implementar diferente isso talvez, ainda não sei
void table::print_table()
{
    for (int i = 0; i < numero_provetas; i++)
    {
        for (std::vector<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
        {
            std::cout << *it;
        }
    std::cout << std::endl;
    }
}

void table::update_table()
{
    do
    {        
        int linha = 0;
        int aux = 0; 
        std::vector<int> vector_aux (tamanho_proveta,0);

        std::cout << "Qual proveta deseja mudar (1-" << numero_provetas << ")? (Caso deseja sair pressione 0)";
        std::cin >> linha;
        
        if(linha == 0)
            break;
        for (int m = 0; m < tamanho_proveta; m++)
        {
            std::cout << "Insira na posição" << m + 1 << " da proveta " << linha << " ou digite 0 para acabar: " << std::endl;
            std::cin >> aux;                  
            if (aux == 0)
                break;
            vector_aux[m] = aux;
        }

        std::copy(vector_aux.begin(),vector_aux.end(),std::back_inserter(provetas[linha]));          

    }while (true);         
}

vec_vec table::get_proveta()
{
    return provetas;
}

int table::get_numero_provetas()
{
    return numero_provetas;
}

int table::get_tamanho_proveta()
{
    return tamanho_proveta;
}