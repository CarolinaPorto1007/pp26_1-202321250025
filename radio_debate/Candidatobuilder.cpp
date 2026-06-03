#include "Candidatobuilder.hpp"
#include <stdexcept>

CandidatoBuilder::CandidatoBuilder() : id(0) {}

CandidatoBuilder& CandidatoBuilder::setId(int i)                  { id = i;         return *this; }
CandidatoBuilder& CandidatoBuilder::setNome(const std::string& n)  { nome = n;       return *this; }
CandidatoBuilder& CandidatoBuilder::setPartido(const std::string& p){ partido = p;    return *this; }

CandidatoConcreto* CandidatoBuilder::build() {
    if (id <= 0)       throw std::invalid_argument("ID do candidato invalido.");
    if (nome.empty())  throw std::invalid_argument("Nome do candidato vazio.");
    if (partido.empty()) throw std::invalid_argument("Partido do candidato vazio.");
    return new CandidatoConcreto(id, nome, partido);
}