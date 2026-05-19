#ifndef ELEITOR_HPP
#define ELEITOR_HPP

#include <string>
#include "Observador.hpp"
#include "Candidato.hpp"

class Eleitor : public Observador {
private:
    std::string nome;
    Candidato*  candidatoPreferido;

public:
    Eleitor(const std::string& nome, Candidato* candidato);
    void atualizar() override;
};

#endif
