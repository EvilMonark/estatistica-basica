#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <ctime>
#include <map>
#include <bits/stdc++.h>

#define RANDOM_SEED srand((unsigned int)time(NULL))
struct Aluno
{
    int idade;
};

template<typename T> struct Data
{
    std::vector<T> dados={0};
    float media=0;
    std::vector<float> moda;
    float mediana=0;
};


template<typename T>
void calcularParametros(Data<T> &dado)
{
    int highestCount = 1;
    std::sort(dado.dados.begin(), dado.dados.end());
    std::fstream sorted("Sorted.txt", std::fstream::out);
    sorted << "+---------------------------+\n";
    for (auto &dados:dado.dados)
    {
        sorted << dados<< "\n";
    }
    sorted.close();
    std::map<int, T> modaCont;
    for(auto &dados: dado.dados)
    {
        dado.media += dados;
        if(modaCont.find(dados) == modaCont.end())
        {
            modaCont[dados] = 1;
        }
        else
        {
            modaCont[dados] += 1;
            if(modaCont[dados] > highestCount)
            {
                highestCount = modaCont[dados];
            }
        }
    }
    dado.media /= dado.dados.size();
    //====================================//
    if(dado.dados.size()%2 ==1)
    {
        dado.mediana=dado.dados[floor((double)dado.dados.size()/2)+1];
    }
    else
    {
        dado.mediana= (dado.dados[dado.dados.size()/2]+ dado.dados[dado.dados.size()/2+1])/2;
    }
    //=====================================//
    for(auto &moda: modaCont)
    {
        if(moda.second == highestCount && highestCount > 1)
        {
            dado.moda.push_back(moda.first);
        }
    }
    std::fstream med;
    med.open("Medidas_Estatistica.txt",std::fstream::out);
    med << "Media: " << dado.media << "\n" << "Mediana: " << dado.mediana
    << "\nModa: ";
    if(dado.moda.empty())
    {
        med << "Amodal\n";
    }
    else
    {
        for(auto &moda: dado.moda)
        {
            med << moda << ", ";
            
        }
        med << "\0" ;
    }
    
    med.close();
}

template <typename T> 
void construirConjuntoDeDadosAleatorio(int ndados, int range, std::fstream &fs, const char* __filename, Data<T> &data, float offset=0.f)
{
    if(range == 0)
    {
        std::cout << "ERROR: DIVISION BY 0. TERMINATING...";
        std::exit(-1);
    }
    fs.open(__filename, std::fstream::out);
    data.dados.resize(ndados);
    fs << "+-------------------------------+" << "\n";
    for(auto &dado: data.dados)
    {
        dado = (rand()%range)+offset;
        fs<< dado << "\n";
    }
    fs.close();
    calcularParametros<T>(data);
}


int main()
{
    RANDOM_SEED;
    std::fstream fs;
    Data<int> dado;
    construirConjuntoDeDadosAleatorio<int>(11,1000,fs,"Atividade_1.txt",dado);
    return 0;
}