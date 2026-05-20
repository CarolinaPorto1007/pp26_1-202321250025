#include "Candidatoconcreto.hpp"

CandidatoConcreto::CandidatoConcreto(int id, const std::string& nome, const std::string& partido)
    : Candidato(id, nome), partido(partido) {}

std::string CandidatoConcreto::getPartido() const { return partido; }