#ifndef GERENCIADORDEBATE_HPP
#define GERENCIADORDEBATE_HPP

#include <vector>
#include <string>
#include "Mediador.hpp"
#include "Candidato.hpp"
#include "Cronometro.hpp"
#include "Logger.hpp"

class GerenciadorDebate : public Mediador {
public:
    std::vector<Candidato*> candidatos;
    int*    tempos;
    Logger* logger;

private:
    Candidato*  inquiridor;
    Candidato*  inquirido;
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
    int  getRodadaAtual() const;
    int  getTotalCandidatos() const;
};

#endif