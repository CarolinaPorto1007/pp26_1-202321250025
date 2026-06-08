#ifndef MICROFONE_HPP
#define MICROFONE_HPP

class Microfone {
private:
    int  id;
    bool ligado;
    bool drSolicitado;

public:
    Microfone(int id);

    void ligar();
    void desligar();
    void acionarDR();
    bool getLigado()       const;
    bool isDrSolicitado()  const;
    void resetarDR();
    int  getId()           const;
};

#endif