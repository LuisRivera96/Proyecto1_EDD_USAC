/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "ListaM.cpp"
using namespace std;

class NodoFilters{
private:
    NodoFilters* siguiente;
    NodoFilters* anterior;
    string filter;
    ListaM* cubo;
    
public:
    NodoFilters(string filter,ListaM* cubo){
        this->filter = filter;
        this->cubo = cubo;
        siguiente = NULL;
        anterior = NULL;
    }
    
    //GETS//
    string getFilter(){
        return this->filter;
    }
    ListaM* getCubo(){
        return this->cubo;
    }
    NodoFilters* getSiguiente(){
        return this->siguiente;
    }
    NodoFilters* getAnterior(){
        return this->anterior;
    }
    //SETS//
    void setFilter(string filter){
        this->filter = filter;
    }
    void setCubo(ListaM* cubo){
        this->cubo = cubo;
    }
    void setSiguiente(NodoFilters* siguiente){
        this->siguiente = siguiente;
    }
    void setAnterior(NodoFilters* anterior){
        this->anterior = anterior;
    }
    
};