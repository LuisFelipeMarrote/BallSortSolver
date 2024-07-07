#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct node
{
    int valor;
    int profundidade;
};



int heuristica(list<int> provetas[], int numeroProvetas, int tamanhoProveta)
{
    int total = 0;
    for (int i = 0; i < numeroProvetas; i++)
    {
        list<int>::iterator base = provetas[i].begin();
        int aux = *base;
        for (list<int>::iterator it = base++; it != provetas[i].end(); ++it)
        {
            total = total + abs(aux - *it);
        }
    }
    return total;
}

void jogadasPossiveisInicio(list<int> provetas[], int numeroProvetas, int tamanhoProveta, int **jogadasPermitidas)
{
    for (int i = 0; i < numeroProvetas; i++)
    {
        if(provetas[i].empty() == true)
        {
            for (int j = 0; j < tamanhoProveta; j++)
            {
                jogadasPermitidas[i][j] = 1;                
            }
        }
        for (int j = 0; j < numeroProvetas; j++)
        {
            if(provetas[i].back() == provetas[j].back() && i != j && provetas[j].size() != tamanhoProveta)
                jogadasPermitidas[i][j] = 1;
        }
    }
}

void PrintjogadasPossiveisInicio(int numeroProvetas, int **jogadasPermitidas)
{
    for (int i = 0; i < numeroProvetas; i++)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            cout << jogadasPermitidas[i][j] << " ";
        }
        cout << endl;
    }
}

bool isOver(list<int> provetas[], int numeroProvetas, int tamanhoProveta)
{
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

    int** jogadasPermitidas = (int**)malloc(numeroProvetas*sizeof(int*));
    for (int i = 0; i < numeroProvetas; i++)
        jogadasPermitidas[i] = (int*)malloc(numeroProvetas*sizeof(int));

    list<int> provetas[numeroProvetas];

    inicializar(provetas, numeroProvetas, tamanhoProveta);
    print(provetas, numeroProvetas, tamanhoProveta);
    cout << isOver(provetas, numeroProvetas, tamanhoProveta) << endl;
    jogadasPossiveisInicio(provetas, numeroProvetas, tamanhoProveta, jogadasPermitidas);
    PrintjogadasPossiveisInicio(numeroProvetas, (int**)jogadasPermitidas);
    return 0;
}

