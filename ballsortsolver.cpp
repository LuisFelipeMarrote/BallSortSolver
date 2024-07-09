#include <iostream>
#include <list>
#include <vector>
#include <map>
#include "jogadas_permitidas_c.h"

using namespace std;

int const tamanho_proveta = 5;

struct node
{
    list<int> provetas[tamanho_proveta];
    jogadas_permitas_c jp;
    node *prev = 0;
    int depth = 0;

    void construc(list<int> provetas_aux[tamanho_proveta], jogadas_permitas_c jp_aux, node *prev, int depth, int numero_provetas)
    {
        for(int i = 0; i < numero_provetas; i++)
            std::copy(provetas_aux[i].begin(),provetas_aux[i].end(),std::back_inserter(provetas[i]));
        jp.numero_provetas = numero_provetas;
        *prev = *prev;
        depth = depth;
    }
};



struct jogada
{
    int origem;
    int alvo;
    int corOrigem; // 0 é vazio outro natural positivo é uma cor
    int corAlvo; // 0 é vazio outro natural positivo é uma cor
};


// acho que a heuristica tem que levar em conta a profundidade da ultima bola comparada a do topo,
// quantidades de bolas de cores diferentes e a posicao das bolas de outras cores.
int heuristica(list<int> provetas[], int numero_provetas)
{
    int total = 0;
    for (int i = 0; i < numero_provetas; i++)
    {
        list<int>::iterator base = provetas[i].begin();
        int aux = *base;
        int j = 1;
        for (list<int>::iterator it = provetas[i].end(); it != provetas[i].begin(); --it)
        {
            //total = total + abs(aux - *it)*j;
            j++;
        }
    }
    return total;
}

void jogadasPossiveisInicio(list<int> provetas[], int numero_provetas,  jogadas_permitas_c *jp)
{
    for (int i = 0; i < numero_provetas; i++)
    {
        if(provetas[i].empty() == true)
        {
            for (int j = 0; j < numero_provetas; j++)
            {
                jp->jogadas_permitidas[j][i] = 1;   
                jp->jogadas_permitidas[i][j] = 0;               
            }
            jp->jogadas_permitidas[i][i] = 0;
        } 
        else 
        {
            for (int j = 0; j < numero_provetas; j++)
            {
                if(provetas[i].back() == provetas[j].back() && i != j && provetas[j].size() != tamanho_proveta)
                    jp->jogadas_permitidas[i][j] = 1;
                else 
                    jp->jogadas_permitidas[i][j] = 0;                
            }
        }
    }
}

// funçao para a atualizar aas jogdas permitidas  
// talvez seja interessante pensar depois numa estrutura que nao considere os tubos ja feitos
void jogadasPossiveisMID(list<int> provetas[], int numero_provetas, jogadas_permitas_c *jp, jogada *jogada)
{      
    // primeiro vou cobrir a proveta alvo
    // caso se a proveta alvo ficar cheia
    if(provetas[jogada->alvo].size() == tamanho_proveta)
    {
        for (int j = 0; j < numero_provetas; j++)
        {
            jp->jogadas_permitidas[j][jogada->alvo] = 0;
        }
    }
    // caso se a proveta alvo estava vazia
    else if (provetas[jogada->alvo].back() != jogada->corAlvo)
    {
        for (int j = 0; j < numero_provetas; j++)
        {
            if(provetas[j].back() == provetas[jogada->alvo].back())
            {
                jp->jogadas_permitidas[j][jogada->alvo] = 1;
                if(provetas[j].size() != tamanho_proveta)
                {
                    jp->jogadas_permitidas[jogada->alvo][j] = 1;                    
                }
                else    
                {
                    jp->jogadas_permitidas[jogada->alvo][j] = 0;                    
                }
            }
            else
            {
                jp->jogadas_permitidas[j][jogada->alvo] = 0;
            }
        }
        jp->jogadas_permitidas[jogada->alvo][jogada->alvo] = 0;
    } 
    // com a certeza que a proveta alvo esta correta, agora vou fazer a proveta origem 
    // caso se a proveta origem ficar vazia
    if(provetas[jogada->origem].empty() == true)
    {
        for (int j = 0; j < numero_provetas; j++)
        {
            jp->jogadas_permitidas[jogada->origem][j] = 0;   
            jp->jogadas_permitidas[j][jogada->origem] = 1;             
        }
    }
    // caso nao fique vazia e a bola mude de cor 
    else if (provetas[jogada->origem].back() != jogada->corOrigem && provetas[jogada->origem].size() == tamanho_proveta - 1)
    {
        for (int j = 0; j < numero_provetas; j++)
        {
            if(provetas[j].back() == provetas[jogada->origem].back())
            {
                jp->jogadas_permitidas[j][jogada->origem] = 1;
                if(provetas[j].size() != tamanho_proveta)
                {
                    jp->jogadas_permitidas[jogada->origem][j] = 1;
                }
                else
                {
                    jp->jogadas_permitidas[jogada->origem][j] = 0;                    
                }
            }
            else
            {
                jp->jogadas_permitidas[j][jogada->origem] = 0;
            }
        }

    }
    // caso a proveta estava cheia 
    else if (provetas[jogada->origem].size() == tamanho_proveta - 1)
    {
            for (int j = 0; j < numero_provetas; j++)
            {
                if(provetas[jogada->origem].back() == provetas[j].back() && jogada->origem != j && provetas[j].size() != tamanho_proveta)
                {
                    jp->jogadas_permitidas[j][jogada->origem] = 1;                    
                }
                else
                {
                    jp->jogadas_permitidas[j][jogada->origem] = 0;                      
                }
            }
    }       
    // mais facil fazer uma substituiçao do que colocar mais condiçoes nos if's.
    jp->jogadas_permitidas[jogada->origem][jogada->origem] = 0;
}

void jogou(list<int> provetas[], int numero_provetas, jogadas_permitas_c *jp, jogada *jogada)
{
    jogada->corOrigem = provetas[jogada->origem].back();
    if(provetas[jogada->alvo].empty() == true)
        jogada->corAlvo = 0;            
    jogada->corAlvo = provetas[jogada->alvo].back();    
    provetas[jogada->origem].pop_back();
    provetas[jogada->alvo].push_back(jogada->corOrigem);
    jogadasPossiveisMID(provetas, numero_provetas, jp, jogada);
}

void printjogadasPossiveis(int numero_provetas, jogadas_permitas_c *jp)
{
    for (int i = 0; i < numero_provetas; i++)
    {
        for (int j = 0; j < numero_provetas; j++)
        {
            cout << jp->jogadas_permitidas[i][j] << " ";
        }
        cout << endl;
    }
}

void print(list<int> provetas[], int numero_provetas)
{
    for (int i = 0; i < numero_provetas; i++)
    {
        for (list<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
        {
            cout << *it;
        }
    cout << endl;
    }
}

bool isOver(list<int> provetas[], int numero_provetas)
{
    for (int i = 0; i < numero_provetas; i++)
    {
        if (provetas[i].size() != tamanho_proveta){
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



void inicializar(list<int> provetas[], int numero_provetas)
{
    int aux;
    for (int i = 0; i < numero_provetas; i++)
    {
        while(provetas[i].size() < tamanho_proveta)
        {        
            cout << "Insira na posição da proveta " << i << " ou digite 0 para acabar: " << endl;
            cin >> aux;    
            if (aux == 0)
                break;
            provetas[i].push_back(aux);
        }
    }
}

// void cria_node(list<int> provetas[], jogadas_permitas_c *jp, node *prev, int numero_provetas)
// {
//     struct node no;
//     no.construc(provetas, *jp, prev, prev->depth, numero_provetas);
//     print(no.provetas, numero_provetas);
//     printjogadasPossiveis(numero_provetas, &(no.jp));
// }

// void arvore()
// {

// }

// falta implementar como se escolhe a jogada e a arvore. mas nao falta mt
int main ()
{
    int numero_provetas;
    cout << "Quantas provetas serão: ";
    cin >> numero_provetas;

    jogadas_permitas_c jp;

    //mudar para char, pois nao tem diferença maior de uma bola da cor verde para uma de cor azul.
    list<int> provetas[numero_provetas];

    struct node a;

    //tenho que passar esses parametros como ponteiros
    inicializar(provetas, numero_provetas);
    jogadasPossiveisInicio(provetas, numero_provetas, &jp);
    //cria_node(provetas, &jp, &a, numero_provetas);
    print(provetas, numero_provetas);
    //printjogadasPossiveis(numero_provetas, &jp);     
}

