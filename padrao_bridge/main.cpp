#include<iostream>
#include<string>
#include "implementador.hpp"
#include "publicacao.hpp"
#include "publicacaoImplBD.hpp"
#include "PublicacaoImplXML.hpp"
#include "livro.hpp"
#include "revista.hpp"


using namespace std;


int main() {
    Implementador* impl = new PublicacaoImplBD();
    
    Livro* livro = new Livro(impl);
    livro->getTitulo();
    livro->getAutor(1);
    livro->getISBN();


    Revista* revista = new Revista(impl);
    revista->getTitulo();
    revista->getAutor(2);
    revista->getArtigo();

    delete impl;
    delete livro;
    delete revista;

    return 0;
}