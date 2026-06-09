#ifndef OBSERVADOR_HPP
#define OBSERVADOR_HPP

#include <string>

class Observador {
public:
    virtual void atualizar() = 0;
    virtual void atualizarDR(const std::string& nomeCandidato,
                              const std::string& partido) = 0;
    virtual ~Observador() {}
};

#endif