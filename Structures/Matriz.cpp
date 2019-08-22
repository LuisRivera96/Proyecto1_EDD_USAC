/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
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
    
    
    ///////////////////////////////////////METODO ADD////////////////////////////////////////////////
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
            
            while(cola != NULL && cola->x < x){
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
            
            while(cFinal != NULL && cFinal->y < nuevo->y){
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
    
    void add(int x,int y,int R,int G,int B){
        
        if(obtenerFila(y) == NULL){
            insertarFila(y);
        }
        
        if(obtenerColumna(x) == NULL){
            insertarColumna(x);
        }
        
        NodoFila* f_seleccionada = obtenerFila(y);
        NodoColumna* c_seleccionada = obtenerColumna(x);
        NodoContenido* nuevo = NULL;
        nuevo = insertarContenidoFila(R,G,B,x,y,f_seleccionada);
        insertarContenidoColumna(c_seleccionada,nuevo);;
    }
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////METODO GRAFICAR///////////////////////////////////////
    string graficar(NodoFila* fila,NodoColumna* columna){
        string line1 = "";
        NodoFila* auxiliar = fila;
        NodoContenido* contenido = fila->siguienteC;
        while(auxiliar != NULL){
            if(auxiliar == fila){
                line1 += auxiliar->XF +"[label=\""+auxiliar->XF+"\" pos=\"5,3!\"  style = filled, fillcolor = bisque1, group=1];\n"; 
            }else{
               line1 += auxiliar->XF +"[label=\""+auxiliar->XF+"\"  style = filled, fillcolor = bisque1, group=1];\n"; 
            }
            
            if(auxiliar->siguiente != NULL){
                line1 += auxiliar->XF + " -> " + auxiliar->siguiente->XF + " -> " + auxiliar->XF+";\n";
            }
            
            auxiliar = auxiliar->siguiente;
            
        }
        
        NodoColumna* auxiliarC = columna;
        string rank = "{rank=same; ";
        while(auxiliarC != NULL){
            line1 += auxiliarC->YC +"[label=\""+auxiliarC->YC+"\" style=filled, fillcolor=lightskyblue, group="+to_string(auxiliarC->columna+1)+"];\n";
            rank += auxiliarC->YC+";";
            if(auxiliarC->siguiente != NULL){
                line1 += auxiliarC->YC + " -> " + auxiliarC->siguiente->YC + " -> " + auxiliarC->YC+";\n";
            }
            auxiliarC = auxiliarC->siguiente;
        }
        line1 += "header ->"+raizFila->XF+";\n";
        line1 += "header ->"+raizColumna->YC+";\n";
        rank += "header;}\n\n";
        line1 += rank;
        
        ///contenido
        auxiliar = fila;
        while(auxiliar != NULL){
            
            string rank2 = "{rank=same; "+auxiliar->XF+"; ";
            contenido = auxiliar->siguienteC;
            while(contenido != NULL){
                
                line1 += contenido->XY +"[label=\""+contenido->RGB+"\" group="+to_string(contenido->x+1)+"];\n";
                
                rank2 += contenido->XY+";";
                if(contenido->siguiente != NULL){
                    line1 += contenido->XY + " -> " + contenido->siguiente->XY + " -> " + contenido->XY +";\n";
                }
                contenido = contenido->siguiente;
                
            }
            
            rank2 += "}\n";
            line1 += rank2;
            line1 += auxiliar->XF + " -> " + auxiliar->siguienteC->XY+"\n";
            auxiliar = auxiliar->siguiente;
            
        }
        ///
        auxiliarC = columna;
        while(auxiliarC != NULL){
            line1 += auxiliarC->YC + " -> " + auxiliarC->abajoC->XY+";\n";
            contenido = auxiliarC->abajoC;
            while(contenido != NULL){
                if(contenido->abajo != NULL){
                    line1 += contenido->XY + " -> " + contenido->abajo->XY + " -> " + contenido->XY +";\n";
                }
                contenido =  contenido->abajo;
            }
            
            
            auxiliarC = auxiliarC->siguiente;
        }
        
        
        //
        
        return line1;
    }
    
    
    
    void getGrafica(){
        string dot = "";
        dot += "digraph DISPERSA{\n";
        dot += "rankdir = TB;";
        dot += "node[shape=rectangle, height=0.5, width=1.7];\n";
        dot += "graph[nodesep = 0.5];\n";
        dot += "header[label=\"MATRIX\" style=filled, fillcolor=firebrick1, group =1];\n";
        //dot += graficarColumna(raizColumna);
        dot += graficar(raizFila,raizColumna);   
        dot += "}";
        cout << dot;
        ofstream file;
        file.open("Dispersa.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg Dispersa.dot -o Dispersa.jpg");
        system("cmd /c Dispersa.jpg");

        
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
};

