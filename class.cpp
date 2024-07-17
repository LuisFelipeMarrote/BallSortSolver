#include <iostream>
#include <list>
#include <vector>
#include <map>
#include "jogadas_permitidas_c.h"
#include "stopwatch.h"

using namespace std;

class ballsortsolver { 
private:
    struct jogada
    {
        int origem;
        int alvo;
        int corOrigem; // 0 é vazio outro natural positivo é uma cor
        int corAlvo; // 0 é vazio outro natural positivo é uma cor
        
        jogada(int i, int j)
        {
            origem = i;        
            alvo = j;        
        }
    };

    struct node
    {
        vector<list<int>> provetas;
        list<jogada> jogadas {};
        jogadas_permitas_c jp;
        int depth = 0; // nao preciso necessariamente posso usar o jogadas.size(), mas vou deixar por enquanto

        node(vector<list<int>> provetas_aux, jogadas_permitas_c jp_aux, int numero_provetas)
        {
            provetas.resize(numero_provetas);
            for(int i = 0; i < numero_provetas; i++)
                std::copy(provetas_aux[i].begin(),provetas_aux[i].end(),std::back_inserter(provetas[i]));
            jp.jogadas_permitidas = jp_aux.jogadas_permitidas;
        }

        node(int numero_provetas, jogada jogada, node *no)
        {
            provetas.resize(numero_provetas);
            for(int i = 0; i < numero_provetas; i++)
                std::copy(no->provetas[i].begin(),no->provetas[i].end(),std::back_inserter(this->provetas[i]));
            this->jp.jogadas_permitidas = no->jp.jogadas_permitidas;
            this->depth = depth;
            std::copy(no->jogadas.begin(), no->jogadas.end(), std::back_inserter(this->jogadas));
            this->jogadas.push_back(jogada);
        }
    };

    int tamanho_proveta;
    int numero_provetas;
    // armazenas as futuras jogadas na ordem em que eu vou tirar baseado no valor
    std::multimap<int, node> guarda_nodes;
    // armazenas os cenarios que eu ja cheguei
    std::vector<node> nodes_vistados;
public:
    // acho que a heuristica tem que levar em conta a profundidade da ultima bola comparada a do topo,
    // quantidades de bolas de cores diferentes e a posicao das bolas de outras cores.
    int heuristica(node *no, int numero_provetas)
    {
        int total = 0;
        for (int i = 0; i < numero_provetas; i++)
        {
            list<int>::iterator base = no->provetas[i].begin();
            int aux = *base;
            int j = 1;
            for (list<int>::iterator it = no->provetas[i].end(); it != no->provetas[i].begin(); --it)
            {
                if(*it == *base)
                    total = total + j;
                j++;
            }
        }
        return total;
    }

    void jogadas_possiveis_inicio(vector<list<int>> &provetas, int numero_provetas,  jogadas_permitas_c *jp)
    {
        for (int i = 0; i < numero_provetas; i++)
        {
            if(provetas[i].empty() == true)
            {
                for (int j = 0; j < numero_provetas; j++)
                {
                    if(provetas[j].empty() == false)
                    {
                        jp->jogadas_permitidas[j][i] = 1;   
                        jp->jogadas_permitidas[i][j] = 0;                       
                    }
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
    // nao esta funcionando
    // talvez seja interessante pensar depois numa estrutura que nao considere os tubos ja feitos
    // void jogadasPossiveisMID(vector<list<int>> &provetas, int numero_provetas, jogadas_permitas_c *jp, jogada *jogada)
    // {      
    //     // primeiro vou cobrir a proveta alvo
    //     // caso se a proveta alvo ficar cheia
    //     if(provetas[jogada->alvo].size() == tamanho_proveta)
    //     {
    //         for (int j = 0; j < numero_provetas; j++)
    //         {
    //             jp->jogadas_permitidas[j][jogada->alvo] = 0;
    //         }
    //     }
    //     // caso se a proveta alvo estava vazia
    //     else if (provetas[jogada->alvo].back() != jogada->corAlvo)
    //     {
    //         for (int j = 0; j < numero_provetas; j++)
    //         {
    //             if(provetas[j].back() == provetas[jogada->alvo].back())
    //             {
    //                 jp->jogadas_permitidas[j][jogada->alvo] = 1;
    //                 if(provetas[j].size() != tamanho_proveta)
    //                 {
    //                     jp->jogadas_permitidas[jogada->alvo][j] = 1;                    
    //                 }
    //                 else    
    //                 {
    //                     jp->jogadas_permitidas[jogada->alvo][j] = 0;                    
    //                 }
    //             }
    //             else 
    //             {
    //                 jp->jogadas_permitidas[j][jogada->alvo] = 0;
    //             }
    //             if(provetas[j].empty())
    //             {   
    //                 jp->jogadas_permitidas[jogada->alvo][j] = 1;                
    //             }
    //         }
    //         jp->jogadas_permitidas[jogada->alvo][jogada->alvo] = 0;
    //     } 
    //     // com a certeza que a proveta alvo esta correta, agora vou fazer a proveta origem 
    //     // caso se a proveta origem ficar vazia
    //     if(provetas[jogada->origem].empty() == true)
    //     {
    //         for (int j = 0; j < numero_provetas; j++)
    //         {
    //             jp->jogadas_permitidas[jogada->origem][j] = 0;   
    //             if(provetas[j].empty() == false)
    //                 jp->jogadas_permitidas[j][jogada->origem] = 1;             
    //         }
    //     }
    //     // caso nao fique vazia e a bola mude de cor 
    //     else if (provetas[jogada->origem].back() != jogada->corOrigem && provetas[jogada->origem].size() == tamanho_proveta - 1)
    //     {
    //         for (int j = 0; j < numero_provetas; j++)
    //         {
    //             if(provetas[j].back() == provetas[jogada->origem].back())
    //             {
    //                 jp->jogadas_permitidas[j][jogada->origem] = 1;
    //                 if(provetas[j].size() != tamanho_proveta)
    //                 {
    //                     jp->jogadas_permitidas[jogada->origem][j] = 1;
    //                 }
    //                 else
    //                 {
    //                     jp->jogadas_permitidas[jogada->origem][j] = 0;                    
    //                 }
    //             }
    //             else
    //             {
    //                 jp->jogadas_permitidas[j][jogada->origem] = 0;
    //             }
    //         }

    //     }
    //     // caso a proveta estava cheia 
    //     else if (provetas[jogada->origem].size() == tamanho_proveta - 1)
    //     {
    //             for (int j = 0; j < numero_provetas; j++)
    //             {
    //                 if(provetas[jogada->origem].back() == provetas[j].back() && jogada->origem != j && provetas[j].size() != tamanho_proveta)
    //                 {
    //                     jp->jogadas_permitidas[j][jogada->origem] = 1;                    
    //                 }
    //                 else
    //                 {
    //                     jp->jogadas_permitidas[j][jogada->origem] = 0;                      
    //                 }
    //             }
    //     }       
    //     // mais facil fazer uma substituiçao do que colocar mais condiçoes nos if's.
    //     jp->jogadas_permitidas[jogada->origem][jogada->origem] = 0;
    // }

    //Muda o tabuleiro e chama a funçao jogadas possiveis mid para atualizar a tabela de jogadas possiveis
    void jogou(vector<list<int>> &provetas, int numero_provetas, jogadas_permitas_c *jp, jogada *jogada)
    {
        jogada->corOrigem = provetas[jogada->origem].back();
        if(provetas[jogada->alvo].empty() == true)
            jogada->corAlvo = 0;            
        jogada->corAlvo = provetas[jogada->alvo].back();    
        provetas[jogada->origem].pop_back();
        provetas[jogada->alvo].push_back(jogada->corOrigem);
        jogadas_possiveis_inicio(provetas, numero_provetas, jp);
        //jogadasPossiveisMID(provetas, numero_provetas, jp, jogada);
    }

    void print_jogadas_possiveis(int numero_provetas, jogadas_permitas_c *jp)
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

    void print(vector<list<int>> &provetas, int numero_provetas)
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

    // confere se o jogo acabou
    // checa se todos as provetas estao preenchidas e com o mesmo numero
    bool is_over(vector<list<int>> &provetas, int numero_provetas)
    {
        cout << typeid(provetas).name();
        for (int i = 0; i < numero_provetas; i++)
        {
            if(provetas[i].size() == tamanho_proveta || provetas[i].empty() == true)
            {
                list<int>::iterator base = provetas[i].begin();
                for (list<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
                { 
                    if(*base != *it)
                    {
                        return false;
                    }
                }    
            }
            else 
            {
                return false;
            }
        }
        return true;
    }


    //inicializa as provetas
    void inicializar(vector<list<int>> &provetas, int numero_provetas)
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

    //confere se o no ja existe 
    bool no_ja_existe(node *no, int numero_provetas)
    {
        bool flag = true;
        for (std::vector<node>::iterator node=nodes_vistados.begin(); node!=nodes_vistados.end(); ++node)
        {            
            for(int i = 0; i < numero_provetas; i++)
            {
                if(node->provetas[i] != no->provetas[i])
                {
                    flag = false;
                }
            }
            if (flag)
                return true;
            else
                flag = true;
        }
        return false;
    }

    // feito com sucesso, posso mudar o parametro para passar so o node e o numero de provetas
    void cria_filhos(vector<list<int>> &provetas, jogadas_permitas_c *jp, node *no, int numero_provetas)
    {
        for (int h = 0; h < numero_provetas; h++)
        {
            for (int k = 0; k < numero_provetas; k++)
            {
                if(no->jp.jogadas_permitidas[h][k] == 1)
                {
                    struct jogada jogada(h,k);
                    struct node noNew (numero_provetas, jogada, no);
                    jogou(noNew.provetas, numero_provetas, &(noNew.jp), &jogada);
                    if(no_ja_existe(&noNew, numero_provetas) == false)
                    {
                        guarda_nodes.insert(std::pair<int, node>(heuristica(&noNew, numero_provetas) - noNew.depth, noNew));                    
                    }
                }
            }
        }
    }

    // resolve o jogo
    list<jogada> resolver(int numero_provetas)
    {
        std::multimap<int,node>::iterator it=guarda_nodes.end();
        it--;
        while (is_over(it->second.provetas, numero_provetas) == false)
        {               
            cria_filhos(it->second.provetas, &(it->second.jp), &(it->second), numero_provetas);
            nodes_vistados.push_back(it->second);
            guarda_nodes.erase (it); 
            if(guarda_nodes.empty() == true)
            {
                list<jogada> vazio = {};        
                return vazio;
            }  
            it=guarda_nodes.end(); 
            it--;   
        }
        print(it->second.provetas,numero_provetas);
        return it->second.jogadas;
    }

    void print_caminho(list<jogada> caminho){
        if(caminho.empty() == true)
            cout<< "Não há solução";
        else
        {
            for (std::list<jogada>::iterator it=caminho.begin(); it != caminho.end(); ++it)
            {   
                cout << "Coloque a bola do tubo " << it->origem + 1 << " no tubo " << it->alvo + 1<< endl;
            }    
        }
    }
};
