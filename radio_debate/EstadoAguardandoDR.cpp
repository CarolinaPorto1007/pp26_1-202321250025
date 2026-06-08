#include "EstadoAguardandoDR.hpp"
#include "EstadoDireitoResposta.hpp"
#include "EstadoNormal.hpp"
#include "GerenciadorDebate.hpp"
#include <iostream>

void EstadoAguardandoDR::executar(GerenciadorDebate* ctx) {
    if (ctx->filaDR.empty()) {
        std::cout << "  [DR] Nenhuma solicitacao de DR pendente." << std::endl;
        ctx->mudarEstado(new EstadoNormal());
        return;
    }

    std::cout << "\n  [DR] Ha " << ctx->filaDR.size()
              << " solicitacao(oes) de Direito de Resposta." << std::endl;
    std::cout << "  [DR] Operador: conceder Direitos de Resposta? (1=Sim / 0=Nao): ";

    int opcao;
    std::cin >> opcao;

    if (opcao == 1) {
        ctx->registrarAcao("DR", "Direito de Resposta concedido pelo operador");
        ctx->mudarEstado(new EstadoDireitoResposta());
        ctx->estadoAtual->executar(ctx);
    } else {
        ctx->registrarAcao("DR", "Direito de Resposta negado pelo operador");
        std::cout << "  [DR] Direito de Resposta negado. Retomando debate." << std::endl;
        while (!ctx->filaDR.empty()) ctx->filaDR.pop();
        ctx->mudarEstado(new EstadoNormal());
    }
}

void EstadoAguardandoDR::solicitarDR(GerenciadorDebate* ctx, int idCandidato) {
    std::cout << "  [DR] Aguardando decisao do operador. Nova solicitacao ignorada." << std::endl;
}
