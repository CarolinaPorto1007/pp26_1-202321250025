#include "EstadoNormal.hpp"
#include "EstadoAguardandoDR.hpp"
#include "GerenciadorDebate.hpp"
#include <iostream>

void EstadoNormal::executar(GerenciadorDebate* ctx) {
    // comportamento normal — controlado pelo GerenciadorDebate
}

void EstadoNormal::solicitarDR(GerenciadorDebate* ctx, int idCandidato) {
    if (!ctx->drPermitido) {
        std::cout << "  [DR] Solicitacao de DR nao permitida agora." << std::endl;
        return;
    }
    for (auto c : ctx->candidatos) {
        if (c->getId() == idCandidato) {
            ctx->filaDR.push(c);
            ctx->registrarAcao("DR", "Solicitacao de DR: " + c->getNome());
            std::cout << "  [DR] " << c->getNome()
                      << " solicitou Direito de Resposta." << std::endl;
            return;
        }
    }
    std::cout << "  [DR] Candidato nao encontrado." << std::endl;
}
