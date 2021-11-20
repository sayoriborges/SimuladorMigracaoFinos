#ifndef METODOSIMPSON_HPP_
#define METODOSIMPSON_HPP_

#include "metodointegracaonumerica.hpp"
#include<iostream>

class MetodoSimpson : public MetodoIntegracaoNumerica1D {
public:
    // construtor
    MetodoSimpson(Funcao1x1& f_x_in) : MetodoIntegracaoNumerica1D(f_x_in) {}

    // a fun��o abaixo resolve a integral pelo m�todo de simpson... a fun��o � usada aqui dentro
    virtual double Integrar(double a, double b, size_t numPontos);
};
#endif
