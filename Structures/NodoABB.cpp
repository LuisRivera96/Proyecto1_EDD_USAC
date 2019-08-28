/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
//
//#include "Matriz.cpp"
//
using namespace std;

class NodoABB{
private:
    NodoABB* izquierda;
    NodoABB* derecha;
   // Matriz* cubo;
    string NombreImagen;
    
public:
    
    NodoABB(string nombre){
        izquierda = NULL;
        derecha = NULL;
//        cubo = NULL;
        NombreImagen = nombre;
    }
    
    //GETS//
    NodoABB* getDerecha(){
        return this->derecha;
    }
    NodoABB* getIzquierda(){
        return this->izquierda;
    }
  /*  Matriz* getMatriz(){
        return this->cubo;
    }*/
    string getNombre(){
        return this->NombreImagen;
    }
    //SETS//
    void setDerecha(NodoABB* derecha){
        this->derecha = derecha;
    }
    void setIzquierda(NodoABB* izquierda){
        this->izquierda = izquierda;
    }
  /*  void setMatriz(Matriz* matriz){
        this->cubo = matriz;
    }*/
    void setNombre(string nombre){
        this->NombreImagen = nombre;
    }
    
};
