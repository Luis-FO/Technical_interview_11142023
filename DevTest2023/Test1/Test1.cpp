// 09/11/2023
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>  
#include <numeric>   
#include <cmath>    

using std::vector;
using std::string;

struct DataStats
{
    float Min;
    float Max;
    float Mean;
    float Std;
    int Count;
};

void ReadFromPath(vector<float>& data, const string& filename)
{
	//Criar instância para o arquivo
    std::ifstream file(filename);
    string line;
	float aux;
	//Pega linha por linha do arquivo
    while (std::getline(file, line))
    {
        try
        {	
			//Segundo a documentação -> Interprets a floating point value in a string 
            float value = std::stof(line);
			//Se não for nan armazena em data
			if(!std::isnan(value)){
				data.push_back(value);
			}
        }
        catch (const std::invalid_argument&)
        {
            //mesmo quando entra no catch, algo é armazenado em data
			//Então adicionei essa linha para remover
			data.pop_back();
        }
    }
}

void GetStats(DataStats &stats, vector<float>& data)
{

	//Soma para a média
    float soma = std::accumulate(data.begin(), data.end(), 0.0);
	//Média,  min, max
	stats.Mean = soma / data.size();
	stats.Min = *std::min_element(data.begin(), data.end());
	stats.Max = *std::max_element(data.begin(), data.end());
	//soma dos quadrados das diferencas
	double somaQuadradosDiferencas = 0.0;
    for (const auto& numero : data) {
        double diferenca = numero - stats.Mean;
        somaQuadradosDiferencas += diferenca * diferenca;
    }


    double variancia = somaQuadradosDiferencas / data.size();
    //std
	stats.Std  = std::sqrt(variancia);
	//Contagem de dados
	stats.Count = data.size();
}


int main()
{
    vector<float> data;
    ReadFromPath(data, "/home/luisfernando/Área de Trabalho/Teste/DevTest2023/Test1/Data.txt");
    DataStats statss;
	GetStats(statss, data);
	
	//Imprime as estatísticas
	std::cout << "Min: " << statss.Min << std::endl;
    std::cout << "Max: " << statss.Max << std::endl;
    std::cout << "Mean: " << statss.Mean << std::endl;
    std::cout << "Std: " << statss.Std << std::endl;
    std::cout << "Count: " << statss.Count << std::endl;
    return 0;
}
