#include "Microfone.hpp"
#include <iostream>

Microfone::Microfone(int id) : id(id), ligado(false) {}

void Microfone::ligar() {
    ligado = true;
    std::cout << "  [MIC " << id << "] LIGADO" << std::endl;
}

void Microfone::desligar() {
    ligado = false;
    std::cout << "  [MIC " << id << "] DESLIGADO" << std::endl;
}

bool Microfone::getLigado() const { return ligado; }