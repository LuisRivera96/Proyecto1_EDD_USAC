/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include "NodoLinealizacion.cpp"
using namespace std;

class ListaLinealizacion{
public:
    NodoLinealizacion* inicio;
    NodoLinealizacion* fin;
    
    ListaLinealizacion(){
        inicio = NULL;
        fin = NULL;
    }
    
    void addLinealizacion(string XY,string RGB){
        NodoLinealizacion* nuevo = new NodoLinealizacion(XY,RGB);
        if(inicio == NULL){
            inicio = nuevo;
            fin = nuevo;
        }else{
            fin->siguiente = nuevo;
            fin = nuevo;
        }
    }
    
    void getGraficaL(string Line,string imagen){
        string dot = "";
        NodoLinealizacion* temp = inicio;
        dot = "";
        dot += "digraph FILAS{\n";
        dot += "compound=true;\n";
        dot += "rankdir=\"LR\";\n";
        dot += "label=\"Linealizacion Por Filas: Capa " + imagen + "\";\n";
        dot += "node[shape=\"rectangle\"];\n";
        while(temp != NULL){
            dot += temp->XY+"[label=\"("+temp->XY+") "+temp->RGB+"\"];\n";
            temp = temp->siguiente;
        }
        
        temp = inicio;
        while(temp != NULL){
            if(temp->siguiente != NULL){
                dot += temp->XY + " -> " + temp->siguiente->XY+";\n";
            }
            temp = temp->siguiente;
        }
        
        dot += "}";
                    //cout << dot;
        ofstream file;
        file.open("LINEALIZACION.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg LINEALIZACION.dot -o LINEALIZACION.jpg");
        system("cmd /c LINEALIZACION.jpg");
    }
};