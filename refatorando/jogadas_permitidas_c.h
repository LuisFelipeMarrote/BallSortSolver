#include <vector>

#pragma once 

class jogadas_permitas_c
{
public:
    std::vector<std::vector<int>> jogadas_permitidas;
    jogadas_permitas_c(int numero_provetas)
    {        
        jogadas_permitidas.resize(numero_provetas);
        for (int i = 0; i < numero_provetas; i++)
        {
            jogadas_permitidas[i].resize(numero_provetas);
        }
    }
    jogadas_permitas_c(){}
};