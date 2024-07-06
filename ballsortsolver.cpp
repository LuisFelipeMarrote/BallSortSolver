#include <iostream>
#include <list>

using namespace std;

int heuristica(list<int> provetas[], int numeroProvetas, int tamanhoProveta){
    int total = 0;
    for (int i = 0; i < numeroProvetas; i++)
    {
        for (list<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
        {
            
        }
    }
}

bool isOver(list<int> provetas[], int numeroProvetas, int tamanhoProveta){
    for (int i = 0; i < numeroProvetas; i++)
    {
        if (provetas[i].size() != tamanhoProveta){
            return false;
        }
        list<int>::iterator base = provetas[i].begin();
        for (list<int>::iterator it = base++; it != provetas[i].end(); ++it)
        {
            if(*base != *it)
                return false;
        }
    }
    return true;
}

void print(list<int> provetas[], int numeroProvetas, int tamanhoProveta)
{
    for (int i = 0; i < numeroProvetas; i++)
    {
        for (list<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
        {
            cout << *it;
        }
    cout << endl;
    }
}

void inicializar(list<int> provetas[], int numeroProvetas, int tamanhoProveta)
{
    int aux;
    int quantidade=0;
    for (int i = 0; i < numeroProvetas; i++)
    {
        while(quantidade < tamanhoProveta)
        {        
            cout << "Insira na posição da proveta " << i << " ou digite 0 para acabar: " << endl;
            cin >> aux;    
            if (aux == 0)
                break;
            provetas[i].push_back(aux);
            quantidade++;
        }
        quantidade = 0;
    }
}

int main ()
{
    int tamanhoProveta = 5;
    int numeroProvetas;
    
    cout << "Quantas provetas serão: ";
    cin >> numeroProvetas;
    
    //cout << "Quantas bolas por proveta serão(min:2): ";
    //cin >> tamanhoProveta;
    
    list<int> provetas[numeroProvetas];
    
    inicializar(provetas, numeroProvetas, tamanhoProveta);
    print(provetas, numeroProvetas, tamanhoProveta);
    cout << isOver(provetas, numeroProvetas, tamanhoProveta);
    return 0;
}

