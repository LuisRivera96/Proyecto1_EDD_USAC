/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

class NodoContenido{
public:
    NodoContenido *siguiente;
    NodoContenido *anterior;
    NodoContenido *abajo;
    NodoContenido *arriba;
    NodoContenido *adelante;
    NodoContenido *atras;
    int x;
    int y;
    int R;
    int G;
    int B;
    
    
    NodoContenido(int R,int G, int B,int x, int y){
        this->R = R;
        this->G = G;
        this->B =B;
        this->x = x;
        this->y = y;
        siguiente = NULL;
        anterior = NULL;
        abajo = NULL;
        arriba = NULL;
        adelante = NULL;
        atras = NULL;
    }
};



class NodoFila{
public:
    NodoFila *siguiente;
    NodoFila *anterior;
    NodoFila *adelante;
    NodoFila *atras;
    NodoContenido *siguienteC;
    int fila;
    
    NodoFila(int fila){
        this->fila = fila;
        siguiente = NULL;
        anterior = NULL;
        adelante = NULL;
        atras = NULL;
        siguienteC = NULL;
    }
};

class NodoColumna{
public:
    NodoColumna *siguiente;
    NodoColumna *anterior;
    NodoColumna *adelante;
    NodoColumna *atras;
    NodoContenido *abajoC;
    int columna;
    
    NodoColumna(int columna){
        this->columna = columna;
        siguiente = NULL;
        anterior = NULL;
        adelante = NULL;
        atras = NULL;
        abajoC = NULL;
    }
};


