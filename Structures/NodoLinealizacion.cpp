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

class NodoLinealizacion{
public:
    NodoLinealizacion* siguiente;
    string XY;
    string RGB;
    
    NodoLinealizacion(string XY, string RGB){
        this->XY = XY;
        this->RGB = RGB;
        siguiente = NULL;
    }
};