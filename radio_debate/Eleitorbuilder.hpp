#ifndef ELEITORBUILDER_HPP
#define ELEITORBUILDER_HPP

#include <string>
#include "Eleitor.hpp"
#include "Candidato.hpp"

class EleitorBuilder {
private:
    int         id;
    std::string nome;
    Candidato*  candidatoPreferido;

public:
    EleitorBuilder();
    EleitorBuilder& setId(int id);
    EleitorBuilder& setNome(const std::string& nome);
    EleitorBuilder& setCandidatoPreferido(Candidato* c);
    Eleitor* build();
};

#endif