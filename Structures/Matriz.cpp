/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>

#include "NodoMatriz.cpp"
using namespace std;

class Matriz{
public:
    NodoFila *raizFila;
    NodoColumna *raizColumna;
    
    Matriz(){
        raizFila = NULL;
        raizColumna = NULL;
    }
    
    
    //////////////////METODO ADD//////////////////////////
    void insertarFila(int fila){
        NodoFila *nuevo = new NodoFila(fila);
        NodoFila *anterior = NULL;
        
        if(raizFila == NULL){
            raizFila = new NodoFila(fila);
            cout << "Primer ValorF\n";
        }else{
            NodoFila *cola = raizFila;
            
            while(cola != NULL && cola->fila < fila){
                anterior = cola;
                cola = cola->siguiente;
            }
            
            if(anterior == NULL){
                nuevo->siguiente = raizFila;
                raizFila->anterior = nuevo;
                raizFila = nuevo;
                cout <<"Se inserto al principio\n";
            }else{
                anterior->siguiente = nuevo;
                nuevo->anterior = anterior;
                
                if(cola != NULL){
                    nuevo->siguiente = cola;
                    cola->anterior = nuevo;
                }
                cout<<"Se inserto en Fila\n";
            }
        }
        
    }
    
    void insertarColumna(int columna){
        NodoColumna *nuevo = new NodoColumna(columna);
        NodoColumna *anterior = NULL;
        
        if(raizColumna == NULL){
            raizColumna = new NodoColumna(columna);
            cout<<"Se inserto PrimeraColumna\n";
        }else{
            NodoColumna *cola = raizColumna;
            
            while(cola != NULL && cola->columna <columna){
                anterior = cola;
                cola = cola->siguiente;
            }
            
            if(anterior == NULL){
                nuevo->siguiente = raizColumna;
                raizColumna->anterior = nuevo;
                raizColumna = nuevo;
                cout<<"Se insertoC al principio\n";
            }else{
                anterior->siguiente = nuevo;
                nuevo->anterior = anterior;
                
                if(cola != NULL){
                    nuevo->siguiente = cola;
                    cola->anterior = nuevo;
                }
                cout<<"Se insertoColumna\n";
            }
        }
    }
    
    NodoContenido* insertarContenidoFila(int R,int G, int B,int x,int y,NodoFila* fila){
        NodoContenido* nuevo = new NodoContenido(R,G,B,x,y);
        
        if (fila->siguienteC == NULL){
            fila->siguienteC = nuevo;
            cout<<"Se inserto ContenidoF\n";
            return fila->siguienteC;
        }else{
            NodoContenido *cola =  fila->siguienteC;
            NodoContenido *temporal = NULL;
            
            while(cola != NULL && cola->y < y){
                temporal = cola;
                cola = cola->siguiente;
            }
            
            if(temporal == NULL){
                nuevo->siguiente = fila->siguienteC;
                fila->siguienteC->anterior = nuevo;
                fila->siguienteC = nuevo;
                cout<<"Se inserto Contenido al Principio\n";
            }else{
                temporal->siguiente = nuevo;
                nuevo->anterior = temporal;
                
                if(cola != NULL){
                    nuevo->siguiente = cola;
                    cola->anterior = temporal;
                }
                cout<<"Se inserto nodo Contenido\n";
            }
        }
        return nuevo;
    }
    
    void insertarContenidoColumna(NodoColumna* columna,NodoContenido* nuevo){
        
        if(columna->abajoC == NULL){
            columna->abajoC = nuevo;
            cout<<"Se inserto NuevoContenidoC\n";
        }else{
            NodoContenido *cFinal = columna->abajoC;
            NodoContenido *cAnterior = NULL;
            
            while(cFinal != NULL && cFinal->x < nuevo->x){
                cAnterior = cFinal;
                cFinal = cFinal->abajo;
            }
            
            if(cAnterior == NULL){
                nuevo->abajo = columna->abajoC;
                columna->abajoC->arriba = nuevo;
                columna->abajoC = nuevo;
                cout<<"Se inserto Nuevo ContenidoC al inicio\n";
            }else{
                cAnterior->abajo = nuevo;
                nuevo->arriba = cAnterior;
                
                if(cFinal != NULL){
                    nuevo->abajo = cFinal;
                    cFinal->arriba = nuevo;
                }
                cout<<"Se inserto nuevo ContenidoC\n";
            }
        }
    }
    
    
    NodoFila* obtenerFila(int fila){
        NodoFila* temporal = raizFila;
        while(temporal != NULL){
            if(temporal->fila == fila){
                return temporal;
            }
            temporal = temporal->siguiente;
        }
        return NULL;
    }
    
    NodoColumna* obtenerColumna(int columna){
        NodoColumna* temporal = raizColumna;
        while(temporal != NULL){
            if(temporal->columna == columna){
                return temporal;
            }
            temporal = temporal->siguiente;
        }
        return NULL;
    }
    
    void insertarMatriz(int x,int y,int R,int G,int B){
        
        if(obtenerFila(x) == NULL){
            insertarFila(x);
        }
        
        if(obtenerColumna(y) == NULL){
            insertarColumna(y);
        }
        
        NodoFila* f_seleccionada = obtenerFila(x);
        NodoColumna* c_seleccionada = obtenerColumna(y);
        NodoContenido* nuevo = NULL;
        nuevo = insertarContenidoFila(R,G,B,x,y,f_seleccionada);
        insertarContenidoColumna(c_seleccionada,nuevo);;
    }
    
    
    //
    
};

