#pragma once
#include<iostream>
#include<string>
#include "implementador.hpp"
#include "publicacao.hpp"


using namespace std;

class Livro : public Publicacao{    

    public:
        Livro(Implementador* imp) : Publicacao(imp) {} 

        string getISBN(){
           cout << "Livro::getISBN() chamado" << endl;
    return "";
        }
        
        string getTitulo() override {
    cout << "Livro::getTitulo() chamado" << endl;
    return "";
}
        
        string getAutor(int id) override {
            cout << "Livro::getAutor() chamado" << endl;
    return "";
        }
};