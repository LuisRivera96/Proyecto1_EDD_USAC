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
#include "ListaM.cpp"
//
using namespace std;

class NodoABB{
private:
    NodoABB* izquierda;
    NodoABB* derecha;
    ListaM* cubo;
    string NombreImagen;
    int imageW;
    int imageH;
    int pixelW;
    int pixelH;
    
public:
    
    NodoABB(string nombre,ListaM* cubo,int imageW,int imageH,int pixelW,int pixelH){
        izquierda = NULL;
        derecha = NULL;
        this->imageW = imageW;
        this->imageH = imageH;
        this->pixelW = pixelW;
        this->pixelH = pixelH;
        this->cubo = cubo;
        NombreImagen = nombre;
    }
    
    //GETS//
    NodoABB* getDerecha(){
        return this->derecha;
    }
    NodoABB* getIzquierda(){
        return this->izquierda;
    }
    ListaM* getCubo(){
        return this->cubo;
    }
    string getNombre(){
        return this->NombreImagen;
    }
    int getImageW(){
        return this->imageW;
    }
    int getImageH(){
        return this->imageH;
    }
    int getPixelW(){
        return this->pixelW;
    }
    int getPixelH(){
        return this->pixelH;
    }
    //SETS//
    void setDerecha(NodoABB* derecha){
        this->derecha = derecha;
    }
    void setIzquierda(NodoABB* izquierda){
        this->izquierda = izquierda;
    }
    void setCubo(ListaM* matriz){
        this->cubo = matriz;
    }
    void setNombre(string nombre){
        this->NombreImagen = nombre;
    }
    void setImageW(int W){
        this->imageW = W;
    }
    void setImageH(int H){
        this->imageH = H;
    }
    void setPixelW(int W){
        this->pixelW = W;
    }
    void setPixelH(int H){
        this->pixelH = H;
    }
};
