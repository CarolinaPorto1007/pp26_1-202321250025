#pragma once
#include<iostream>
#include<string>
#include "implementador.hpp"
#include "publicacao.hpp"


using namespace std;

class Revista : public Publicacao{    

    public:
        Revista(Implementador* imp) : Publicacao(imp) {}
        
        string getArtigo(){
           cout << "Revista::getArtigo() chamado" << endl;
           return "";
        }
        
        string getTitulo() override {
        cout << "Revista::getTitulo() chamado" << endl;
        return "";
}
        
        string getAutor(int id) override {
            cout << "Revista::getAutor() chamado" << endl;
            return "";
        }
};