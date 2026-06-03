#ifndef CANDIDATOCONCRETO_HPP
#define CANDIDATOCONCRETO_HPP

#include <string>
#include "Candidato.hpp"
#include "Prototype.hpp"

class CandidatoConcreto : public Candidato, public Prototype<CandidatoConcreto> {
private:
    std::string partido;

public:
    CandidatoConcreto(int id, const std::string& nome, const std::string& partido);

    std::string         getPartido() const override;
    CandidatoConcreto*  clonar()     const override;
};

#endif