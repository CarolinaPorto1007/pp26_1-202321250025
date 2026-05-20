#ifndef COLABORADOR_HPP
#define COLABORADOR_HPP

#include "Mediador.hpp"

class Colaborador {
protected:
    Mediador* mediador;

public:
    Colaborador();
    void setMediador(Mediador* m);
};

#endif