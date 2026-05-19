#include <iostream>
#include "Fachada.hpp"
#include "Candidato.hpp"
#include "Eleitor.hpp"

int main() {
    // Cria candidatos com partido
    Candidato* c1 = new Candidato(1, "Joao Silva",  "Partido A");
    Candidato* c2 = new Candidato(2, "Maria Souza", "Partido B");
    Candidato* c3 = new Candidato(3, "Pedro Alves", "Partido C");

    // Cadastra eleitores (Observer) — construtor ja chama candidato->cadastrar(this)
    Eleitor* e1 = new Eleitor("Ana",    c1);
    Eleitor* e2 = new Eleitor("Carlos", c1);
    Eleitor* e3 = new Eleitor("Lucia",  c2);
    Eleitor* e4 = new Eleitor("Bruno",  c3);

    // Tempos: [0]=PERGUNTA [1]=RESPOSTA [2]=REPLICA [3]=TREPLICA
    int tempos[] = {30, 60, 30, 30};

    Fachada* fachada = Fachada::getInstance();
    fachada->configurarDebate({c1, c2, c3}, tempos);

    // Inicia debate — sorteia inquiridor automaticamente
    fachada->iniciarDebate();

    // Define Pedro como inquirido (id=3 — nunca sera sorteado como inquiridor aqui)
    // Em um sistema real, o apresentador escolheria via CLI
    fachada->definirInquirido(3);

    // Inicia fase PERGUNTA — ciclo roda automatico ate TREPLICA
    fachada->iniciarPrimeiraFase();

    fachada->finalizarDebate();

    delete e1; delete e2; delete e3; delete e4;
    delete c1; delete c2; delete c3;

    return 0;
}