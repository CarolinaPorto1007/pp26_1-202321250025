#ifndef FACHADA_HPP
#define FACHADA_HPP

#include <vector>
#include "GerenciadorDebate.hpp"
#include "Candidato.hpp"

class Fachada {
private:
    static Fachada*    instance;
    GerenciadorDebate* gerenciador;
    Fachada();

public:
    Fachada(const Fachada&)            = delete;
    Fachada& operator=(const Fachada&) = delete;
    ~Fachada();

    static Fachada* getInstance();

    void configurarDebate(const std::vector<Candidato*>& candidatos, int tempos[]);
    void definirInquirido(int idCandidato);
    void iniciarDebate();
    void finalizarDebate();
};

#endif