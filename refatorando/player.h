//tenho que mudar isso para receber aa table e setar numero_provetas e tamanho_proveta, alem de provestas
//vou mudar a forma com que faço o node, vou tirar jogadas e mudar para que ele seja so as provetas
//tenho que adicionar no node um ponteiro para o pai nesse caso 

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include "jogadas_permitidas_c.h"
#include "table.h"

typedef std::vector<std::vector<int>> vec_vec;

#pragma once

class player
{

/****************************************************************/
//Variables

public:
    struct jogada
    {
        int origem;
        int alvo;
        
        jogada(int i, int j)
        {
            origem = i;        
            alvo = j;        
        }
        jogada(){}
    };

private:
    int numero_provetas;
    int tamanho_proveta;

/****************************************************************/
//Funticions

protected:
    //tenho que iniciar a função resolver aqui e passar as provetas como parametro
    player(int numero_provetas, int tamanho_proveta);
    void print_jogadas_possiveis(jogadas_permitas_c *jp);
    void print(vec_vec &provetas);
    void jogadas_possiveis_inicio(vec_vec &provetas, jogadas_permitas_c *jp);
    //muda o tabuleiro e chama a funçao jogadas possiveis inicio para atualizar a tabela de jogadas possiveis
    void jogou(vec_vec &provetas, jogadas_permitas_c *jp, jogada *jogada);
    int get_numero_provetas();
    int get_tamanho_proveta();
    // confere se o jogo acabou
    // checa se todos as provetas estao preenchidas e com o mesmo numero
    bool is_over(vec_vec &provetas);
public:
    virtual void rodar_game() = 0;
};