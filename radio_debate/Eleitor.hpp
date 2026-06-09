#ifndef ELEITOR_HPP
#define ELEITOR_HPP

#include <string>
#include <iomanip>
#include "Observador.hpp"
#include "Candidato.hpp"
#include "Prototype.hpp"

class Eleitor : public Observador, public Prototype<Eleitor> {
private:
    int         id;
    std::string nome;
    Candidato*  candidatoPreferido;

public:
    Eleitor(int id, const std::string& nome, Candidato* candidato);
    void        atualizar()      override;
    void        atualizarDR(const std::string& nomeCandidato,
                             const std::string& partido) override;
    Eleitor*    clonar()         const override;
    std::string getNomeEleitor() const;
    int         getId()          const;
};

#endif