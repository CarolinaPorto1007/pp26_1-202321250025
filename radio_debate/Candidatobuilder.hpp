#ifndef CANDIDATOBUILDER_HPP
#define CANDIDATOBUILDER_HPP

#include <string>
#include "Candidatoconcreto.hpp"

class CandidatoBuilder {
private:
    int         id;
    std::string nome;
    std::string partido;

public:
    CandidatoBuilder();
    CandidatoBuilder& setId(int id);
    CandidatoBuilder& setNome(const std::string& nome);
    CandidatoBuilder& setPartido(const std::string& partido);
    CandidatoConcreto* build();
};

#endif