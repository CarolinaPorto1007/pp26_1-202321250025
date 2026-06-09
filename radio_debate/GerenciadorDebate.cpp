#include "GerenciadorDebate.hpp"
#include "EstadoNormal.hpp"
#include "EstadoAguardandoDR.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

GerenciadorDebate::GerenciadorDebate()
    : inquiridor(nullptr), inquirido(nullptr),
      tempos(nullptr), faseAtual(""),
      rodadaAtual(0), totalRodadas(0),
      drPermitido(true)
{
    cronometro  = new Cronometro();
    logger      = new Logger("debate_log.txt");
    estadoAtual = new EstadoNormal();
    cronometro->setMediador(this);
    std::srand((unsigned)std::time(nullptr));
}

GerenciadorDebate::~GerenciadorDebate() {
    delete cronometro;
    delete logger;
    delete estadoAtual;
}

void GerenciadorDebate::mudarEstado(EstadoDebate* novoEstado) {
    delete estadoAtual;
    estadoAtual = novoEstado;
    std::cout << "  [STATE] Estado: " << estadoAtual->getNome() << std::endl;
}

bool GerenciadorDebate::temCandidatosDisponiveis() {
    for (auto c : candidatos)
        if (!c->getJaPerguntou()) return true;
    return false;
}

int  GerenciadorDebate::getRodadaAtual()     const { return rodadaAtual; }
int  GerenciadorDebate::getTotalCandidatos() const { return (int)candidatos.size(); }
std::string GerenciadorDebate::getFaseAtual() const { return faseAtual; }
void GerenciadorDebate::setFaseAtual(const std::string& f) { faseAtual = f; }

void GerenciadorDebate::solicitarDR(int idCandidato) {
    estadoAtual->solicitarDR(this, idCandidato);
}

void GerenciadorDebate::executarDireitos() {
    mudarEstado(new EstadoAguardandoDR());
    estadoAtual->executar(this);
}

void GerenciadorDebate::sortearInquiridor() {
    faseAtual = "PERGUNTA";

    std::vector<Candidato*> disponiveis;
    for (auto c : candidatos)
        if (!c->getJaPerguntou())
            disponiveis.push_back(c);

    if (disponiveis.empty()) {
        std::cout << "\n  Todos os candidatos ja foram inquiridores." << std::endl;
        return;
    }

    rodadaAtual++;
    totalRodadas = (int)candidatos.size();

    int idx    = std::rand() % (int)disponiveis.size();
    inquiridor = disponiveis[idx];
    inquiridor->marcarComoInquiridor();

    std::cout << "\n  > Rodada " << rodadaAtual << "/" << totalRodadas << std::endl;
    std::cout << "  > Inquiridor sorteado: "
              << inquiridor->getNome()
              << " (" << inquiridor->getPartido() << ")" << std::endl;

    registrarAcao("SORTEIO",
        "Rodada " + std::to_string(rodadaAtual) + "/" + std::to_string(totalRodadas) +
        " — Inquiridor: " + inquiridor->getNome());
}

void GerenciadorDebate::definirInquirido(int id) {
    for (auto c : candidatos) {
        if (c->getId() == id && c != inquiridor) {
            inquirido = c;
            std::cout << "  > Inquirido : "
                      << inquirido->getNome()
                      << " (" << inquirido->getPartido() << ")" << std::endl;
            registrarAcao("CONFIGURACAO", "Inquirido: " + c->getNome());
            return;
        }
    }
    std::cout << "  [ERRO] Candidato invalido." << std::endl;
}

void GerenciadorDebate::iniciarFase(int tempo) {
    std::cout << "\n  +------------------------------------------+" << std::endl;
    std::cout << "  | FASE: " << std::left << std::setw(12) << faseAtual
              << " | Duracao: " << std::setw(4) << tempo << "s         |" << std::endl;

    std::string quemFala = (faseAtual == "PERGUNTA" || faseAtual == "REPLICA")
                           ? inquiridor->getNome() : inquirido->getNome();
    std::string quemAguarda = (faseAtual == "PERGUNTA" || faseAtual == "REPLICA")
                              ? inquirido->getNome() : inquiridor->getNome();

    std::cout << "  | Com a palavra : " << std::left << std::setw(25) << quemFala    << "|" << std::endl;
    std::cout << "  | Aguardando    : " << std::left << std::setw(25) << quemAguarda << "|" << std::endl;
    std::cout << "  +------------------------------------------+" << std::endl;

    if (faseAtual == "PERGUNTA") {
        inquiridor->microfone->ligar();
        inquiridor->notificar();
        inquirido->microfone->desligar();
    } else if (faseAtual == "RESPOSTA") {
        inquiridor->microfone->desligar();
        inquirido->microfone->ligar();
        inquirido->notificar();
    } else if (faseAtual == "REPLICA") {
        inquiridor->microfone->ligar();
        inquiridor->notificar();
        inquirido->microfone->desligar();
    } else if (faseAtual == "TREPLICA") {
        inquiridor->microfone->desligar();
        inquirido->microfone->ligar();
        inquirido->notificar();
    }

    // Pergunta durante a fase se alguem quer acionar DR
    if (drPermitido && faseAtual == "PERGUNTA") {
        std::cout << "\n  Algum candidato deseja acionar o DR durante essa rodada?" << std::endl;
        std::cout << "  (Digite o ID do candidato ou 0 para nenhum): ";
        int drId; std::cin >> drId;
        if (drId != 0) solicitarDR(drId);
    }

    registrarAcao("FASE", faseAtual + " (" + std::to_string(tempo) + "s) | Fala: " + quemFala);
    cronometro->iniciar(tempo);
}

void GerenciadorDebate::registrarAcao(const std::string& categoria, const std::string& acao) {
    logger->registrar(categoria, acao);
}

void GerenciadorDebate::proximaAcao() {
    if (faseAtual == "PERGUNTA") {
        faseAtual = "RESPOSTA";
        iniciarFase(tempos[1]);
    } else if (faseAtual == "RESPOSTA") {
        faseAtual = "REPLICA";
        iniciarFase(tempos[2]);
    } else if (faseAtual == "REPLICA") {
        faseAtual = "TREPLICA";
        iniciarFase(tempos[3]);
    } else if (faseAtual == "TREPLICA") {
        registrarAcao("RODADA", "Rodada " + std::to_string(rodadaAtual) + " finalizada");
        std::cout << "\n  > Rodada " << rodadaAtual << " encerrada." << std::endl;

        // Verifica DR ao fim da treplica
        if (!filaDR.empty()) {
            executarDireitos();
        }

        if (temCandidatosDisponiveis()) {
            std::cout << "  Preparando proxima rodada..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}
