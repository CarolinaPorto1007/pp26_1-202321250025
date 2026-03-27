#pragma once
#include<iostream>
#include<string>
using namespace std;

class Publicacao; 

class Implementador{
    public:
        virtual string getDados(Publicacao *tipo) = 0;
        virtual ~Implementador() {}
};
