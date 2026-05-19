#include "Fachada.hpp"
#include <iostream>

Fachada* Fachada::instance = nullptr;

Fachada::Fachada() {
    gerenciador = new GerenciadorDebate();
}

Fachada::~Fachada() { delete gerenciador; }

Fachada* Fachada::getInstance() {
    if (!instance)
        instance = new Fachada();
    return instance;
}

void Fachada::configurarDebate(const std::vector<Candidato*>& candidatos, int tempos[]) {
    if (candidatos.empty() || !tempos) {
        std::cout << "[ERRO] Dados invalidos." << std::endl;
        return;
    }
    gerenciador->candidatos = candidatos;
    gerenciador->tempos     = tempos;

    std::cout << "\n==================================================" << std::endl;
    std::cout << "         DEBATE POLITICO — CONFIGURACAO           " << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "  Candidatos registrados:" << std::endl;
    for (auto c : candidatos)
        std::cout << "    [" << c->getId() << "] " << c->getNome()
                  << " - " << c->getPartido() << std::endl;
    std::cout << "\n  Tempos por fase:" << std::endl;
    std::cout << "    PERGUNTA : " << tempos[0] << "s" << std::endl;
    std::cout << "    RESPOSTA : " << tempos[1] << "s" << std::endl;
    std::cout << "    REPLICA  : " << tempos[2] << "s" << std::endl;
    std::cout << "    TREPLICA : " << tempos[3] << "s" << std::endl;
    std::cout << "==================================================" << std::endl;
}

void Fachada::sortearInquiridor() {
    gerenciador->sortearInquiridor();
}

void Fachada::definirInquirido(int idCandidato) {
    gerenciador->definirInquirido(idCandidato);
}

void Fachada::iniciarDebate() {
    if (gerenciador->candidatos.empty()) {
        std::cout << "[ERRO] Debate nao configurado." << std::endl;
        return;
    }
    std::cout << "\n  [DEBATE INICIADO]" << std::endl;
    gerenciador->registrarAcao("Debate iniciado");
    gerenciador->sortearInquiridor();
}

void Fachada::iniciarPrimeiraFase() {
    gerenciador->iniciarFase(gerenciador->tempos[0]);
}

void Fachada::avancarEtapa() {
    gerenciador->proximaAcao();
}

void Fachada::finalizarDebate() {
    gerenciador->registrarAcao("Debate finalizado");
    gerenciador->logger->gerarRelatorio();
}