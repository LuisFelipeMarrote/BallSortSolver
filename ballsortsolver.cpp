#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct jogada
{
    int origem;
    int alvo;
    int corOrigem; // 0 é vazio outro natural positivo é uma cor
    int corAlvo; // 0 é vazio outro natural positivo é uma cor
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
        else 
        {
            for (int j = 0; j < numeroProvetas; j++)
            {
                if(provetas[i].back() == provetas[j].back() && i != j && provetas[j].size() != tamanhoProveta)
                    jogadasPermitidas[i][j] = 1;
                else 
                    jogadasPermitidas[i][j] = 0;                
            }
        }
    }
}

// funçao para a atualizar aas jogdas permitidas  
// talvez seja interessante pensar depois numa estrutura que nao considere os tubos ja feitos
void jogadasPossiveisMID(list<int> provetas[], int numeroProvetas, int tamanhoProveta, int **jogadasPermitidas, jogada *jogada)
{      
    // primeiro vou cobrir a proveta alvo
    // caso se a proveta alvo ficar cheia
    if(provetas[jogada->alvo].size() == tamanhoProveta)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            jogadasPermitidas[j][jogada->alvo] = 0;
        }
    }
    // caso se a proveta alvo estava vazia
    else if (provetas[jogada->alvo].back() != jogada->corAlvo)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            if(provetas[j].back() == provetas[jogada->alvo].back())
            {
                jogadasPermitidas[j][jogada->alvo] = 1;
                if(provetas[j].size() != tamanhoProveta)
                {
                    jogadasPermitidas[jogada->alvo][j] = 1;                    
                }
                else    
                {
                    jogadasPermitidas[jogada->alvo][j] = 0;                    
                }
            }
            else
            {
                jogadasPermitidas[j][jogada->alvo] = 0;
            }
        }
        jogadasPermitidas[jogada->alvo][jogada->alvo] = 0;
    } 
    // com a certeza que a proveta alvo esta correta, agora vou fazer a proveta origem 
    // caso se a proveta origem ficar vazia
    if(provetas[jogada->origem].empty() == true)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            jogadasPermitidas[jogada->origem][j] = 0;   
            jogadasPermitidas[j][jogada->origem] = 1;             
        }
    }
    // caso nao fique vazia e a bola mude de cor 
    else if (provetas[jogada->origem].back() != jogada->corOrigem)
    {
        for (int j = 0; j < numeroProvetas; j++)
        {
            if(provetas[j].back() == provetas[jogada->origem].back())
            {
                jogadasPermitidas[j][jogada->origem] = 1;
                if(provetas[j].size() != tamanhoProveta)
                {
                    jogadasPermitidas[jogada->origem][j] = 1;
                }
                else
                {
                    jogadasPermitidas[jogada->origem][j] = 0;                    
                }
            }
            else
            {
                jogadasPermitidas[j][jogada->origem] = 0;
            }
        }
        // mais facil fazer uma substituiçao do que colocar mais condiçoes nos if's.
    }
    // caso a proveta estava cheia 
    else if (provetas[jogada->origem].size() == tamanhoProveta - 1)
    {
            for (int j = 0; j < numeroProvetas; j++)
            {
                if(provetas[jogada->origem].back() == provetas[j].back() && jogada->origem != j && provetas[j].size() != tamanhoProveta)
                {
                    jogadasPermitidas[j][jogada->origem] = 1;                    
                }
                else
                {
                    jogadasPermitidas[j][jogada->origem] = 0;                      
                }
            }
    }
    
    jogadasPermitidas[jogada->origem][jogada->origem] = 0;

}

void jogou(list<int> provetas[], int numeroProvetas, int tamanhoProveta, int **jogadasPermitidas, jogada *jogada)
{
    jogada->corOrigem = provetas[jogada->origem].back();
    if(provetas[jogada->alvo].empty() == true)
        jogada->corAlvo = 0;            
    jogada->corAlvo = provetas[jogada->alvo].back();    
    provetas[jogada->origem].pop_back();
    provetas[jogada->alvo].push_back(jogada->corOrigem);
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
    jogada jogada = {2,3};
    jogou(provetas, numeroProvetas, tamanhoProveta, jogadasPermitidas, &jogada);
    print(provetas, numeroProvetas, tamanhoProveta);
    printjogadasPossiveis(numeroProvetas, jogadasPermitidas);     
    free(jogadasPermitidas);

}

