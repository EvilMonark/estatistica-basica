#include "Estat.hpp"
#define RANDOM_SEED srand((unsigned int)time(NULL))
int main()
{
    RANDOM_SEED;
    std::fstream fs;
    est::Data<int> dado;
    est::construirConjuntoDeDadosAleatorio<int>(11,1000,fs,"Atividade_1.txt",dado);
    return 0;
}