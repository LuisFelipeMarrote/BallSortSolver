#include "player.h"

typedef std::vector<std::vector<int>> vec_vec;

#pragma once

class maquina : public player
{
    
/****************************************************************/
//Variables
public: 
    struct node
    {
        vec_vec provetas;
        jogadas_permitas_c jp;
        int depth = 0; // nao preciso necessariamente posso usar o jogadas.size(), mas vou deixar por enquanto
        node *no_pai;
        jogada jogada {}; 

        node(vec_vec provetas_aux, jogadas_permitas_c jp_aux)
        {
            this->provetas = provetas_aux;
            this->jp.jogadas_permitidas = jp_aux.jogadas_permitidas;
            this->no_pai = nullptr;
        }

        node(player::jogada jogada, node *no_pai)
        {
            this->provetas = no_pai->provetas;
            this->jp.jogadas_permitidas = no_pai->jp.jogadas_permitidas;
            this->depth = no_pai->depth + 1;
            this->no_pai = no_pai;
            this->jogada = jogada;
        }
        node(){}
    };

private:
    // armazenas as futuras jogadas na ordem em que eu vou tirar baseado no valor
    std::multimap<int, node> guarda_nodes;
    // armazenas os cenarios que eu ja cheguei, isso daqui tem que ser lista 
    std::list<node> nodes_vistados;
    // Agora faz sentido o porque lista é usada para quando não sabemos quantos itens teremos e vector usado principalmente
    // para alocar dinamicamente, mas quando é necessário acesso aleatorio. Ambos podem aumentar de tamanho, mas o vector pode 
    // redefinir a alocação sempre que há inserção e remoção (pop e push), ou seja, o iterador pode ser realocado "Iterator Va-
    // lidity".
    
/****************************************************************/
//Funticions

public:
    maquina (table table);
    int heuristica(node *no);
    bool no_ja_existe(node *no);
    void cria_filhos(vec_vec &provetas, jogadas_permitas_c *jp, node *no);
    void print_caminho(node* no);    
    void rodar_game() override;
};