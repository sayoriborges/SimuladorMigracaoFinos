#ifndef CSIMULADORPARTICULAS_HPP
#define CSIMULADORPARTICULAS_HPP

#include "CGrid.cpp"
#include "CRocha.cpp"
#include "CParticulaFluido.cpp"

#include<vector>
#include<string>
#include<iostream>
#include<math.h>

class CSimuladorParticulas : public CParticulaFluido, CRocha {
private:
	size_t indiceTempoAtual = 0;
	size_t size_tempo = 100;
	size_t size_malha = 10001;
	double start_x = 0.0, end_x = 1.0, start_t = 0, end_t = 10.0;

	std::vector<double> tempo;
	std::vector<double> malha;

	std::vector<CGrid*> resultados_ao_longo_do_tempo;

public:
	/// CONSTRUTORES
	CSimuladorParticulas(std::string pathParticulaFluido, std::string pathRocha);

	/// 'MAIN' metodo, ele que esta executando o objeto
	void run();

	/// CALCULOS
private:
	double CalculoSigma_a(double x, double t);
	double CalculoDiffSigma_a(double x, double t);
	double CalculoLinhaZona(double x);
	double CalculoTb(double x);
	double CalculoConcentracoes(double x, double t);
	double CalculoConcentracoes_N_igual_1(double x, double t);
	double CalculoConcentracoes_N_diferente_1(double x, double t);

public:
	/// metodos para SALVAR e APRESENTAR os resultados
	void printCSimuladorParticulas();
	void print_vector(std::vector<double> vetor);

	void saveInFile(std::vector<double> vector1, std::string name_vector1);
	void saveInFile(std::vector<double> vector1, std::vector<double> vector2, std::string name_vector1, std::string name_vector2);

};
#endif
