#ifndef MICROFONE_HPP
#define MICROFONE_HPP

class Microfone {
private:
    int  id;
    bool ligado;

public:
    Microfone(int id);
    void ligar();
    void desligar();
    bool getLigado() const;
};

#endif
