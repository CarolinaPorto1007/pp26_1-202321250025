#ifndef ELEITOR_HPP
#define ELEITOR_HPP

#include <string>
#include <iomanip>
#include "Observador.hpp"
#include "Candidato.hpp"

class Eleitor : public Observador {
private:
    int         id;
    std::string nome;
    Candidato*  candidatoPreferido;

public:
    Eleitor(const std::string& nome, Candidato* candidato);
    void        atualizar() override;
    std::string getNomeEleitor() const;
};

#endif