#ifndef ESTADODEBATE_HPP
#define ESTADODEBATE_HPP

class GerenciadorDebate;

class EstadoDebate {
public:
    virtual void executar(GerenciadorDebate* ctx) = 0;
    virtual void solicitarDR(GerenciadorDebate* ctx, int idCandidato) = 0;
    virtual std::string getNome() const = 0;
    virtual ~EstadoDebate() {}
};

#endif
