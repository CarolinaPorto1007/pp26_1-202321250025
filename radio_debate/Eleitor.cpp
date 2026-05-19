#include "Eleitor.hpp"
#include <iostream>

Eleitor::Eleitor(const std::string& nome, Candidato* candidato)
    : nome(nome), candidatoPreferido(candidato)
{
    candidatoPreferido->cadastrar(this);
}

void Eleitor::atualizar() {
    std::cout << "  >> [NOTIFICACAO] Eleitor " << nome
              << " | Seu candidato " << candidatoPreferido->getNome()
              << " (" << candidatoPreferido->getPartido() << ")"
              << " esta com a palavra!" << std::endl;
}