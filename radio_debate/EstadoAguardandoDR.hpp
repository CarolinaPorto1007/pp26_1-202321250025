#ifndef ESTADOAGUARDANDODR_HPP
#define ESTADOAGUARDANDODR_HPP

#include <string>
#include "EstadoDebate.hpp"

class EstadoAguardandoDR : public EstadoDebate {
public:
    void executar(GerenciadorDebate* ctx) override;
    void solicitarDR(GerenciadorDebate* ctx, int idCandidato) override;
    std::string getNome() const override { return "AGUARDANDO_DR"; }
};

#endif
