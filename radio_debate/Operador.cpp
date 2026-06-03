#include "Operador.hpp"

Operador::Operador(int id, const std::string& nome, const std::string& perfil)
    : id(id), nome(nome), perfil(perfil) {}

int         Operador::getId()     const { return id; }
std::string Operador::getNome()   const { return nome; }
std::string Operador::getPerfil() const { return perfil; }

Operador* Operador::clonar() const {
    return new Operador(id, nome, perfil);
}