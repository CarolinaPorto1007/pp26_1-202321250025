#include "Candidato.hpp"

Candidato::Candidato(int id, const std::string& nome)
    : id(id), nome(nome), jaPerguntou(false)
{
    microfone = new Microfone(id);
}

Candidato::~Candidato() { delete microfone; }

void Candidato::cadastrar(Observador* o) { observadores.push_back(o); }
void Candidato::remover(Observador* o)   { observadores.remove(o); }

void Candidato::notificar() {
    for (auto o : observadores)
        o->atualizar();
}

int         Candidato::getId()          const { return id; }
std::string Candidato::getNome()        const { return nome; }
bool        Candidato::getJaPerguntou() const { return jaPerguntou; }
void        Candidato::marcarComoInquiridor()  { jaPerguntou = true; }