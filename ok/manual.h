#include "player.h"

typedef std::vector<std::vector<int>> vec_vec;

#pragma once 

class manual : public player
{

/****************************************************************/
//Funticions

public:

    manual(int numero_provetas, int tamanho_proveta, vec_vec &provetas_aux);
    player::jogada cria_jogada();
    bool checa_jogada(vec_vec &provetas, jogadas_permitas_c *jogadas_permitas, player::jogada jogada);
    bool continuar_jogando();
    void rodar_game(vec_vec &provetas, jogadas_permitas_c *jogadas_permitas);
};