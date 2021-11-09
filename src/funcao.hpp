#ifndef FUNCAO_HPP_
#define FUNCAO_HPP_

class Funcao1x1 {
public:
    virtual double operator()(double) = 0; // Funcao virtual pura 
};

class Funcao1x1_Reta : public Funcao1x1 {
public:
    Funcao1x1_Reta(double a, double b) 
        : coeficienteAngular{ a }, coeficienteLinear{ b } {}

    virtual double operator()(double x) { return coeficienteLinear + coeficienteAngular * x; }
    double coeficienteAngular, coeficienteLinear;
};

class Funcao2x1 {
public:
    virtual double operator()(double x, double y) = 0;
};

class FuncaoParametrizadaCurva : public Funcao1x1 {
public:
    // construtor
    FuncaoParametrizadaCurva(Funcao2x1& f_xy_in, Funcao1x1& X_par, Funcao1x1& Y_par)
        : f_xy(f_xy_in), curvaX_par(X_par), curvaY_par(Y_par) {}

    virtual double operator()(double par) { return f_xy(curvaX_par(par), curvaY_par(par)); }
    
private:
    Funcao2x1& f_xy;
    Funcao1x1& curvaX_par;
    Funcao1x1& curvaY_par;
};

#endif