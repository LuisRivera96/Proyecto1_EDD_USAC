/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//
#ifndef LISTAM
#define LISTAM
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "NodoListaM.cpp"
using namespace std;

class ListaM{
private:
    NodoListaM* inicio;
    NodoListaM* fin;
public:
    ListaM(){
        inicio = NULL;
        fin = NULL;
    }
    
    NodoListaM* getInicio(){
        return this->inicio;
    }
    
    NodoListaM* getFin(){
        return this->fin;
    }
    
    bool vacia(){
        if(inicio == NULL){
            return true;
        }else{
            return false;
        }
    }
    
    void addMatriz(int capa,Matriz* matriz){
        NodoListaM* nuevo = new NodoListaM(capa,matriz);
        if(inicio == NULL){
            
            inicio = nuevo;
            fin = nuevo;
            cout<<"Se anadio capaInici"<<capa<<endl;
        }else{
            
            fin->setSiguiente(nuevo);
            fin = nuevo;
            cout<<"Se anadio capaDESPUES "<<capa<<endl;
            
        }
    }
    
    Matriz* buscar(string capa){
        NodoListaM* temp = inicio;
        while(temp != NULL){
            if(temp->getCapa() == stoi(capa)){
               return temp->getMatriz();
            }
            temp = temp->getSiguiente();
        }
        
    }
};
#endif