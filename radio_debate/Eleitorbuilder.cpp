#include "Eleitorbuilder.hpp"
#include <stdexcept>

EleitorBuilder::EleitorBuilder() : id(0), candidatoPreferido(nullptr) {}

EleitorBuilder& EleitorBuilder::setId(int i)                       { id = i;                   return *this; }
EleitorBuilder& EleitorBuilder::setNome(const std::string& n)       { nome = n;                 return *this; }
EleitorBuilder& EleitorBuilder::setCandidatoPreferido(Candidato* c) { candidatoPreferido = c;   return *this; }

Eleitor* EleitorBuilder::build() {
    if (id <= 0)                    throw std::invalid_argument("ID do eleitor invalido.");
    if (nome.empty())               throw std::invalid_argument("Nome do eleitor vazio.");
    if (!candidatoPreferido)        throw std::invalid_argument("Candidato preferido nao definido.");
    return new Eleitor(id, nome, candidatoPreferido);
}