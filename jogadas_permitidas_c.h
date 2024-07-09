#include <vector>
class jogadas_permitas_c
{
    public:
        int numero_provetas;  
        std::vector<std::vector<int>> jogadas_permitidas;
    jogadas_permitas_c()
    {
        jogadas_permitidas.resize(numero_provetas);
        this->numero_provetas = numero_provetas;
        for (int i = 0; i < numero_provetas; i++)
        {
            jogadas_permitidas[i].resize(numero_provetas);
        }
    }
};