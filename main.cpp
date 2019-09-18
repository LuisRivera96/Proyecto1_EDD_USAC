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
ListaM* filtroS;
ListaFilters* filters;
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
//METODO QUE CARGA LA IMAGEN A TRAVES DE ARCHIVOS .CSV Y LOS AGREGA POR CAPAS A UNA LISTA LA CUAL SE INGRESA A UN NODO ARBOL
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
       
}
}
//METODO QUE RECORRE EL ARCHVIDO DE CONFIG.CSV PARA PODER SACAR SUS DATOS
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
//VECTOR PARA PODER RECORRER DATOS DE UN ARCHIVO
vector<string> split(string cadena,char delimiter){
    stringstream ss(cadena);
    string item;
    vector<string> splittedStrings;
    while(getline(ss,item,delimiter)){
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}

//METODO QUE RECIBE LOS CSV Y AGREGA EN CAPAS  LAS CUALES SE VAN AGREGANDO A UNA LISTA DE CAPAS
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

//SELECCIONAR IMAGEN PARA TRABAJAR CON ELLA LOS FILTROS Y REPORTES
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
         filters = new ListaFilters();
         system("cmd /c cls");
         menuP();
    }
    
}



//MENU DE REPORTES
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
            system("cmd /c cls");
            cout<<"Filters Report.\n";
            filtersReport();
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
//MENU PARA VER LAS CAPAS GRAFICADAS POR GRAPHIZ
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
//REPORTE DE LINEALZACION DE LA MATRIZ SELECCIONADA
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

//EXPORTAR IMAGEN ORIGINAL O ALGUNO DE LOS FILTROS APLICADOS
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
        {
            exportArchivos(to_string(reporte));
            system("cmd /c cls");
            menuP();
            break;
        }
        case 2:
        {
            system("cmd /c cls");
            cout<<"Menu Seleccion Filtro a Exportar.\n";
            cout << "===========================SELECT FILTERS EXPORT==============================\n";
            filters->listFilters();
            cout << "2 - BACK.\n";
            cin>>filterS;
            if(filterS.compare("2") == 0){
                system("cmd /c cls");
                menuP();
            }
            NodoFilters* temporal = filters->getInicio();
            do{
                if(temporal->getFilter().compare(filterS) == 0){
                    filtroS = temporal->getCubo();
                }
                temporal = temporal->getSiguiente();
            }while(temporal != filters->getInicio());
            exportArchivos(to_string(reporte));
            break;
    }
        case 3:
        {
            cout<<"BACK\n";
            system("cmd /c cls");
            menuP();
            break;
        }
        default:
            cout<<"Error ingrese una opcion correcta\n";
            break;
        
    }
}
//EXPORTAR A HTML Y CSS IMAGEN SELECCIONADA
void exportArchivos(string opcion){
    if(opcion.compare("1") == 0){
        NodoListaM* temp = cuboSeleccionado->getInicio();
        Matriz* temporalM = new Matriz();
        //cout<<"n "<<nodoActual->getNombre()<<endl;
        int pixelT = nodoActual->getImageW()*nodoActual->getImageH();
        string creacionHTML = "Exports/"+nodoActual->getNombre()+".html";
        string creacionCSS = "Exports/"+nodoActual->getNombre()+".css";
        
        //HTML
        ofstream file;
        file.open(creacionHTML);
        file << "<!DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "<link rel=\"stylesheet\" href=\""+nodoActual->getNombre()+".css\">\n";
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
        NodoListaM* temp = filtroS->getInicio();
        Matriz* temporalM = new Matriz();
        //cout<<"n "<<nodoActual->getNombre()<<endl;
        int pixelT = nodoActual->getImageW()*nodoActual->getImageH();
        string creacionHTML = "Exports/"+nodoActual->getNombre()+".html";
        string creacionCSS = "Exports/"+nodoActual->getNombre()+".css";
        
        //HTML
        ofstream file;
        file.open(creacionHTML);
        file << "<!DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "<link rel=\"stylesheet\" href=\""+nodoActual->getNombre()+".css\">\n";
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
    }
}
//RGB A HEXADECIMAL
string RGBtoHex(int dec){
    if(dec < 1) return "00";
    if(dec <10 ) return "0"+to_string(dec);
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
//APLICACION DE FILTROS(FUNCIONALIDAD DE LA APLICACION)
void aplicarFilters(){
    int filter;
    cout<<"===========================FILTERS==============================\n";
    cout<<"1 - Negativo.\n";
    cout<<"2 - Grayscale.\n";
    cout<<"3 - Mirrror.\n";
    cout<<"4 - Collage.\n";
    cout<<"5 - Mosaico.\n";
    cout<<"6 - Regresar.\n";
    cin>>filter;
    switch(filter){
        case 1:
        {
            int seleccion;
            system("cmd /c cls");
            cout<<"=======================NEGATIVO===========================\n";
            cout<<"1 - Aplicar a toda la Imagen\n";
            cout<<"2 - Aplicar a capa Individual\n";
            cin>>seleccion;
            ListaM* actual = cuboSeleccionado;
            NodoListaM* temp = actual->getInicio();
            Matriz* temporalM = new Matriz();
            switch(seleccion){
                case 1:
                    
                    while(temp != NULL){
                        temporalM = temp->getMatriz();
                        NodoFila* fila = temporalM->raizFila;
                        NodoContenido* contenido = fila->siguienteC;
                        while(fila != NULL){
                            contenido = fila->siguienteC;
                            while(contenido != NULL){
                                int RN = 255 - contenido->R;
                                int GN = 255 - contenido->G;
                                int BN = 255 - contenido->B;
                                contenido->RGB = to_string(RN)+"-"+to_string(GN)+"-"+to_string(BN);
                                contenido->R = RN;
                                contenido->G = GN;
                                contenido->B = BN;
                                
                                contenido = contenido->siguiente;
                            }
                            fila = fila->siguiente;
                        }
                        temp = temp->getSiguiente();
                    }
                    filters->addFilter("NEGATIVO",actual);
                    break;
                
            
                case 2:
                    system("cmd /c cls");
                    int capaS;
                    cout<<"=======================ELEGIR CAPA===========================\n";
                    temp = cuboSeleccionado->getInicio();
                    while(temp != NULL){
                        cout<<"--"<<temp->getCapa()<<endl;
                        temp =  temp->getSiguiente();
                    }
                    cin>>capaS;
                    temp = cuboSeleccionado->getInicio();
                    temporalM = new Matriz();
                    while(temp != NULL){
                        if(temp->getCapa() == capaS){
                        temporalM = temp->getMatriz();
                        NodoFila* fila = temporalM->raizFila;
                        NodoContenido* contenido = fila->siguienteC;
                        while(fila != NULL){
                            contenido = fila->siguienteC;
                            while(contenido != NULL){
                                int RN = 255 - contenido->R;
                                int GN = 255 - contenido->G;
                                int BN = 255 - contenido->B;
                                contenido->RGB = to_string(RN)+"-"+to_string(GN)+"-"+to_string(BN);
                                contenido->R = RN;
                                contenido->G = GN;
                                contenido->B = BN;
                                
                                contenido = contenido->siguiente;
                            }
                            fila = fila->siguiente;
                        }
                    }
                        temp = temp->getSiguiente();
                    }
                    filters->addFilter("NEGATIVO",actual);
                    break;
                
                    
                    
                
            }
            break;
    }
        case 2:
            {
            int seleccion;
            system("cmd /c cls");
            cout<<"=======================GRAYSCALE===========================\n";
            cout<<"1 - Aplicar a toda la Imagen\n";
            cout<<"2 - Aplicar a capa Individual\n";
            cin>>seleccion;
            ListaM* actual = cuboSeleccionado;
            NodoListaM* temp = actual->getInicio();
            Matriz* temporalM = new Matriz();
            switch(seleccion){
                case 1:
                    
                    while(temp != NULL){
                        temporalM = temp->getMatriz();
                        NodoFila* fila = temporalM->raizFila;
                        NodoContenido* contenido = fila->siguienteC;
                        while(fila != NULL){
                            contenido = fila->siguienteC;
                            while(contenido != NULL){
                                int RN = (int)contenido->R*0.33;
                                int GN = (int)contenido->G*0.59;
                                int BN = (int)contenido->B*0.11;
                                contenido->RGB = to_string(RN)+"-"+to_string(GN)+"-"+to_string(BN);
                                contenido->R = RN;
                                contenido->G = GN;
                                contenido->B = BN;
                                
                                contenido = contenido->siguiente;
                            }
                            fila = fila->siguiente;
                        }
                        temp = temp->getSiguiente();
                    }
                    filters->addFilter("GRAYSCALE",actual);
                    break;
                
            
                case 2:
                    system("cmd /c cls");
                    int capaS;
                    cout<<"=======================ELEGIR CAPA===========================\n";
                    temp = cuboSeleccionado->getInicio();
                    while(temp != NULL){
                        cout<<"--"<<temp->getCapa()<<endl;
                        temp =  temp->getSiguiente();
                    }
                    cin>>capaS;
                    temp = cuboSeleccionado->getInicio();
                    temporalM = new Matriz();
                    while(temp != NULL){
                        if(temp->getCapa() == capaS){
                        temporalM = temp->getMatriz();
                        NodoFila* fila = temporalM->raizFila;
                        NodoContenido* contenido = fila->siguienteC;
                        while(fila != NULL){
                            contenido = fila->siguienteC;
                            while(contenido != NULL){
                                int RN = (int)contenido->R*0.33;
                                int GN = (int)contenido->G*0.59;
                                int BN = (int)contenido->B*0.11;
                                contenido->RGB = to_string(RN)+"-"+to_string(GN)+"-"+to_string(BN);
                                contenido->R = RN;
                                contenido->G = GN;
                                contenido->B = BN;
                                
                                contenido = contenido->siguiente;
                            }
                            fila = fila->siguiente;
                        }
                    }
                        temp = temp->getSiguiente();
                    }
                    filters->addFilter("GRAYSCALE",actual);
                    break;
                
                    
                    
                
            }
            break;
    }
            break;
        case 3:
            cout<<"MIRROR\n";
            break;
        case 4:
            cout<<"collage\n";
            break;
        case 5:
            cout<<"MOSAICO\n";
            break;
        case 6:
            system("cmd /c cls");
            menuP();
            break;
        default:
            cout<<"Ingrese una Opcion correcta\n";
            system("cmd /c cls");
            aplicarFilters();
            break;
    }
}
//Filters Report (MENU DE FILTROS APLICADOS EN DONDE SE GRAFICARA EL SELECCIONADO POR CAPA)
void filtersReport(){
   int reporte;
   string filterS;
   string capaSelec;
   cout<<"==============================FILTER REPORT================================\n";
   cout<<"1 - All Filters Report\n";
   cout<<"2 - Individual Filter Report\n";
   cout<<"3 - Regresar\n";
   cin>>reporte;
   switch(reporte){
       case 1:
       {
           filters->getGraphFilters();
           break;
        }
       case 2:
       {
           cout << "===========================SELECT FILTERS EXPORT==============================\n";
           filters->listFilters();
           cin>>filterS;
           NodoFilters* temporal = filters->getInicio();
            do{
                if(temporal->getFilter().compare(filterS) == 0){
                    filtroS = temporal->getCubo();
                }
                temporal = temporal->getSiguiente();
            }while(temporal != filters->getInicio());
            //layer report
            
            system("cmd /c cls");
            NodoListaM* temp = filtroS->getInicio();
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
            temp = filtroS->getInicio();
            Matriz* temporalM = new Matriz();
            while(temp != NULL){
                
                temporalM = temp->getMatriz();
                temp = temp->getSiguiente();
                contI++;
                temporalM->getGrafica(to_string(contI));
            }
            
            
//GRAFICAR CAPA UNICA     
        }else{
            
            Matriz* tempM = filtroS->buscar(capaSelec);
            if(tempM != NULL){
              tempM->getGrafica(capaSelec);
            }else{
                menuLayer();
     
            }
            
        }
            //
           break;
   }
       case 3:
           system("cmd /c cls");
           menuReportes();
           break;
       default:
           cout<<"Ingrese una opcion correcta\n";
           system("cmd /c cls");
           filtersReport();
           break;
   }
}
//MENU PRINCIPAL
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
                 system("cmd /c cls");
                 aplicarFilters();
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

