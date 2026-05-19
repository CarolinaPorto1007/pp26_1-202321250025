#include "GerenciadorDebate.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

GerenciadorDebate::GerenciadorDebate()
    : inquiridor(nullptr), inquirido(nullptr),
      tempos(nullptr), faseAtual("")
{
    cronometro = new Cronometro();
    logger     = new Logger();
    cronometro->setMediador(this);
    std::srand((unsigned)std::time(nullptr));
}

GerenciadorDebate::~GerenciadorDebate() {
    delete cronometro;
    delete logger;
}

void GerenciadorDebate::sortearInquiridor() {
    if (faseAtual.empty())
        faseAtual = "PERGUNTA";

    std::vector<Candidato*> disponiveis;
    for (auto c : candidatos)
        if (!c->getJaPerguntou())
            disponiveis.push_back(c);

    if (disponiveis.empty()) {
        std::cout << "  [AVISO] Todos os candidatos ja foram inquiridores." << std::endl;
        return;
    }

    int idx    = std::rand() % (int)disponiveis.size();
    inquiridor = disponiveis[idx];
    inquiridor->marcarComoInquiridor();
    registrarAcao("Inquiridor sorteado: " + inquiridor->getNome()
                  + " (" + inquiridor->getPartido() + ")");
}

void GerenciadorDebate::definirInquirido(int id) {
    for (auto c : candidatos) {
        if (c->getId() == id && c != inquiridor) {
            inquirido = c;
            registrarAcao("Inquirido definido: " + c->getNome()
                          + " (" + c->getPartido() + ")");
            return;
        }
    }
    std::cout << "  [ERRO] Candidato invalido ou e o proprio inquiridor." << std::endl;
}

void GerenciadorDebate::iniciarFase(int tempo) {
    std::cout << "\n+--------------------------------------------------+" << std::endl;
    std::cout << "  FASE: " << faseAtual
              << "  |  Tempo: " << tempo << "s" << std::endl;
    std::cout << "+--------------------------------------------------+" << std::endl;

    if (faseAtual == "PERGUNTA") {
        std::cout << "  Inquiridor : " << inquiridor->getNome()
                  << " (" << inquiridor->getPartido() << ") [PERGUNTA]" << std::endl;
        std::cout << "  Inquirido  : " << inquirido->getNome()
                  << " (" << inquirido->getPartido() << ") [AGUARDANDO]" << std::endl;
        inquiridor->microfone->ligar();
        inquirido->microfone->desligar();
        inquiridor->notificar();

    } else if (faseAtual == "RESPOSTA") {
        std::cout << "  Inquiridor : " << inquiridor->getNome()
                  << " (" << inquiridor->getPartido() << ") [AGUARDANDO]" << std::endl;
        std::cout << "  Inquirido  : " << inquirido->getNome()
                  << " (" << inquirido->getPartido() << ") [RESPONDE]" << std::endl;
        inquiridor->microfone->desligar();
        inquirido->microfone->ligar();
        inquirido->notificar();

    } else if (faseAtual == "REPLICA") {
        std::cout << "  Inquiridor : " << inquiridor->getNome()
                  << " (" << inquiridor->getPartido() << ") [REPLICA]" << std::endl;
        std::cout << "  Inquirido  : " << inquirido->getNome()
                  << " (" << inquirido->getPartido() << ") [AGUARDANDO]" << std::endl;
        inquiridor->microfone->ligar();
        inquirido->microfone->desligar();
        inquiridor->notificar();

    } else if (faseAtual == "TREPLICA") {
        std::cout << "  Inquiridor : " << inquiridor->getNome()
                  << " (" << inquiridor->getPartido() << ") [AGUARDANDO]" << std::endl;
        std::cout << "  Inquirido  : " << inquirido->getNome()
                  << " (" << inquirido->getPartido() << ") [TREPLICA]" << std::endl;
        inquiridor->microfone->desligar();
        inquirido->microfone->ligar();
        inquirido->notificar();
    }

    registrarAcao("Fase iniciada: " + faseAtual + " (" + std::to_string(tempo) + "s)");
    cronometro->iniciar(tempo);
}

void GerenciadorDebate::registrarAcao(const std::string& acao) {
    logger->registrar(acao);
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
        std::cout << "\n  [FIM] Rodada encerrada!" << std::endl;
        registrarAcao("Rodada finalizada");
    }
}