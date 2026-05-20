#include "Colaborador.hpp"

Colaborador::Colaborador() : mediador(nullptr) {}

void Colaborador::setMediador(Mediador* m) { mediador = m; }