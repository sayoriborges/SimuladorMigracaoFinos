#include<iostream>
#include<string>
#include<math.h>

#include "metodosimpson.cpp"
#include "CSimuladorParticulas.cpp"
#include  "CGrid.cpp"
#include "CRocha.cpp"
#include "CParticulaFluido.cpp"
using namespace std;

class FuncaoSeno2D : public Funcao2x1 {
	virtual double operator()(double x, double y) { return sin(x * y); }
};

int main() {
	
	//double a, b;
	//size_t numPontos;

	//cout << "a? ";
	//cin >> a;
	//cout << "b? ";
	//cin >> b;
	//cout << "numPontos? ";
	//cin >> numPontos;

	//Funcao2x1* objSeno2Dptr = new FuncaoSeno2D;
	//Funcao1x1* x_par_ptr    = new Funcao1x1_Reta(1, 0);
	//Funcao1x1* y_par_ptr    = new Funcao1x1_Reta(0, 1);

	//// Criacao curva parametrica e passagem diretamente para objeto funcao sobre curva parametrizada
	//FuncaoParametrizadaCurva objIntegracao(*objSeno2Dptr, *x_par_ptr, *y_par_ptr);
	//MetodoIntegracaoNumerica1D* metodo = new MetodoSimpson(objIntegracao);

	//cout << "A integral de sin(x) definida de " << a << " ateh " << b << " eh "
	//	<< metodo->Integrar(a, b, numPontos) << " ." << endl;

	/////////////////////////////////////////////////////////
	CSimuladorParticulas simulacao("particulaFluido.txt", "rocha.txt");
	simulacao.printCSimuladorParticulas();
	simulacao.run();
	/////////////////////////////////////////////////////////
	/*delete x_par_ptr;
	delete y_par_ptr;
	delete objSeno2Dptr;
	delete metodo;*/
}
