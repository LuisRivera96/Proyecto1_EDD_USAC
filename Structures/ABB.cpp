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
#include "NodoABB.cpp"
using namespace std;

class ABB{
private:
    NodoABB* raiz;
public:
    ABB(){
        raiz = NULL;
    }
    
    NodoABB* getRaiz(){
        return this->raiz;
    }
    bool vacio(){
        if(raiz == NULL){
            return true;
        }else{
            return false;
        }
    }
    
    //INSERT//
    void add(string name,ListaM* cubo,int imageW,int imageH,int pixelW,int pixelH){
        if(raiz !=NULL){
            return add_recursived(name,raiz,cubo,imageW,imageH,pixelW,pixelH);
        }else{
            NodoABB* nuevo = new NodoABB(name,cubo,imageW,imageH,pixelW,pixelH);
            raiz = nuevo;
            cout<<"Raiz agregada\n";
            
        }
    }
    
    void add_recursived(string name,NodoABB* raiz,ListaM* cubo,int imageW,int imageH,int pixelW,int pixelH){
        if(name.compare(raiz->getNombre()) < 0){
            if(raiz->getIzquierda() !=  NULL){
                add_recursived(name,raiz->getIzquierda(),cubo,imageW,imageH,pixelW,pixelH);
            }else{
                NodoABB* nuevo = new NodoABB(name,cubo,imageW,imageH,pixelW,pixelH);
                raiz->setIzquierda(nuevo);
            }
        }else if(name.compare(raiz->getNombre()) > 0){
            if(raiz->getDerecha() != NULL){
                add_recursived(name,raiz->getDerecha(),cubo,imageW,imageH,pixelW,pixelH);
            }else{
                NodoABB* nuevo = new NodoABB(name,cubo,imageW,imageH,pixelW,pixelH);
                raiz->setDerecha(nuevo);
            }
        }else{
            cout<<"Imagen ya Ingresada\n";
            
        }
    }
    //BUSCAR//
    ListaM* BusquedaI(string image){
        return Busqueda(image,raiz);
    }
    
    ListaM* Busqueda(string image,NodoABB* raiz){
        if(raiz == NULL){
            cout<<"No existe la Imagen\n";
            return NULL;
        }else if(image.compare(raiz->getNombre()) == 0){
            return raiz->getCubo();
        }else if(image.compare(raiz->getNombre()) < 0){
            return Busqueda(image,raiz->getIzquierda());
        }else{
           return Busqueda(image,raiz->getDerecha());
        }
    }
    
    
    NodoABB* ImageB(string image){
        return ImageBR(image,raiz);
    }
    NodoABB* ImageBR(string image,NodoABB* raiz){
        if(raiz == NULL){
            cout<<"No existe la Imagen\n";
            return NULL;
        }else if(image.compare(raiz->getNombre()) == 0){
            return raiz;
        }else if(image.compare(raiz->getNombre()) < 0){
            return ImageBR(image,raiz->getIzquierda());
        }else{
            return ImageBR(image,raiz->getDerecha());
        }
    }
    //RECORRIDOS//
    //INORDEN////////////////////////////////////////////////////////////////////
    string inor = "";
    void inorden(){
        recursived_inorden(raiz);
    }
    void recursived_inorden(NodoABB* raiz){
        if(raiz != NULL){
            recursived_inorden(raiz->getIzquierda());
            inor = raiz->getNombre();
            cout<<"--"<<inor<<"\n";
            recursived_inorden(raiz->getDerecha());
            
        }
        
    }
    string gInorden(NodoABB* rz){
        string Dot="";
        if(rz != NULL){
            Dot += gInorden(rz->getIzquierda());
            Dot += rz->getNombre()+";\n";
            Dot += rz->getNombre() + " -> ";
            Dot += gInorden(rz->getDerecha());
            
            
        }
        
        return Dot;
    }
    
    void getGraphIno(){
        string dot = "";
        dot += "digraph ABB{\n";
        dot += "label=\"Inorden\";\n";
        dot += "rankdir=\"LR\";\n";
        dot += gInorden(raiz);   
        dot += "}";
       // cout << dot;
        ofstream file;
        file.open("ABBINO.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg ABBINO.dot -o ABBINO.jpg");
        system("cmd /c ABBINO.jpg");
    }
    //POSTORDEN///////////////////////////////////////////////////////////////////
    string post = "";
    void postorden(){
        recursived_postorden(raiz);
    }
    void recursived_postorden(NodoABB* raiz){
        if(raiz != NULL){
            recursived_postorden(raiz->getIzquierda());
            recursived_postorden(raiz->getDerecha());
            post = raiz->getNombre();
            cout<<post;
            cout<<"->";
            
        }
        
    }
    string gPostorden(NodoABB* rz){
        string Dot="";
        if(rz != NULL){
            Dot += gPostorden(rz->getIzquierda());
            Dot += gPostorden(rz->getDerecha());
            Dot += rz->getNombre()+";\n";
            Dot += rz->getNombre() + " -> ";
            
            
        }
        
        return Dot;
    }
    
    void getGraphPost(){
        string dot = "";
        dot += "digraph ABB{\n";
        dot += "label=\"PostOrden\";\n";
        dot += "rankdir=\"LR\";\n";
        dot += gPostorden(raiz);   
        dot += "}";
       // cout << dot;
        ofstream file;
        file.open("ABBPOST.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg ABBPOST.dot -o ABBPOST.jpg");
        system("cmd /c ABBPOST.jpg");
    }
    //PREORDEN/////////////////////////////////////////////////////////////////////
    string pre = "";
    void preorden(){
        recursived_preorden(raiz);
    }
    void recursived_preorden(NodoABB* raiz){
        if(raiz != NULL){
            pre = raiz->getNombre();
            cout<<pre;
            cout<<"->";
            recursived_preorden(raiz->getIzquierda());
            recursived_preorden(raiz->getDerecha());
            
            
        }
        
    }
    string gPreorden(NodoABB* rz){
        string Dot="";
        if(rz != NULL){
            Dot += rz->getNombre()+";\n";
            Dot += rz->getNombre() + " -> ";
            Dot += gPreorden(rz->getIzquierda());
            Dot += gPreorden(rz->getDerecha());
            
            
            
        }
        
        return Dot;
    }
    
    void getGraphPre(){
        string dot = "";
        dot += "digraph ABB{\n";
        dot += "label=\"PreOrden\";\n";
        dot += "rankdir=\"LR\";\n";
        dot += gPreorden(raiz);   
        dot += "}";
       // cout << dot;
        ofstream file;
        file.open("ABBPRE.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg ABBPRE.dot -o ABBPRE.jpg");
        system("cmd /c ABBPRE.jpg");
    }
    //GRAPHIZ/////////////////////////////////////////AB///////////////////////////////////////////

    string graficar(NodoABB* raiz) {
        string Dot = "";

        if (raiz != NULL) {
            if(raiz->getDerecha() != NULL || raiz->getIzquierda() != NULL){
            Dot +=  raiz->getNombre() + ":f" + raiz->getNombre() + "[id=" + raiz->getNombre() + ", color=\"blue\"]; \n";
            Dot +=  raiz->getNombre() + "[label=\" <N" + raiz->getNombre() + "I>  | <f" + raiz->getNombre() + "> " + raiz->getNombre() + "\\n" + " | <f" + raiz->getNombre() + "D> \" shape=\"record\"];\n";
            }else{
               Dot +=  raiz->getNombre() + ":f" + raiz->getNombre() + "[id=" + raiz->getNombre() + ", color=\"blue\" shape=\"rectangle\"]; \n"; 
            }
            
            string a = graficar(raiz->getIzquierda());
            if (a != "") {
                Dot += "\""+ raiz->getNombre() + "\" : N" + raiz->getNombre() + "I -> ";
                Dot += " " + a;
            }
            string b = graficar(raiz->getDerecha());
            if (b != "") {
                Dot +=  "\""+raiz->getNombre() + "\" : f" + raiz->getNombre() + "D -> ";
                Dot += " " + b;
            }
        }

        return Dot;
    }
    
    void getGrafica(){
        string dot = "";
        dot += "digraph ABB{\n";
        dot += "compound=true;\n";
        dot += "node[shape=\"Mrecord\"];\n";
        dot += graficar(raiz);   
        dot += "}";
        //cout << dot;
        ofstream file;
        file.open("ABB.dot");
        file << dot;
        file.close();
        system("cmd /c dot -Tjpg ABB.dot -o ABB.jpg");
        system("cmd /c ABB.jpg");
    }
};