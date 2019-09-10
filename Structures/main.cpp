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
#include <vector>
#include <sstream>
#include <fstream>


#include "ABB.cpp"
#include "ListaFilters.cpp"
#include "ListaM.cpp"
#include "ListaLinealizacion.cpp"

using namespace std;

/*
 * 
 */
//
ABB arbol;
ListaM* cub;
ListaM* cuboSeleccionado;
ListaFilters filters;
Matriz* Capa;
NodoABB* nodoActual;
ListaLinealizacion* linea;
int ImageW,ImageH = 0;
int PixelW,PixelH = 0;
//
class Menus{
public:
void menuCarga(){
    
    cargaImagenes();
    
}

void cargaImagenes(){
    string ruta;
    string datos;
    vector<string> val;
    int fila = 1;
    int columna = 1;
    string capa;
    cub = new ListaM();
   // char pos[] = "";
    cout<<"Ingrese Nombre del Archivo Inicial\n";
    cout<<"2 - Back.\n";
    cin>>ruta;
    string archInicial = ruta+"/"+ruta+".csv";
    if(ruta.compare("2") == 0){
        system("cmd /c cls");
        menuP();
    }else {
       ifstream inicial(archInicial);
       if(inicial.fail()){
           cout<<"No existe la Carpeta o el Archivo\n";
       }else{
           
           while(!inicial.eof()){
               getline(inicial,datos);
               val = split(datos,',');
               for(int i= 0;i<val.size();i++){
                  // cout<<val[i]<<endl;   
                   //cout<<"F"<<fila<<endl;
                   if(fila == 4){
                       cout<<"config"<<endl;
                       leerConfig(ruta,val[i]);
                   }else if(fila>4){
                       if(fila%2 != 0){
                           capa = val[i];
                       }else{
                           
                           cargarCubo(ruta,capa,val[i]);
                            
                       }
                   }
                   fila++;

               }
               
              
               
           }
         
       }
       inicial.close();
       cuboSeleccionado = arbol.BusquedaI(ruta);
       nodoActual = arbol.ImageB(ruta);
}
}

void leerConfig(string ruta,string config){
    string archSalto = config.replace(config.size()-1,1,"");
    string archInicial = ruta+"/"+archSalto;
    string datos;
    vector<string> val;
    int fila = 1;
       ifstream inicial(archInicial);
       if(inicial.fail()){
           cout<<"No existe la Carpeta o el Archivo\n";
       }else{
           
           while(!inicial.eof()){
               getline(inicial,datos);
               val = split(datos,',');
               for(int i= 0;i<val.size();i++){
                  // cout<<val[i]<<endl;   
                   //cout<<"F"<<fila<<endl;
                   if(fila == 4){
                      ImageW = stoi(val[i]); 
                   }else if(fila == 6){
                       ImageH = stoi(val[i]); 
                   }else if(fila == 8){
                       PixelW = stoi(val[i]);
                   }else if(fila == 10){
                       PixelH = stoi(val[i]);
                   }
                   
                   fila++;

               }
               
              
               
           }
         
       }
       inicial.close();
       

}

vector<string> split(string cadena,char delimiter){
    stringstream ss(cadena);
    string item;
    vector<string> splittedStrings;
    while(getline(ss,item,delimiter)){
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}


void cargarCubo(string ruta,string capaM,string archivo){

        string cadena = "";
        int estado = 0;
        int fila = 0;
        int columna = 1;
        string name = "";
        //
        int R,G,B = 0;
        string dato = "";
        //
        
        //cout<<archivo.size()<<endl;
        string archSalto = archivo.replace(archivo.size()-1,1,"");
        cout<<archSalto<<"*"<<endl;
        string Ncapa = ruta+"/"+archSalto;
        cout<<Ncapa<<"+"<<endl;
        ifstream capas(Ncapa);
        if (capas.fail()) {
            cout << "No se pudo Abrir el Archivo\n";
        } else {
            cout<<"se abrio el archivo\n";
            //capa = NULL;
            Capa = new Matriz();
            while (!capas.eof()) {
                capas >> cadena;
                //cout<<"FilaA "<<fila<<endl;
                fila++;
                for(int i=0;i<cadena.size();i++){
                    char temp = cadena[i];
                    if(estado == 0){
                        if(temp == 88 || temp == 120){
                            //cout<<"temp"<<temp<<endl;
                            estado = 1;
                        }else if(temp >=48 && temp<=57){
                            dato+=temp;
                        }else if(temp == 45){
                            //cout<<"temp"<<temp<<endl;
                            estado = 2;
                            R = stoi(dato);
                            dato = "";
                        }else{
                            estado = 0;
                        }
                    }else if(estado == 1){
                        if(temp == 44){
                            estado = 0;
                            columna++;
                        }
                    }else if(estado == 2){
                        if(temp>=48 && temp<=57){
                            dato+=temp;
                        }else if(temp == 45){
                           // cout<<"temp"<<temp<<endl;
                            estado = 3;
                            G = stoi(dato);
                            dato = "";
                        }
                    }else if(estado == 3){
                        if(temp >= 48 && temp <= 57){
                            dato+= temp;
                        }else if(temp == 44){
                            //cout<<"temp"<<temp<<endl;
                            B = stoi(dato);
                            dato="";
                            estado = 0;
                            cout<<"X:"<<columna<<" Y:"<<fila<<" RGB:"<<R<<G<<B<<endl;
                            //
                            Capa->add(columna,fila,R,G,B);
                                  
                            
                            //
                            columna++;
                        } 
                    }
                }
                //cout<<"Col "<<columna<<endl;
                columna = 1;
                //cout<<"Fila: "<<fila<<endl;
                
                
            }
            
            //cub = NULL;
            
            
        }
        capas.close();

        int cap = stoi(capaM);
        cub->addMatriz(cap, Capa);
        cout << "inserto a la lista\n";
        cout<<"IW "<<ImageW<<" IH "<<ImageH<<" PW "<<PixelW<<" PH "<<PixelH<<endl;
        arbol.add(ruta, cub,ImageW,ImageH,PixelW,PixelH);
        cout<<"se inseto al arbol \n";
        
}


void menuSelectImage(){
    string entrada;
    cout<<"=======================IMAGES===============================\n";
    arbol.inorden();
    cout<<"2 - BACK\n";
    cin>>entrada;
    if(entrada.compare("2") == 0){
        system("cmd /c cls");
        menuP();
    }else{
         cuboSeleccionado = arbol.BusquedaI(entrada);
         nodoActual = arbol.ImageB(entrada);
         system("cmd /c cls");
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
            system("cmd /c cls");
            menuLayer();
            break;
        case 3:
            system("cmd /c cls");
            matrixReport();
            break;
        case 4:
            cout<<"Traversal Report.\n";
            system("cmd /c cls");
            menuTraversal();
            break;
        case 5:
            cout<<"Filters Report.\n";
            break;
        case 6:
            system("cmd /c cls");
            menuP();
            break;
        default:
            cout<<"Error ingrese una opcion correcta\n";
            break;
        
    }
    
}

void menuLayer(){
    string imagen;
    string capaSelec;
    cout<<"===========================LAYER REPORT==============================\n";
    cout<<"Images Loaded"<<endl;
    cout<<"Ingrese el Nombre de la Imagen que desea Graficar"<<endl;
    arbol.inorden();
    cout<<"2 - BACK.\n";
    cin>>imagen;
    if(imagen.compare("2") == 0){
        menuReportes();
    }else{
        ListaM* temporal = arbol.BusquedaI(imagen);
        system("cmd /c cls");
        NodoListaM* temp = temporal->getInicio();
        while(temp != NULL){
            cout<<"--"<<temp->getCapa()<<endl;
            temp =  temp->getSiguiente();
        }
        cout<<"--C Graficar Completa\n"<<endl;
        cin>>capaSelec;
//GRAFICAR COMPLETA
        if(capaSelec.compare("C") == 0 || capaSelec.compare("c") == 0){
            //Matriz* unido = new Matriz();
            int contI = 0;
            temp = temporal->getInicio();
            Matriz* temporalM = new Matriz();
            while(temp != NULL){
                
                temporalM = temp->getMatriz();
                temp = temp->getSiguiente();
                contI++;
                temporalM->getGrafica(to_string(contI));
            }
            
            
//GRAFICAR CAPA UNICA     
        }else{
            
            Matriz* tempM = temporal->buscar(capaSelec);
            if(tempM != NULL){
              tempM->getGrafica(capaSelec);
            }else{
                menuLayer();
     
            }
            
        }
    }
}

void matrixReport(){
    string imagen;
    string capaSelec;
    string linealizacion;
    cout<<"===========================MATRIX REPORT==============================\n";
    cout<<"Images Loaded"<<endl;
    cout<<"Ingrese el Nombre de la Imagen que desea Linealizar"<<endl;
    arbol.inorden();
    cout<<"2 - BACK.\n";
    cin>>imagen;
    if(imagen.compare("2") == 0){
        menuReportes();
    }else{
        ListaM* temporal = arbol.BusquedaI(imagen);
        system("cmd /c cls");
        cout << "=========================LISTA DE CAPAS DE LA IMAGEN=============================\n";
        NodoListaM* temp = temporal->getInicio();
        while(temp != NULL){
            cout<<"--"<<temp->getCapa()<<endl;
            temp =  temp->getSiguiente();
        }
        cin>>capaSelec;
            Matriz* tempM = temporal->buscar(capaSelec);
            if (tempM == NULL) {
                //tempM->getGrafica();
                matrixReport();
            } else {
                system("cmd /c cls");
                string dot = "";
                
                cout << "=========================FORMA DE LINEALIZACION=============================\n";
                cout << "1-- Filas\n";
                cout << "2-- Columnas\n";
                cin>>linealizacion;
                linea = new ListaLinealizacion();
                if(linealizacion.compare("1") == 0){
                    NodoFila* auxF = tempM->raizFila;
                    NodoContenido* auxC = auxF->siguienteC;
                    
                    while(auxF != NULL){
                        auxC = auxF->siguienteC;
                        while(auxC != NULL){
                            linea->addLinealizacion(auxC->XY,auxC->RGB);
                            auxC = auxC->siguiente;
                        }
                        auxF = auxF->siguiente;
                    }
                    linea->getGraficaL("FILAS",capaSelec);
                    
                    
                }else if(linealizacion.compare("2") == 0){
                    linea = new ListaLinealizacion();
                    NodoColumna* auxC = tempM->raizColumna;
                    NodoContenido* auxContenido = auxC->abajoC;
                    while(auxC != NULL){
                        auxContenido = auxC->abajoC;
                        while(auxContenido != NULL){
                            linea->addLinealizacion(auxContenido->XY,auxContenido->RGB);
                            auxContenido = auxContenido->abajo;
                        }
                        auxC = auxC->siguiente;
                    }
                    linea->getGraficaL("COLUMNAS",capaSelec);
                    
                    
                    
                }else{
                  cout<<"No existe esa Opcion\n"; 
                  matrixReport();  
                }

            }
        
        
    }
    
}

//MENU RECORRIDOS ARBOL BUSQUEDA
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
            system("cmd /c cls");
            menuTraversal();
            break;
        case 2:
            cout<<"Postorden Report.\n";
            arbol.getGraphPost();
            system("cmd /c cls");
            menuTraversal();
            break;
        case 3:
            cout<<"Preorden Report.\n";
            arbol.getGraphPre();
            system("cmd /c cls");
            menuTraversal();
            break;
        case 4:
            cout<<"BACK\n";
            system("cmd /c cls");
            menuReportes();
            break;
        default:
            cout<<"Error ingrese una opcion correcta\n";
            break;
        
    }
}

//EXPORTAR IMAGEN
void exportImage(){
    int reporte;
    string filterS;
    cout<<"===========================EXPORT IMAGE==============================\n";
    cout<<"1 - Exportar OG Image.\n";
    cout<<"2 - Filters.\n";
    cout<<"3 - BACK.\n";
    cin>>reporte;
    switch(reporte){
        case 1:
            exportArchivos(to_string(reporte));
            system("cmd /c cls");
            menuP();
            break;
        case 2:
            system("cmd /c cls");
            cout<<"Menu Seleccion Filtro a Exportar.\n";
            cout << "===========================SELECT FILTERS EXPORT==============================\n";
            filters.listFilters();
            cout << "2 - BACK.\n";
            cin>>filterS;
            system("cmd /c cls");
            menuP();
            break;
        case 3:
            cout<<"BACK\n";
            system("cmd /c cls");
            menuP();
            break;
        default:
            cout<<"Error ingrese una opcion correcta\n";
            break;
        
    }
}

void exportArchivos(string opcion){
    if(opcion.compare("1") == 0){
        NodoListaM* temp = cuboSeleccionado->getInicio();
        Matriz* temporalM = new Matriz();
        //cout<<"n "<<nodoActual->getNombre()<<endl;
        int pixelT = nodoActual->getImageW()*nodoActual->getImageH();
        string creacionHTML = "Exports/"+nodoActual->getNombre()+".html";
        string creacionCSS = "Exports/template.css";
        
        //HTML
        ofstream file;
        file.open(creacionHTML);
        file << "<!DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "<link rel=\"stylesheet\" href=\"template.css\">\n";
        file << "</head>\n";
        file << "</head>\n";
        file << "<body>\n";
        file << "<div class=\"canvas\">\n";
        for(int i=0; i<pixelT; i++){
            file << "<div class=\"pixel\"></div>\n";
        }
        file << "</div>\n";
        file << "</body>\n";
        file << "</html>\n";
        file.close();
        //CSS
        ofstream file2;
        file2.open(creacionCSS);
        file2 << "body {\n background :#333333;\nheight : 100vh;\ndisplay: flex;\njustify-content : center;\nalign-items : center;\n}\n";
        file2 << ".canvas {\n";
        file2 << "width: "+to_string(nodoActual->getImageH()*nodoActual->getPixelH())+"px;\n";
        file2 << "height: "+to_string(nodoActual->getImageH()*nodoActual->getPixelH())+"px;\n";
        file2 << "}\n";
        file2 << ".pixel {\n";
        file2 << "width: "+to_string(nodoActual->getPixelW())+"px;\n";
        file2 << "height: "+to_string(nodoActual->getPixelH())+"px;\n";
        file2 << "float: left;\n";
        file2 << "box-shadow: 0px 0px 1px #fff;";
        file2 << "}\n";
        while(temp != NULL){
            temporalM = temp->getMatriz();
            NodoFila* fila = temporalM->raizFila;
            NodoContenido* contenido = fila->siguienteC;
            while(fila != NULL){
                contenido = fila->siguienteC;
                while(contenido != NULL){
                    file2 << ".pixel:nth-child("+to_string((contenido->y-1)*nodoActual->getImageW()+contenido->x)+"){background: "+Hex(contenido->R,contenido->G,contenido->B)+";}\n";
                    contenido = contenido->siguiente;
                }
                fila =  fila->siguiente;
            }
            temp = temp->getSiguiente();
        }
        file2.close();
        
    }else if(opcion.compare("2") == 0){
        
    }
}
//RGB A HEXADECIMAL
string RGBtoHex(int dec){
    if(dec < 1) return "00";
    
    int hex = dec;
    string hexStr = "";
    while(dec > 0){
        hex = dec % 16;
        if(hex < 10)
            hexStr = hexStr.insert(0,string(1,(hex+48)));
        else
            hexStr = hexStr.insert(0,string(string(1,(hex+55))));
        
        dec /= 16;
    }
    
    return hexStr;
}
string Hex(int R, int G,int B){
    string rs = RGBtoHex(R);
    string gs = RGBtoHex(G);
    string bs = RGBtoHex(B);
    return '#'+rs+gs+bs;
}
//
//

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
                system("cmd /c cls");
                menuCarga();
                break;
             case 2:
                 cout<<"Select Image\n";
                 system("cmd /c cls");
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
                 system("cmd /c cls");
                 exportImage();
                 break;
             case 6:
                 cout<<"Reports\n";
                 system("cmd /c cls");
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

