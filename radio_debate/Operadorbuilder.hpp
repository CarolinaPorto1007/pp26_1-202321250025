#ifndef OPERADORBUILDER_HPP
#define OPERADORBUILDER_HPP

#include <string>
#include "Operador.hpp"

class OperadorBuilder {
private:
    int         id;
    std::string nome;
    std::string perfil;

public:
    OperadorBuilder();
    OperadorBuilder& setId(int id);
    OperadorBuilder& setNome(const std::string& nome);
    OperadorBuilder& setPerfil(const std::string& perfil);
    Operador* build();
};

#endif