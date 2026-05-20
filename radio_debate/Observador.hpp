#ifndef OBSERVADOR_HPP
#define OBSERVADOR_HPP

class Observador {
public:
    virtual void atualizar() = 0;
    virtual ~Observador() {}
};

#endif