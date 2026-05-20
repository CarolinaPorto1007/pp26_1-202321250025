#ifndef CANDIDATOCONCRETO_HPP
#define CANDIDATOCONCRETO_HPP

#include <string>
#include "Candidato.hpp"

class CandidatoConcreto : public Candidato {
private:
    std::string partido;

public:
    CandidatoConcreto(int id, const std::string& nome, const std::string& partido);
    std::string getPartido() const override;
};

#endif