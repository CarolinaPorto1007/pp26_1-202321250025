#pragma once
#include<iostream>
#include<string>
#include "implementador.hpp"
#include "publicacao.hpp"


using namespace std;
class publicacao;

class PublicacaoImplXML : public Implementador {
    public:
        string getDados(Publicacao* tipo) override {
            cout << "PublicacaoImplXML::getDados() chamado" << endl;
            return "";
        }
};