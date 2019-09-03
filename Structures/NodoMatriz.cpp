/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
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
    string RGB;
    string XY;
    int R;
    int G;
    int B;
    
    NodoContenido(int R,int G, int B,int x, int y){
        RGB = to_string(R)+"-"+to_string(G)+"-"+to_string(B);
        XY = "X"+to_string(x)+"Y"+to_string(y);
        this->x = x;
        this->y = y;
        this->R = R;
        this->G = G;
        this->B = B;
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
    string XF;
    NodoFila(int fila){
        this->fila = fila;
        XF = "Y"+to_string(fila);
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
    string YC;
    NodoColumna(int columna){
        this->columna = columna;
        YC = "X"+to_string(columna);
        siguiente = NULL;
        anterior = NULL;
        adelante = NULL;
        atras = NULL;
        abajoC = NULL;
    }
};


