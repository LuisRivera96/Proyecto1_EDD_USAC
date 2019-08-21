/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: user
 *
 * Created on 20 de agosto de 2019, 08:28 PM
 */

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "Matriz.cpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Matriz m;
    m.insertarMatriz(1,1,112,122,112);
    m.insertarMatriz(1,2,112,122,112);
    m.insertarMatriz(2,1,112,122,112);
    m.insertarMatriz(2,2,112,122,112);
    m.insertarMatriz(3,3,112,122,112);
    return 0;
}

