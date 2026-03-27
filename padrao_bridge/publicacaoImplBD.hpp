#pragma once
#include<iostream>
#include<string>
#include "implementador.hpp"
#include "publicacao.hpp"

using namespace std;
class publicacao;

class PublicacaoImplBD : public Implementador {
    public:
        string getDados(Publicacao* tipo) override {
            cout << "PublicacaoImplBD::getDados() chamado" << endl;
            return "";
        }
};