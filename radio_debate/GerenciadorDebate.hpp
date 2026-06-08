#ifndef GERENCIADORDEBATE_HPP
#define GERENCIADORDEBATE_HPP

#include <vector>
#include <queue>
#include <string>
#include "Mediador.hpp"
#include "Candidato.hpp"
#include "Cronometro.hpp"
#include "Logger.hpp"

class EstadoDebate;

class GerenciadorDebate : public Mediador {
public:
    std::vector<Candidato*> candidatos;
    int*    tempos;
    Logger* logger;

    // State
    EstadoDebate* estadoAtual;

    // Fila de DR
    std::queue<Candidato*> filaDR;
    bool drPermitido;   // false durante execucao do DR

    Candidato*  inquiridor;
    Candidato*  inquirido;

private:
    Cronometro* cronometro;
    std::string faseAtual;
    int         rodadaAtual;
    int         totalRodadas;

public:
    GerenciadorDebate();
    ~GerenciadorDebate();

    void sortearInquiridor();
    void definirInquirido(int id);
    void iniciarFase(int tempo);
    void registrarAcao(const std::string& categoria, const std::string& acao);
    void proximaAcao() override;
    bool temCandidatosDisponiveis();
    int  getRodadaAtual()     const;
    int  getTotalCandidatos() const;
    std::string getFaseAtual() const;
    void setFaseAtual(const std::string& f);

    // DR
    void solicitarDR(int idCandidato);
    void executarDireitos();
    void mudarEstado(EstadoDebate* novoEstado);
};

#endif
