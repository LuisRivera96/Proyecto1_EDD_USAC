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
#include <time.h>
#include <fstream>
#include "Matriz.cpp"
#include "ABB.cpp"
using namespace std;

/*
 * 
 */
//
ABB arbol;

//
class Menus{
public:
void menuCarga(){
    string archivo;
    cout<<"Ingrese nombre del Archivo Inicial.\n";
    cout<<"2 - Back.\n";
    cin>> archivo;
    if(archivo.compare("2") == 0){
        system("cls");
        menuP();
    }else{
        arbol.add(archivo);
    }
    
    
}

void menuSelectImage(){
    string entrada;
    cout<<"=======================IMAGES===============================\n";
    arbol.inorden();
    cout<<"2 - BACK\n";
    cin>>entrada;
    if(entrada.compare("2") == 0){
        system("cls");
        menuP();
    }
    
}

void menuReportes(){
    int reporte;
    cout<<"===========================REPORTS==============================\n";
    cout<<"1 - Images Report.\n";
    cout<<"2 - Layer Report.\n";
    cout<<"3 - Matrix Report.\n";
    cout<<"4 - Traversal Report.\n";
    cout<<"5 - Filters Report.\n";
    cout<<"6 - Back.\n";
    cin>>reporte;
    switch(reporte){
        case 1:
            cout<<"Images Report.\n";
            arbol.getGrafica();
            break;
        case 2:
            cout<<"Layer Report.\n";
            break;
        case 3:
            cout<<"Matrix Report.\n";
            break;
        case 4:
            cout<<"Traversal Report.\n";
            system("cls");
            menuTraversal();
            break;
        case 5:
            cout<<"Filters Report.\n";
            break;
        case 6:
            system("cls");
            menuP();
            break;
        default:
            cout<<"Error ingrese una opcion correcta\n";
            break;
        
    }
    
}

void menuTraversal(){
    int reporte;
    cout<<"===========================TRAVERSAL REPORTS==============================\n";
    cout<<"1 - Inorden Report.\n";
    cout<<"2 - Postorden Report.\n";
    cout<<"3 - Preorden Report.\n";
    cout<<"4 - BACK.\n";
    cin>>reporte;
    switch(reporte){
        case 1:
            cout<<"Inorden Report.\n";
            arbol.getGraphIno();
            break;
        case 2:
            cout<<"Postorden Report.\n";
            arbol.getGraphPost();
            break;
        case 3:
            cout<<"Preorden Report.\n";
            arbol.getGraphPre();
            break;
        case 4:
            cout<<"BACK\n";
            system("cls");
            menuReportes();
            break;
        default:
            cout<<"Error ingrese una opcion correcta\n";
            break;
        
    }
}

void menuP(){
    string opcion;
    int numero;
    while(numero != 7){
         cout<<"-----------------------PHOTOGEN++------------------------------------\n";
         cout<<"==============================MENU============================\n";
         cout<<"1 - Insert Image.\n";
         cout<<"2 - Select Image.\n";
         cout<<"3 - Apply Filters.\n";
         cout<<"4 - Manual Editing.\n";
         cout<<"5 - Export Image.\n";
         cout<<"6 - Reports.\n";
         cout<<"7 - Exit.\n";
         cin>> opcion;
         bool ok = true;
        for (string::const_iterator it = opcion.begin(); it != opcion.end() && ok; ++it)
            ok = isdigit(*it);

        if (ok) {
               numero    = atoi(opcion.c_str());
           // std::cout << "El número introducido es: " << numero << std::endl;
        } else {
            cout << "Error!!!" << endl;
            
        }
         
         
         switch(numero){
             case 1:
                system("cls");
                menuCarga();
                break;
             case 2:
                 cout<<"Select Image\n";
                 system("cls");
                 menuSelectImage();
                 break;
             case 3:
                 cout<<"Apply Filters\n";
                 break;
             case 4:
                 cout<<"Manual Editing\n";
                 break;
             case 5:
                 cout<<"Export Image\n";
                 break;
             case 6:
                 cout<<"Reports\n";
                 system("cls");
                 menuReportes();
                 break;
             case 7:
                 cout<<"EXIT\n";
                 break;
             default:
                 cout<<"ERROR\n";
                 break;
                
         }
     }
    
}
};
int main(int argc, char** argv) {
  
    Menus menus;
    menus.menuP();
    return 0;
}

