#include "manual.h"
#include "Scenario.h"
#include "maquina.h"

int main()
{
    vec_vec provetas {{1,1,1,1},{2,2,2},{2}};
    int numero_provetas = 3, tamanho_proveta = 4;
    Scenario scenario_i;
    bool flag = true;
    do
    {
        maquina maquina_i (scenario_i.get_table());
        //fazer um menu e dar clear screen 
    } while (flag);
    return 0;
}