#include "Cronometro.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Cronometro::Cronometro() : tempoAtual(0) {}

void Cronometro::iniciar(int tempo)
{
    tempoAtual = tempo;
    std::cout << "  [CRONOMETRO] Simulando " << tempo << "s..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "  [CRONOMETRO] Tempo encerrado!" << std::endl;
    finalizarTempo();
}

void Cronometro::finalizarTempo()
{
    if (mediador)
        mediador->proximaAcao();
}