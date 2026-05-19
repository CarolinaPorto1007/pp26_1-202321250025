#include "Candidato.hpp"

Candidato::Candidato(int id, const std::string& nome, const std::string& partido)
    : id(id), nome(nome), partido(partido), jaPerguntou(false)
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
std::string Candidato::getPartido()     const { return partido; }
bool        Candidato::getJaPerguntou() const { return jaPerguntou; }
void        Candidato::marcarComoInquiridor()  { jaPerguntou = true; }