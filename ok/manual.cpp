#include "manual.h"

manual::manual(int numero_provetas, int tamanho_proveta, vec_vec &provetas_aux) : player::player(numero_provetas, tamanho_proveta)
{
    vec_vec provetas;
    provetas.resize(numero_provetas);
    for(int i = 0; i < numero_provetas; i++)
        std::copy(provetas_aux[i].begin(),provetas_aux[i].end(),std::back_inserter(provetas[i]));
    jogadas_permitas_c jogadas_permitas;
    player::jogadas_possiveis_inicio(provetas_aux, &jogadas_permitas);
    std::cout<<"oi" << std::endl;
    rodar_game(provetas, &jogadas_permitas);
};

player::jogada manual::cria_jogada()
{
    player::jogada jogada;
    std::cout << "Tubo origem(A bola vai sair desse tubo): " << std::endl;  
    std::cin >> jogada.origem;      
    std::cout << "Tubo alvo(A bola vai para esse tubo): " << std::endl;
    std::cin >> jogada.alvo;
    return jogada;
}

bool manual::checa_jogada(vec_vec &provetas, jogadas_permitas_c *jogadas_permitas, player::jogada jogada)
{
    if(provetas[jogada.origem][jogada.alvo] == 1)
    {
        return true;
    }
    return false;
}

bool manual::continuar_jogando()
{
    char jogar = 'a';
    do{        
        std::cout << "Você quer continuar jogando ('s' ou 'n')?" << std::endl;
        std::cin >> jogar;
    }while(jogar != 's' && jogar != 'n');
    if (jogar == 's')
    {
        return true;
    }
    return false;
}

void manual::rodar_game(vec_vec &provetas, jogadas_permitas_c *jogadas_permitas)
{
    bool flag = true;

    while(player::is_over(provetas) && flag == true)
    {
        player::print(provetas);
        jogada jogada = cria_jogada();
        if(checa_jogada(provetas, jogadas_permitas, jogada))
        {
            player::jogou(provetas, jogadas_permitas, &jogada);            
            player::jogadas_possiveis_inicio(provetas, jogadas_permitas);
        } 
        else
        {
            std::cout << "Essa jogada é ilegal" << std::endl;
        }
        flag = continuar_jogando();
    }
    player::print(provetas);
}
