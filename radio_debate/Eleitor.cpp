#include "Eleitor.hpp"
#include <iostream>

Eleitor::Eleitor(const std::string& nome, Candidato* candidato)
    : nome(nome), candidatoPreferido(candidato)
{
    candidatoPreferido->cadastrar(this);
}

void Eleitor::atualizar() {
    std::cout << "  [OBSERVER] Eleitor " << nome
              << " notificado: Candidato "
              << candidatoPreferido->getNome()
              << " esta falando!" << std::endl;
}

std::string Eleitor::getNomeEleitor() const { return nome; }