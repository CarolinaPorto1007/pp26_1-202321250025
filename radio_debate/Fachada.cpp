#include "Fachada.hpp"
#include <iostream>
#include <iomanip>

Fachada* Fachada::instance = nullptr;

Fachada::Fachada() { gerenciador = new GerenciadorDebate(); }
Fachada::~Fachada() { delete gerenciador; }

Fachada* Fachada::getInstance() {
    if (!instance) instance = new Fachada();
    return instance;
}

void Fachada::configurarDebate(const std::vector<Candidato*>& candidatos, int tempos[]) {
    if (candidatos.empty() || !tempos) {
        std::cout << "[ERRO] Dados invalidos." << std::endl;
        return;
    }
    gerenciador->candidatos = candidatos;
    gerenciador->tempos     = tempos;
}

void Fachada::definirInquirido(int idCandidato) {
    gerenciador->definirInquirido(idCandidato);
}

void Fachada::iniciarDebate() {
    if (gerenciador->candidatos.empty()) {
        std::cout << "[ERRO] Debate nao configurado." << std::endl;
        return;
    }
    gerenciador->registrarAcao("SISTEMA", "Debate iniciado");

    // Roda enquanto houver candidatos disponíveis
    while (gerenciador->temCandidatosDisponiveis()) {
        gerenciador->sortearInquiridor();

        // Pede ao usuário para escolher o inquirido via CLI
        std::cout << "\n  Candidatos disponíveis para inquirido:" << std::endl;
        for (auto c : gerenciador->candidatos)
            std::cout << "    [" << c->getId() << "] "
                      << c->getNome() << " - " << c->getPartido() << std::endl;

        int escolha = -1;
        bool valido = false;
        while (!valido) {
            std::cout << "\n  Digite o ID do inquirido: ";
            std::cin >> escolha;
            for (auto c : gerenciador->candidatos) {
                if (c->getId() == escolha && c != gerenciador->inquiridor) {
                    valido = true;
                    break;
                }
            }
            if (!valido)
                std::cout << "  ID invalido ou e o proprio inquiridor. Tente novamente." << std::endl;
        }

        gerenciador->definirInquirido(escolha);
        gerenciador->iniciarFase(gerenciador->tempos[0]);
    }
}

void Fachada::finalizarDebate() {
    gerenciador->registrarAcao("SISTEMA", "Debate encerrado");
    gerenciador->logger->gerarRelatorio();
}