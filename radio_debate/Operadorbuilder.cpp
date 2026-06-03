#include "Operadorbuilder.hpp"
#include <stdexcept>

OperadorBuilder::OperadorBuilder() : id(0) {}

OperadorBuilder& OperadorBuilder::setId(int i)                   { id = i;      return *this; }
OperadorBuilder& OperadorBuilder::setNome(const std::string& n)   { nome = n;    return *this; }
OperadorBuilder& OperadorBuilder::setPerfil(const std::string& p) { perfil = p;  return *this; }

Operador* OperadorBuilder::build() {
    if (id <= 0)       throw std::invalid_argument("ID do operador invalido.");
    if (nome.empty())  throw std::invalid_argument("Nome do operador vazio.");
    if (perfil.empty()) throw std::invalid_argument("Perfil do operador vazio.");
    return new Operador(id, nome, perfil);
}