#ifndef ESTADODIREITORESPOSTA_HPP
#define ESTADODIREITORESPOSTA_HPP

#include <string>
#include "EstadoDebate.hpp"

class EstadoDireitoResposta : public EstadoDebate {
public:
    void executar(GerenciadorDebate* ctx) override;
    void solicitarDR(GerenciadorDebate* ctx, int idCandidato) override;
    std::string getNome() const override { return "DIREITO_RESPOSTA"; }
};

#endif
