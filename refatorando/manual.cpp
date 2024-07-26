#include "manual.h"

manual::manual(int numero_provetas, int tamanho_proveta, vec_vec &provetas_aux) : player::player(numero_provetas, tamanho_proveta)
{
    vec_vec provetas = provetas_aux;
    jogadas_permitas_c jogadas_permitas(numero_provetas);
    player::jogadas_possiveis_inicio(provetas_aux, &jogadas_permitas);
    rodar_game(provetas, &jogadas_permitas);
};

manual::manual(table table) : player::player(table.get_numero_provetas(), table.get_tamanho_proveta())
{
    vec_vec provetas = table.get_proveta();
    jogadas_permitas_c jogadas_permitas(table.get_numero_provetas());
    player::jogadas_possiveis_inicio(provetas, &jogadas_permitas);
    rodar_game(provetas, &jogadas_permitas);
};

player::jogada manual::cria_jogada()
{
    player::jogada jogada;
    std::cout << "Tubo origem(A bola vai sair desse tubo): " << std::endl;  
    std::cin >> jogada.origem;      
    std::cout << "Tubo alvo(A bola vai para esse tubo): " << std::endl;
    std::cin >> jogada.alvo;
    jogada.origem -= 1;
    jogada.alvo -= 1;    
    return jogada;
}

bool manual::checa_jogada(vec_vec &provetas, jogadas_permitas_c *jogadas_permitas, player::jogada jogada)
{
    int tam = player::get_numero_provetas();
    if(jogada.alvo >= player::get_numero_provetas() || jogada.alvo < 0)
    {
        return false;
    }
    if(jogada.origem >= player::get_numero_provetas() || jogada.origem < 0)
    {
        return false;
    }
    if(jogadas_permitas->jogadas_permitidas[jogada.origem][jogada.alvo] == 1)
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

    while(player::is_over(provetas) == false && flag == true)
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
            std::cout << "\n";
            std::cout << "Essa jogada é ilegal" << std::endl;        
            flag = continuar_jogando();
        }
    }
    player::print(provetas);
}
