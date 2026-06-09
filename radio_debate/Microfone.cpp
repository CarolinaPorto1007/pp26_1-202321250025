#include "Microfone.hpp"
#include <iostream>

Microfone::Microfone(int id) : id(id), ligado(false), drSolicitado(false) {}

void Microfone::ligar() {
    ligado = true;
    std::cout << "  [MIC " << id << "] LIGADO" << std::endl;
}

void Microfone::desligar() {
    ligado = false;
    std::cout << "  [MIC " << id << "] DESLIGADO" << std::endl;
}

void Microfone::acionarDR() {
    drSolicitado = true;
    std::cout << "  [MIC " << id << "] Botao DR acionado!" << std::endl;
}

bool Microfone::getLigado()      const { return ligado; }
bool Microfone::isDrSolicitado() const { return drSolicitado; }
void Microfone::resetarDR()            { drSolicitado = false; }
int  Microfone::getId()          const { return id; }