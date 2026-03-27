#pragma once
#include<iostream>
#include<string>
#include "implementador.hpp"


using namespace std;

class Publicacao{
    protected:
        Implementador* imp;
        
    public:
        Publicacao(Implementador* imp) : imp(imp) {}

        virtual string obterDado(){return imp->getDados(this); }
        virtual string getTitulo() = 0;
        virtual string getAutor(int id) = 0;

        virtual ~Publicacao() {}
};