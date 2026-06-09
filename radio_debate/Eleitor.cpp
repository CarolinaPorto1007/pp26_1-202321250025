#include "Eleitor.hpp"
#include <iostream>

Eleitor::Eleitor(int id, const std::string& nome, Candidato* candidato)
    : id(id), nome(nome), candidatoPreferido(candidato)
{
    candidatoPreferido->cadastrar(this);
}

void Eleitor::atualizar() {
    std::cout << "  [OBSERVER] Eleitor " << nome
              << " notificado: Candidato "
              << candidatoPreferido->getNome()
              << " esta falando!" << std::endl;
}

void Eleitor::atualizarDR(const std::string& nomeCandidato,
                           const std::string& partido) {
    std::cout << "  [OBSERVER - DR] Eleitor " << nome
              << " notificado: Candidato "
              << nomeCandidato << " (" << partido << ")"
              << " esta exercendo seu Direito de Resposta!" << std::endl;
}

Eleitor* Eleitor::clonar() const {
    return new Eleitor(id, nome, candidatoPreferido);
}

std::string Eleitor::getNomeEleitor() const { return nome; }
int         Eleitor::getId()          const { return id; }