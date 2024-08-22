#include "maquina.h"
#include <stack>

maquina::maquina(table table) : player::player(table.get_numero_provetas(), table.get_tamanho_proveta())
{
    vec_vec provetas = table.get_proveta();
    jogadas_permitas_c jogadas_permitas(table.get_numero_provetas());
    player::jogadas_possiveis_inicio(provetas, &jogadas_permitas);
    struct node no(provetas, jogadas_permitas);
    guarda_nodes.insert(std::pair<int, node>(heuristica(&no) - no.depth, no));       
    rodar_game();
};

int maquina::heuristica(node *no)
{
    int total = 0;
    for (int i = 0; i < player::get_numero_provetas(); i++)
    {
        if(no->provetas[i].empty() != true)
        {
            int j = 1;
            for (std::vector<int>::iterator it = no->provetas[i].end(); it != no->provetas[i].begin(); --it)
            {
                if(*it == *(no->provetas[i].begin()))
                    total = total + j;
                j++;
            }
        }
    }
    return total;
}

//confere se o no ja existe 
bool maquina::no_ja_existe(node *no)
{
    bool flag = true;
    for (std::list<node>::iterator it=nodes_vistados.begin(); it!=nodes_vistados.end(); ++it)
    {            
        for(int i = 0; i < player::get_numero_provetas(); i++)
        {
            if(it->provetas[i] != no->provetas[i])
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
void maquina::cria_filhos(vec_vec &provetas, jogadas_permitas_c *jp, node *no)
{
    for (int h = 0; h < player::get_numero_provetas(); h++)
    {
        for (int k = 0; k < player::get_numero_provetas(); k++)
        {
            if(no->jp.jogadas_permitidas[h][k] == 1)
            {
                player::jogada jogada(h,k);
                struct node noNew(jogada, no);
                player::jogou(noNew.provetas, &(noNew.jp), &jogada);
                if(no_ja_existe(&noNew) == false)
                {
                    guarda_nodes.insert(std::pair<int, node>(heuristica(&noNew) - noNew.depth, noNew));                    
                }
            }
        }
    }
}

void maquina::print_caminho(node* no){        
    std::stack<std::string> printer;
    if( no == nullptr)
    {

        std::cout<< "Não há solução" << std::endl;
    }
    else
    {    
        player::print(no->provetas);
        while(no->no_pai != nullptr)
        {   
            std::string s1("Coloque a bola do tubo ");
            s1 += std::to_string(no->jogada.origem + 1);
            s1 += " no tubo ";
            s1 += std::to_string(no->jogada.alvo + 1);
            s1 += "\n";
            printer.push(s1);
            std::cout << "X Coloque a bola do tubo " << no->jogada.origem + 1 << " no tubo " << no->jogada.alvo + 1<< std::endl;
            no = no->no_pai;
        }  
        while(printer.empty()== false)
        {
            std::cout << printer.top();
            printer.pop();
        }
    }
}

void maquina::rodar_game()
{
    std::list<maquina::node>::iterator it_nv;
    std::multimap<int,node>::iterator it_gn=guarda_nodes.end();
    it_gn--;
    while (is_over(it_gn->second.provetas) == false)
    {          
        nodes_vistados.push_back(it_gn->second);
        guarda_nodes.erase(it_gn);      
        it_nv = nodes_vistados.end();
        it_nv--;
        cria_filhos(it_nv->provetas, &(it_nv->jp), &(*it_nv));
        if(guarda_nodes.empty() == true)
        {        
            node *no = nullptr;
            print_caminho(no);
            return;
        }  
        it_gn=guarda_nodes.end(); 
        it_gn--;   
    }
    print_caminho(&(it_gn->second));
}