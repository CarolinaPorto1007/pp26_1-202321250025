#ifndef CRONOMETRO_HPP
#define CRONOMETRO_HPP

#include "Colaborador.hpp"

class Cronometro : public Colaborador {
private:
    int tempoAtual;

public:
    Cronometro();
    void iniciar(int tempo);
    void finalizarTempo();
};

#endif
