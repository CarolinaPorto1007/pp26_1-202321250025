#include "Cronometro.hpp"
#include <iostream>

Cronometro::Cronometro() : tempoAtual(0) {}

void Cronometro::iniciar(int tempo) {
    tempoAtual = tempo;
    std::cout << "  [CRONOMETRO] Contando " << tempo << "s..." << std::endl;
    while (tempoAtual > 0) tempoAtual--;
    finalizarTempo();
}

void Cronometro::finalizarTempo() {
    std::cout << "  [CRONOMETRO] Tempo esgotado! Avancando fase..." << std::endl;
    if (mediador) mediador->proximaAcao();
}