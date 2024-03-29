/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "NodoFilters.cpp"
using namespace std;

class ListaFilters{
private:
    NodoFilters* inicio;
    NodoFilters* fin;
public:
    NodoFilters* getInicio(){
        return this->inicio;
    }
    NodoFilters* getFin(){
        return this->fin;
    }
    
    void setInicio(NodoFilters* inicio){
        this->inicio = inicio;
    }
    void setFin(NodoFilters* fin){
        this->fin = fin;
    }
    
    void addFilter(string filter,ListaM* cubo){
        NodoFilters* nuevo = new NodoFilters(filter,cubo);
        if(inicio == NULL){
            inicio = nuevo;
            fin = nuevo;
            inicio->setSiguiente(fin);
            inicio->setAnterior(fin);
            fin->setAnterior(inicio);
            fin->setSiguiente(inicio);
            
            
        }else{
            nuevo->setAnterior(fin);
            nuevo->setSiguiente(inicio);
            fin->setSiguiente(nuevo);
            fin = nuevo;
            inicio->setAnterior(fin);
        }
    }
    
    string graficaFilters(NodoFilters* inicioS){
        string dot = "";
        NodoFilters* aux = inicioS;
        
        do{
            dot += aux->getFilter()+"[label=\""+aux->getFilter()+"\"];\n";
            if(aux->getSiguiente() != NULL){
                dot += aux->getFilter()+" -> "+aux->getSiguiente()->getFilter() + " -> "+aux->getFilter()+";\n";
            }
            aux = aux->getSiguiente();
        }while(aux!= inicio);
        
        
        return dot;
    }
    
    
    
    void listFilters(){
        NodoFilters* temp = inicio;
        do{
           cout<<"--"+temp->getFilter()+"\n";
           temp = temp->getSiguiente(); 
        }while(temp != inicio);
        
    }
    
    void getGraphFilters(){
        string dot = "";
        dot += "digraph FILTERS{\n";
        dot += "compound=true;\n";
        dot += "rankdir=\"LR\"\n";
        dot += "node[shape=\"rectangle\"];\n";
        dot += graficaFilters(inicio);   
        dot += "}";
        //cout << dot;
        ofstream file;
        file.open("FILTERS.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg FILTERS.dot -o FILTERS.jpg");
        system("cmd /c FILTERS.jpg");
    }
};