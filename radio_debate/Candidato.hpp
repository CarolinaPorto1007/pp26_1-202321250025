#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include <string>
#include <list>
#include "Observador.hpp"
#include "Microfone.hpp"

class Candidato {
private:
    int         id;
    std::string nome;
    std::string partido;
    bool        jaPerguntou;
    std::list<Observador*> observadores;

public:
    Microfone* microfone;

    Candidato(int id, const std::string& nome, const std::string& partido);
    ~Candidato();

    void cadastrar(Observador* o);
    void remover(Observador* o);
    void notificar();

    int         getId()          const;
    std::string getNome()        const;
    std::string getPartido()     const;
    bool        getJaPerguntou() const;
    void        marcarComoInquiridor();
};

#endif