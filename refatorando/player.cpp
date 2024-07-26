#include "player.h"

player::player(int numero_provetas, int tamanho_proveta)
{
    this->numero_provetas = numero_provetas;
    this->tamanho_proveta = tamanho_proveta;
}

int player::get_numero_provetas()
{
    return this->numero_provetas;
}

int player::get_tamanho_proveta()
{
    return this->tamanho_proveta;
}

void player::print_jogadas_possiveis(jogadas_permitas_c *jp)
{
    for (int i = 0; i < numero_provetas; i++)
    {
        for (int j = 0; j < numero_provetas; j++)
        {
            std::cout << jp->jogadas_permitidas[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void player::print(vec_vec &provetas)
{
    std::cout << "\n";
    for (int i = 0; i < numero_provetas; i++)
    {
        for (std::vector<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
        {
            std::cout << *it;
        }
    std::cout << std::endl;
    }
    std::cout << "\n";
}

void player::jogadas_possiveis_inicio(vec_vec &provetas, jogadas_permitas_c *jp)
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
                if(provetas[j].empty() == false && provetas[i].back() == provetas[j].back() && i != j && provetas[j].size() != tamanho_proveta)
                    jp->jogadas_permitidas[i][j] = 1;
                else 
                    jp->jogadas_permitidas[i][j] = 0;                
            }
        }
    }
}

//muda o tabuleiro e chama a funçao jogadas possiveis inicio para atualizar a tabela de jogadas possiveis
void player::jogou(vec_vec &provetas, jogadas_permitas_c *jp, jogada *jogada)
{
    provetas[jogada->alvo].push_back(provetas[jogada->origem].back());
    provetas[jogada->origem].pop_back();
    jogadas_possiveis_inicio(provetas, jp);
}

// confere se o jogo acabou
// checa se todos as provetas estao preenchidas e com o mesmo numero
bool player::is_over(vec_vec &provetas)
{
    for (int i = 0; i < numero_provetas; i++)
    {
        if(provetas[i].size() == tamanho_proveta || provetas[i].empty() == true)
        {
            std::vector<int>::iterator base = provetas[i].begin();
            for (std::vector<int>::iterator it = provetas[i].begin(); it != provetas[i].end(); ++it)
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

