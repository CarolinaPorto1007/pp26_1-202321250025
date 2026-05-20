#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include "Fachada.hpp"
#include "Candidatoconcreto.hpp"
#include "Eleitor.hpp"

void limparTela() { system("clear"); }

void cabecalho() {
    std::cout << "\n+==================================================+" << std::endl;
    std::cout << "|         SISTEMA DE DEBATE POLITICO                |" << std::endl;
    std::cout << "+==================================================+" << std::endl;
}

int lerInteiro(const std::string& msg, int min, int max) {
    int val;
    while (true) {
        std::cout << msg;
        if (std::cin >> val && val >= min && val <= max) return val;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Valor invalido. Digite entre " << min << " e " << max << ".\n";
    }
}

int main() {
    limparTela();
    cabecalho();

    // --- Candidatos ---
    int n = lerInteiro("\n  Quantos candidatos participarao do debate? ", 2, 10);
    std::cin.ignore();

    std::vector<Candidato*> candidatos;
    for (int i = 1; i <= n; i++) {
        std::string nome, partido;
        std::cout << "\n  Candidato " << i << ":" << std::endl;
        std::cout << "    Nome   : "; std::getline(std::cin, nome);
        std::cout << "    Partido: "; std::getline(std::cin, partido);
        candidatos.push_back(new CandidatoConcreto(i, nome, partido));
    }

    // --- Eleitores ---
    int ne = lerInteiro("\n  Quantos eleitores deseja cadastrar? ", 0, 20);
    std::cin.ignore();

    std::vector<Eleitor*> eleitores;
    for (int i = 0; i < ne; i++) {
        std::string nome;
        std::cout << "\n  Eleitor " << (i+1) << ":" << std::endl;
        std::cout << "    Nome: "; std::getline(std::cin, nome);
        std::cout << "    Candidatos disponiveis:" << std::endl;
        for (auto c : candidatos)
            std::cout << "      [" << c->getId() << "] "
                      << c->getNome() << " - " << c->getPartido() << std::endl;
        int id = lerInteiro("    ID do candidato preferido: ", 1, (int)candidatos.size());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Candidato* pref = nullptr;
        for (auto c : candidatos)
            if (c->getId() == id) { pref = c; break; }
        eleitores.push_back(new Eleitor(nome, pref));
    }

    // --- Tempos ---
    std::cout << "\n  Configure os tempos de cada fase (segundos):" << std::endl;
    int tempos[4];
    tempos[0] = lerInteiro("    PERGUNTA : ", 1, 300);
    tempos[1] = lerInteiro("    RESPOSTA : ", 1, 300);
    tempos[2] = lerInteiro("    REPLICA  : ", 1, 300);
    tempos[3] = lerInteiro("    TREPLICA : ", 1, 300);

    // --- Resumo ---
    limparTela();
    cabecalho();
    std::cout << "\n  +-----------------------------------+" << std::endl;
    std::cout << "  |     RESUMO DA CONFIGURACAO        |" << std::endl;
    std::cout << "  +-----------------------------------+" << std::endl;
    for (auto c : candidatos)
        std::cout << "  |  [" << c->getId() << "] "
                  << c->getNome() << " - " << c->getPartido() << std::endl;
    std::cout << "  |  Tempos: P=" << tempos[0] << "s R=" << tempos[1]
              << "s Re=" << tempos[2] << "s Tr=" << tempos[3] << "s" << std::endl;
    std::cout << "  +-----------------------------------+" << std::endl;

    std::cout << "\n  Pressione ENTER para iniciar o debate...";
    std::cin.ignore(); std::cin.get();

    limparTela();
    cabecalho();

    // --- Inicia via Fachada ---
    Fachada* fachada = Fachada::getInstance();
    fachada->configurarDebate(candidatos, tempos);
    fachada->iniciarDebate();
    fachada->finalizarDebate();

    std::cout << "\n  Pressione ENTER para sair...";
    std::cin.get();

    for (auto e : eleitores) delete e;
    for (auto c : candidatos) delete c;
    return 0;
}