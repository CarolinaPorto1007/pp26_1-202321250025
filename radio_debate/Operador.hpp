#ifndef OPERADOR_HPP
#define OPERADOR_HPP

#include <string>
#include "Prototype.hpp"

class Operador : public Prototype<Operador> {
private:
    int         id;
    std::string nome;
    std::string perfil;   // ex: "apresentador", "tecnico"

public:
    Operador(int id, const std::string& nome, const std::string& perfil);

    int         getId()     const;
    std::string getNome()   const;
    std::string getPerfil() const;
    Operador*   clonar()    const override;
};

#endif