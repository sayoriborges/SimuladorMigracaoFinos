#ifndef CPARTICULAFLUIDO_HPP
#define CPARTICULAFLUIDO_HPP

#include <fstream>
#include <iostream>
#include <string>

class CParticulaFluido {
protected:
	double viscosidade;
	double lambdaPonte;
	double lambdaAdesao;
	double parC;
	double par_n;
	double velocidade;
	double C = 2.0;
	double cb = 0.0004;

	void readFile(std::string path);

public:
	//CParticulaFluido() {}
	// construtores por vari�veis e por nome do arquivo txt
	CParticulaFluido(double _mu, double _lambdaPonte, double _lambdaAdesao, double _parC, double _par_n, double _velocidade):
		viscosidade{ _mu }, lambdaPonte{ _lambdaPonte }, lambdaAdesao{ _lambdaAdesao }, parC{ _parC }, par_n{ _par_n }, velocidade{ _velocidade } {}

	CParticulaFluido(std::string path) { readFile(path); }

	// fun��es get-set
	double getViscosidade() { return viscosidade; };
	void setViscosidade(double novo_mu) { viscosidade = novo_mu; }

	double getLambdaPonte() { return lambdaPonte; }
	double getLambdaAdesao() { return lambdaAdesao; }
	double getParC() { return parC; }
	double getParN() { return par_n; }
	double getVelocidade() { return velocidade; }

	// fun��o para mostrar os par�metros da classe
	void printCParticulaFluido();
};

#endif
