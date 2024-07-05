#include <iostream>
#include <list>

using namespace std;

#define tamanhoProveta 5

void print(list<int> provetas[], int numeroProvetas)
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

void inicializar(list<int> provetas[], int numeroProvetas)
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
    cout << "Quantas provetas serão: ";
    int numeroProvetas; 
    cin >> numeroProvetas;
    list<int> provetas[numeroProvetas];
    inicializar(provetas, numeroProvetas);
    print(provetas, numeroProvetas);
    return 0;
}

