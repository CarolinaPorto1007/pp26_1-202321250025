#ifndef ESTADONORMAL_HPP
#define ESTADONORMAL_HPP

#include <string>
#include "EstadoDebate.hpp"

class EstadoNormal : public EstadoDebate {
public:
    void executar(GerenciadorDebate* ctx) override;
    void solicitarDR(GerenciadorDebate* ctx, int idCandidato) override;
    std::string getNome() const override { return "NORMAL"; }
};

#endif
