#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include <string>
#include <list>
#include "Observador.hpp"
#include "Microfone.hpp"

class Candidato {
protected:
    int         id;
    std::string nome;
    bool        jaPerguntou;
    std::list<Observador*> observadores;

public:
    Microfone* microfone;

    Candidato(int id, const std::string& nome);
    virtual ~Candidato();

    void cadastrar(Observador* o);
    void remover(Observador* o);
    void notificar();
    void notificarDR();         // notificacao especifica de DR

    int         getId()          const;
    std::string getNome()        const;
    bool        getJaPerguntou() const;
    void        marcarComoInquiridor();

    virtual std::string getPartido() const = 0;
};

#endif