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
#include <string>
#include <string.h>
#include "Matriz.cpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Matriz m;
    m.add(1,10,255,229,204);
    m.add(2,10,6,229,204);
    m.add(15,10,255,229,204);
    m.add(3,6,255,229,204);
    m.add(5,2,255,229,204);
    m.add(16,11,255,229,204);
    m.add(4,1,255,229,204);
    m.add(1,1,255,229,204);
    m.add(2,2,255,229,204);
    m.add(2,3,255,229,204);
    m.add(15,1,255,229,204);
    m.add(15,2,255,229,204);
    m.add(15,3,255,229,204);
    m.add(5,10,255,22,22);
    m.getGrafica();
    return 0;
}

