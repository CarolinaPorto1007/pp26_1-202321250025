#include "EstadoDireitoResposta.hpp"
#include "EstadoNormal.hpp"
#include "GerenciadorDebate.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void EstadoDireitoResposta::executar(GerenciadorDebate* ctx) {
    ctx->drPermitido = false;   // bloqueia novos DRs durante as defesas

    std::cout << "\n  +------------------------------------------+" << std::endl;
    std::cout << "  |        DIREITO DE RESPOSTA               |" << std::endl;
    std::cout << "  +------------------------------------------+" << std::endl;

    while (!ctx->filaDR.empty()) {
        Candidato* solicitante = ctx->filaDR.front();
        ctx->filaDR.pop();

        // muta todos
        for (auto c : ctx->candidatos)
            c->microfone->desligar();

        std::cout << "\n  [DR] Microfone aberto para: "
                  << solicitante->getNome()
                  << " (" << solicitante->getPartido() << ")" << std::endl;

        solicitante->microfone->ligar();
        solicitante->notificar();   // Observer — notifica eleitores sobre DR

        ctx->registrarAcao("DR",
            "Defesa: " + solicitante->getNome() +
            " (" + solicitante->getPartido() + ")");

        std::cout << "  [CRONOMETRO] Simulando 60s de defesa..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "  [CRONOMETRO] Tempo encerrado!" << std::endl;

        solicitante->microfone->desligar();
    }

    ctx->registrarAcao("DR", "Direito de Resposta encerrado. Retomando debate.");
    std::cout << "\n  [DR] Defesas encerradas. Retomando debate normal." << std::endl;

    ctx->drPermitido = true;
    ctx->mudarEstado(new EstadoNormal());
}

void EstadoDireitoResposta::solicitarDR(GerenciadorDebate* ctx, int idCandidato) {
    std::cout << "  [DR] Solicitacao bloqueada durante Direito de Resposta." << std::endl;
}
