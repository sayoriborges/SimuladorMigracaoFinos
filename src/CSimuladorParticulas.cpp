#include "CSimuladorParticulas.hpp"

CSimuladorParticulas::CSimuladorParticulas(std::string pathParticulaFluido, std::string pathRocha):CParticulaFluido(pathParticulaFluido), CRocha(pathRocha) {
	tempo = CGrid::linspace(start_t, end_t, size_tempo); /// nao eh objeto CGrid, eh vetor - metodo static
	malha = CGrid::linspace(start_x, end_x, size_malha);
	/// inicio as malhas
	resultados_ao_longo_do_tempo.resize(size_tempo);
	for (unsigned int i = 0; i < size_tempo; i++)
		resultados_ao_longo_do_tempo[i] = new CGrid(size_malha);
}

void CSimuladorParticulas::run() {
	int nx = resultados_ao_longo_do_tempo[0]->get_size();
	std::vector<double>linhazona(nx);
	std::vector<double>tb(nx);

	for (unsigned int j = 0; j < size_tempo; j++) { /// loop dos tempos
		//malhas_ao_longo_do_tempo[j]->sigma_a = CalculoSigma_a(malhas_ao_longo_do_tempo[j]->get_posicoes(), tempo[j]);
		for (unsigned int i = 0; i < nx; i++) {
			/// na linha abaixo, estou colocando o valor do 'calculo' dentro da variavel sigma_a da respectiva malha/grid
			resultados_ao_longo_do_tempo[j]->sigma_a[i] = CalculoSigma_a(malha[i], tempo[j]);
			resultados_ao_longo_do_tempo[j]->diff_sigma_a[i] = CalculoDiffSigma_a(malha[i], tempo[j]);
			resultados_ao_longo_do_tempo[j]->concentracao[i] = CalculoConcentracoes(malha[i], tempo[j]);
			linhazona[i] = CalculoLinhaZona(malha[i]);
			tb[i] = CalculoTb(malha[i]);
		}
		resultados_ao_longo_do_tempo[j]->saveGrid(malha, tempo[j]);
	}
	std::cout << "Vetor de tb: " << std::endl;
	saveInFile(tempo, "tempo");
	saveInFile(malha, "grid");
	
}

/// abaixo estao os calculos do simulador

double CSimuladorParticulas::CalculoSigma_a(double x, double t){
	if (N == 1) {
		if (t < (x * porosidade / velocidade))
			return sigma_a0;
		else {
			return sigma_am + (sigma_a0 - sigma_am) * exp(-parC * (t - x * porosidade / velocidade));
		}
	}	
	else {
		if (t < (x * porosidade / velocidade))
			return sigma_a0;
		else {
			return pow(sigma_am+pow(sigma_a0-sigma_am, 1- N) - parC *(1- N)*(t-x* porosidade / velocidade), N / (1- N));
		}
	}
}

double CSimuladorParticulas::CalculoDiffSigma_a(double x, double t) {
	if (N == 1) {
		if (t < (x * porosidade / velocidade))
			return 0.0;
		else {
			return -parC *(sigma_a0 - sigma_am) * exp(-parC * (t - x * porosidade / velocidade));
		}
	}
	else {
		if (t < (x * porosidade / velocidade))
			return 0.0;
		else {
			return -parC *pow( pow(sigma_a0 - sigma_am, 1 - N) - parC * (1 - N) * (t - x * porosidade / velocidade), N / (1 - N));
		}
	}
}

double CSimuladorParticulas::CalculoLinhaZona(double x) {
	return porosidade * x / velocidade;
}

double CSimuladorParticulas::CalculoTb(double x) {
	double cb = 0.0004; /// rocha
	double linhaZona = CalculoLinhaZona(x);

	double tb;
	if (N == 1)
		tb = linhaZona + (1/ parC) * log(parC *(sigma_a0 - sigma_am)*(1-exp(-lambdaPonte *x))/(cb* velocidade * lambdaPonte));
	else
		tb = 2 * linhaZona + pow(sigma_a0 - sigma_am, 1 - N) / (parC * (1 - N)) - (1 / (parC * (1 - N))) * pow(lambdaPonte * velocidade * cb / (parC * (1 - exp(-x * lambdaPonte))), (1 - N) / N);

	return tb;
}

double CSimuladorParticulas::CalculoConcentracoes(double x, double t) {
	if (N == 1)
		return CalculoConcentracoes_N_igual_1(x, t);
	else
		return CalculoConcentracoes_N_diferente_1(x, t);
}

double CSimuladorParticulas::CalculoConcentracoes_N_igual_1(double x, double t) {
	double concentracao;
	if (t < CalculoTb(x))
		concentracao = 0.0;
	else {
		if (C < cb)
			concentracao = C * (sigma_a0 - sigma_am) * exp(-C * (t - CalculoTb(x))) * (1 - exp(-lambdaAdesao * x)) / (velocidade * lambdaAdesao);
		else
			concentracao = C * (sigma_a0 - sigma_am) * exp(-C * t - CalculoTb(x)) / (velocidade * (lambdaAdesao + lambdaPonte)) * (1 - (1 - velocidade * (lambdaAdesao + lambdaPonte) * cb / (C * (sigma_a0 - sigma_am) * exp(-C * (t - CalculoTb(x))))) / pow(1 - velocidade * lambdaAdesao * cb / (C * (sigma_a0 - sigma_am) * exp(-C * (t - CalculoTb(x)))), 1 + lambdaPonte / lambdaAdesao) * exp((lambdaAdesao + lambdaPonte) * x));
	}
	return concentracao;
}

double CSimuladorParticulas::CalculoConcentracoes_N_diferente_1(double x, double t) {
	double concentracao;
	if (t < CalculoTb(x))
		concentracao = 0.0;
	else {
		if (C < cb)
			concentracao = C * pow(pow(sigma_a0 - sigma_am, 1 - N) - C * (1 - N) * (t - 2 * CalculoTb(x)), N / (N - 1)) * (1 - exp(-x * lambdaAdesao)) / (lambdaAdesao * velocidade);
		else {
			double c1 = C * pow(pow(sigma_a0 - sigma_am, 1 - N) - C * (1 - N) * (t - 2 * CalculoTb(x)), N / (N - 1));
			double esquerda = c1 / (velocidade * (lambdaAdesao + lambdaPonte));
			double direita = 1-(1 - (velocidade*(lambdaAdesao+lambdaPonte))/c1)*exp(-x*(lambdaAdesao+lambdaPonte))/ pow(1-lambdaAdesao*velocidade*cb/c1,1+lambdaPonte/lambdaAdesao);
			concentracao = esquerda * direita;
		}
	}
	return concentracao;
}

void CSimuladorParticulas::printCSimuladorParticulas() {
	printCParticulaFluido();
	printCRocha();
	std::cout << "\n--------------------" << std::endl;
	std::cout << "Classe da simulacao: " << std::endl;
	std::cout << "--------------------" << std::endl;

	std::cout << "Grid dos tempos:" << std::endl;
	print_vector(tempo);
}

void CSimuladorParticulas::saveInFile(std::vector<double> vector1, std::string name_vector1) {
	std::ofstream outdata; //save data
	outdata.open((name_vector1 + ".dat").c_str());
	outdata << "# "<< name_vector1 << std::endl;
	for (unsigned int i = 0; i < vector1.size(); i++)
		outdata << vector1[i] << std::endl;
	outdata.close();
}

void CSimuladorParticulas::saveInFile(std::vector<double> vector1, std::vector<double> vector2, std::string name_vector1, std::string name_vector2){
	if (vector1.size() != vector2.size()) {
		std::cout << "Nao foi possivel salvar os vetores, por terem tamanhos distintos!"<<std::endl;
		return;
	}

	std::ofstream outdata; //save data
	outdata.open((name_vector1+"_"+ name_vector2 + ".dat").c_str());
	outdata << "# " << name_vector1 << " " << name_vector2 << std::endl;
	for (unsigned int i = 0; i < vector1.size(); i++)
		outdata << vector1[i] << " " << vector2[i] << std::endl;
	outdata.close();
}

void CSimuladorParticulas::print_vector(std::vector<double> vetor) {
	std::cout << vetor[0]; /// este primeiro nao fica dentro do loop por causa do ' - '
	for (unsigned int i = 1; i < vetor.size(); i++)
		std::cout << " - " << vetor[i];
	std::cout << std::endl;
}


