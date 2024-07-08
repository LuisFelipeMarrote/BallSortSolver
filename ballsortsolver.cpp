#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct node
{
    int valor;
    int profundidade;
};


// acho que a heuristica tem que levar em conta a profundidade da ultima bola comparada a do topo,
// quantidades de bolas de cores diferentes e a posicao das bolas de outras cores.
int heuristica(list<int> provetas[], int numeroProvetas, int tamanhoProveta)
{
    int total = 0;
    for (int i = 0; i < numeroProvetas; i++)
    {
        list<int>::iterator base = provetas[i].begin();
        int aux = *base;
        int j = 1;
        for (list<int>::iterator it = provetas[i].end(); it != provetas[i].begin(); --it)
        {
            total = total + abs(aux - *it)*j;
            j++;
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
            for (int j = 0; j < numeroProvetas; j++)
            {
                jogadasPermitidas[j][i] = 1;                
            }
            jogadasPermitidas[i][i] = 0;
        }
        for (int j = 0; j < numeroProvetas; j++)
        {
            if(provetas[i].back() == provetas[j].back() && i != j && provetas[j].size() != tamanhoProveta)
                jogadasPermitidas[j][i] = 1;
        }
    }
}
// jogada é um array com 2 valores i e j ([i,j]), a bola de i vai para j;
// funçao para a atualizar aas jogdas permitidas  
// talvez seja interessante pensar depois numa estrutura que nao considere os tubos ja feitos
void jogadasPossiveisMID(list<int> provetas[], int numeroProvetas, int tamanhoProveta, int **jogadasPermitidas, int jogada[])
{    
    if(provetas[jogada[0]].back() != provetas[jogada[1]].back())
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            if(provetas[j].back() == provetas[jogada[0]].back() && j != jogada[0])
            {
                if(provetas[j].size() != tamanhoProveta)
                {
                    jogadasPermitidas[jogada[0]][j] = 1;    
                    jogadasPermitidas[j][jogada[0]] = 1;
                }
                else
                {
                    jogadasPermitidas[j][jogada[0]] = 1;  
                }
            }
            else
            {
                jogadasPermitidas[jogada[0]][j] = 0;
                jogadasPermitidas[j][jogada[0]] = 0;  
            }
        }

    }

    // atualiza jogadasPermitidas se a proveta alvo da mudança encha com a mudança 
    if(provetas[jogada[1]].size() == tamanhoProveta)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            jogadasPermitidas[j][jogada[1]] == 0;
        }
    }

    // atualiza jogadasPermitidas se a proveta origem da mudança esvazie com a mudança
    if(provetas[jogada[0]].empty() == true)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            jogadasPermitidas[jogada[0]][j] = 0;   
            jogadasPermitidas[j][jogada[0]] = 1;             
        }
        jogadasPermitidas[jogada[0]][jogada[0]] = 0;
    }
}

void jogou(list<int> provetas[], int numeroProvetas, int tamanhoProveta, int **jogadasPermitidas, int jogada[])
{
    int aux = provetas[jogada[0]].back();
    provetas[jogada[0]].pop_back();
    provetas[jogada[1]].push_back(aux);
    jogadasPossiveisMID(provetas, numeroProvetas, tamanhoProveta, jogadasPermitidas, jogada);
}

void printjogadasPossiveis(int numeroProvetas, int **jogadasPermitidas)
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

    //mudar para char, pois nao tem diferença maior de uma bola da cor verde para uma de cor azul.
    list<int> provetas[numeroProvetas];
    //tenho que passar esses parametros como ponteiros
    inicializar(provetas, numeroProvetas, tamanhoProveta);
    print(provetas, numeroProvetas, tamanhoProveta);
    cout << isOver(provetas, numeroProvetas, tamanhoProveta) << endl;
    jogadasPossiveisInicio(provetas, numeroProvetas, tamanhoProveta, jogadasPermitidas);
    printjogadasPossiveis(numeroProvetas, jogadasPermitidas);     
    int jogada[2] = {2,3};
    jogou(provetas, numeroProvetas, tamanhoProveta, jogadasPermitidas, jogada);
    print(provetas, numeroProvetas, tamanhoProveta);
    printjogadasPossiveis(numeroProvetas, jogadasPermitidas);     
    free(jogadasPermitidas);

}

