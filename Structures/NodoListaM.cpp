/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "Matriz.cpp"

using namespace std;

class NodoListaM{
private:
    NodoListaM* siguiente;
    int capa;
    Matriz* matriz;
public:
    NodoListaM(int capa,Matriz* matriz){
        this->capa = capa;
        this->matriz = matriz;
        siguiente = NULL;
    }
    
    //GETS//
    int getCapa(){
        return this->capa;
    }
    NodoListaM* getSiguiente(){
        return this->siguiente;
    }
    Matriz* getMatriz(){
        return this->matriz;
    }
    //SETS//
    void setCapa(int cap){
        this->capa = cap;
    }
    void setSiguiente(NodoListaM* sigt){
        this->siguiente = sigt;
    }
    void setMatriz(Matriz* matz){
        this->matriz = matz;
    }
    
};