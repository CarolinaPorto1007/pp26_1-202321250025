#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include "Fachada.hpp"
#include "Candidatobuilder.hpp"
#include "Eleitorbuilder.hpp"
#include "Operadorbuilder.hpp"

void limparTela() { system("clear"); }

void cabecalho()
{
    std::cout << "\n+==================================================+" << std::endl;
    std::cout << "|      SISTEMA DE DEBATE POLITICO — GDP v3.0        |" << std::endl;
    std::cout << "+==================================================+" << std::endl;
}

int lerInteiro(const std::string &msg, int min, int max)
{
    int val;
    while (true)
    {
        std::cout << msg;
        if (std::cin >> val && val >= min && val <= max)
            return val;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Valor invalido. Digite entre " << min << " e " << max << ".\n";
    }
}

int main()
{
    limparTela();
    cabecalho();

    // --- Operador (Builder) ---
    // --- Operador (Builder) ---
    std::string nomeOp;
    std::cout << "\n  Identificacao do Operador:" << std::endl;
    std::cout << "    Nome: ";
    std::getline(std::cin, nomeOp);

    Operador *operador = nullptr;
    try
    {
        operador = OperadorBuilder()
                       .setId(1)
                       .setNome(nomeOp)
                       .setPerfil("apresentador")
                       .build();
        std::cout << "  Operador registrado: " << operador->getNome()
                  << " [" << operador->getPerfil() << "]" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "  [ERRO] " << e.what() << std::endl;
        return 1;
    }

    // --- Candidatos (Builder + Prototype) ---
    int n = lerInteiro("\n  Quantos candidatos participarao do debate? ", 2, 10);
    std::cin.ignore();

    std::vector<Candidato *> candidatos;
    for (int i = 1; i <= n; i++)
    {
        std::string nome, partido;
        std::cout << "\n  Candidato " << i << ":" << std::endl;
        std::cout << "    Nome   : ";
        std::getline(std::cin, nome);
        std::cout << "    Partido: ";
        std::getline(std::cin, partido);

        try
        {
            CandidatoConcreto *c = CandidatoBuilder()
                                       .setId(i)
                                       .setNome(nome)
                                       .setPartido(partido)
                                       .build();
            candidatos.push_back(c);
        }
        catch (const std::exception &e)
        {
            std::cout << "  [ERRO] " << e.what() << std::endl;
            i--;
        }
    }

    // --- Demonstracao do Prototype: clona o primeiro candidato ---
    std::cout << "\n  [PROTOTYPE] Clonando candidato 1 como exemplo..." << std::endl;
    CandidatoConcreto *original = dynamic_cast<CandidatoConcreto *>(candidatos[0]);
    if (original)
    {
        CandidatoConcreto *clone = original->clonar();
        std::cout << "  Clone criado: " << clone->getNome()
                  << " (" << clone->getPartido() << ")" << std::endl;
        delete clone;
    }

    // --- Eleitores (Builder + Prototype) ---
    int ne = lerInteiro("\n  Quantos eleitores deseja cadastrar? ", 0, 20);
    std::cin.ignore();

    std::vector<Eleitor *> eleitores;
    for (int i = 0; i < ne; i++)
    {
        std::string nome;
        std::cout << "\n  Eleitor " << (i + 1) << ":" << std::endl;
        std::cout << "    Nome: ";
        std::getline(std::cin, nome);
        std::cout << "    Candidatos disponiveis:" << std::endl;
        for (auto c : candidatos)
            std::cout << "      [" << c->getId() << "] "
                      << c->getNome() << " - " << c->getPartido() << std::endl;
        int id = lerInteiro("    ID do candidato preferido: ", 1, (int)candidatos.size());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Candidato *pref = nullptr;
        for (auto c : candidatos)
            if (c->getId() == id)
            {
                pref = c;
                break;
            }

        try
        {
            Eleitor *e = EleitorBuilder()
                             .setId(i + 1)
                             .setNome(nome)
                             .setCandidatoPreferido(pref)
                             .build();
            eleitores.push_back(e);
        }
        catch (const std::exception &ex)
        {
            std::cout << "  [ERRO] " << ex.what() << std::endl;
            i--;
        }
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
#include <iomanip>

    // ...

    std::cout << "  +--------------------------------------+" << std::endl;
    std::cout << "  |       RESUMO DA CONFIGURACAO         |" << std::endl;
    std::cout << "  +--------------------------------------+" << std::endl;

    std::cout << "  | " << std::left << std::setw(36)
              << ("Operador: " + operador->getNome() + " [" + operador->getPerfil() + "]")
              << "|" << std::endl;

    std::cout << "  | " << std::left << std::setw(36)
              << "Candidatos:"
              << "|" << std::endl;

    for (auto c : candidatos)
    {
        std::string linha = "[" + std::to_string(c->getId()) + "] " + c->getNome() + " - " + c->getPartido();

        std::cout << "  | " << std::left << std::setw(36)
                  << linha
                  << "|" << std::endl;
    }

    std::cout << "  | " << std::left << std::setw(36)
              << ("Eleitores: " + std::to_string(eleitores.size()) + " cadastrado(s)")
              << "|" << std::endl;

    std::string temposStr = "Tempos: P=" + std::to_string(tempos[0]) +
                            "s R=" + std::to_string(tempos[1]) +
                            "s Re=" + std::to_string(tempos[2]) +
                            "s Tr=" + std::to_string(tempos[3]) + "s";

    std::cout << "  | " << std::left << std::setw(36)
              << temposStr
              << "|" << std::endl;

    std::cout << "  +--------------------------------------+" << std::endl;
    std::cout << "\n  Pressione ENTER para iniciar o debate...";
    std::cin.ignore();
    std::cin.get();

    limparTela();
    cabecalho();

    // --- Inicia via Fachada ---
    Fachada *fachada = Fachada::getInstance();
    fachada->configurarDebate(candidatos, tempos);
    fachada->iniciarDebate();
    fachada->finalizarDebate();

    std::cout << "\n  Pressione ENTER para sair...";
    std::cin.get();

    delete operador;
    for (auto e : eleitores)
        delete e;
    for (auto c : candidatos)
        delete c;
    return 0;
}