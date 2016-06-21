//
//  UtilInteraccion.cpp
//  Practica3v8
//
//  Created by Pablo Dubikin on 31/01/16.
//  Copyright © 2016 Pablo Dubikin. All rights reserved.
//
#include <iostream>
#include "UtilLaberinto.hpp"
#include "ResuelveLaberinto.hpp"
#include "UtilInteraccion.hpp"
#include "Kruskal.hpp"
#include "Backtracking.hpp"

#define NORIGINAL   17
#define _ENTRADA_Y  16
#define _ENTRADA_X  5
#define _SALIDA_Y   11
#define _SALIDA_X   16
#define PARED -1

using namespace std;

int genera_lab(int **&lab);
void resuelve_lab(int **&lab, int N, int salidaX, int salidaY, int entradaX, int entradaY);

void UtilInteraccion::creacionLaberinto(int **&lab){
    int N = genera_lab(lab);
    
    int entradaX, entradaY, salidaX, salidaY;
    
    cout << "A continuación introduzca 4 numeros para las posiciones que se le solicite" << endl<< endl;

    cout << "Posicion X de Entrada (entre 0 y " << N << "):" << endl;
    cin >> entradaX;
    while(entradaX<0 || entradaX >= N){
        cout << "El valor introducido no es válido. Inténtelo de nuevo:" << endl;
        cin >> entradaX;
        cout << endl;
    }
        
    cout << "Posicion Y de Entrada " << (entradaX == 0 || entradaX == N ? "(distinto de 0 y de N)" : "(o bien 0 o bien N)" )<< ":" << endl;
    cin >> entradaY;
    while(entradaY<0 || entradaY >= N
          || (entradaX == 0 && entradaY == 0)
          || (entradaX == N && entradaY == 0)){
        cout << "El valor introducido no es válido. Inténtelo de nuevo:" << endl;
    }
    
    cout << "Posicion X de Salida (entre 0 y " << N << "):" << endl;
    cin >> salidaX;
    while(salidaX<0 || salidaX >= N){
        cout << "El valor introducido no es válido. Inténtelo de nuevo:" << endl;
        cin >> salidaX;
        cout << endl;
    }
    
    cout << "Posicion Y de Salida "<< (salidaX == 0 || salidaX == N ? "(distinto de 0 y de N)" : "(o bien 0 o bien N)" )<< ":" << endl;
    cin >> salidaY;
    while(salidaY<0 || salidaY >= N
          || (salidaX == 0 && salidaX == 0)
          || (salidaX == N && salidaX == 0)){
        cout << "El valor introducido no es válido. Inténtelo de nuevo:" << endl;
    }
    
    cout << endl;
    
    cout << "De acuerdo. El laberinto es el siguiente:" << endl;
    
    UtilLaberinto::sustituirPesosPorCeros(lab, N, salidaX, salidaY, entradaX, entradaY);
    UtilLaberinto::printLab(0, 0, N, lab);
    
    cout << endl << "Las coordenadas de entrada son: (" << entradaY << "," << entradaX
        << "). Y las coordenadas de salida son: (" << salidaY << "," << salidaX << ")." << endl << endl;
    
    resuelve_lab(lab,N,salidaX,salidaY,entradaX,entradaY);
}

int genera_lab(int **&lab){
    
    int N = 0;
    char op;
    int y = 0;
    int x = 0;
    int nCeldas = 0;
    int kruskExito = 0;
    
    
    cout << "Introduzca un tamaño (N) impar y mayor que 5 para el laberinto: \n" << endl;
    cin >> N;
    cout << endl;
    
    cout << "Seleccione un modo para generar un nuevo laberinto aleatorio \n" << endl << endl;
    cout << "b -> Laberinto aleatorio por el algoritmo de Backtracking / Vuelta atrás" << endl;
    cout << "k -> Laberinto aleatorio por el algoritmo de Kruskal \n" << endl;

    cin >> op;
    cout << "\n";
    
    bool verGeneracion = false;

    cout << "Indique si quiere ver como se genera el laberinto paso a paso. Tenga en cuenta que si ha elegido un tamaño grande, esto puede llevar un rato. (s / n) ";

    UtilLaberinto::inicializarLaberinto(lab, N);
    
    switch(op){
        case 'B':
        case 'b':

            cin >> op;
            if(op=='s') verGeneracion = true;
    
            UtilLaberinto::rellenarLaberintoConCeros(lab, N);
            Backtracking::generar(y, x, N, lab,verGeneracion);

            break;
        case 'K':
        case 'k':

            cin >> op;
            if(op=='s') verGeneracion = true;

            nCeldas = UtilLaberinto::rellenarLaberintoConPesos(lab, N);
            Kruskal::generarKruskal(lab, kruskExito, nCeldas, N, verGeneracion);
            
            break;
        default:
            cout << "Dicha opción no se encuentra en el menu";
            break;
            
    }
    
    return N;
    
}

void resuelve_lab(int **&lab, int N, int salidaX, int salidaY, int entradaX, int entradaY){
    
    char opc;
    int currX = entradaX;
    int currY = entradaY;
    bool exito = false;
    
    cout << "A continuación, seleccione un modo de resolver el laberinto: \n" << endl;

    cout << "i -> Resolver laberinto de inmediato" << endl;
    cout << "p -> Resolver mediante paso a paso" << endl;
    cin >> opc;
    cout << "\n";
    
    switch(opc){
        case 'I':
        case 'i':
            UtilLaberinto::sustituirPesosPorCeros(lab, N, salidaX, salidaY, entradaX, entradaY);
            ResuelveLaberinto::resolver(currY, currX, exito, lab, salidaX, salidaY, N, false);
            UtilLaberinto::printLab(currY, currX, N, lab);
            break;
        case 'P':
        case 'p':
            UtilLaberinto::sustituirPesosPorCeros(lab, N, salidaX, salidaY, entradaX, entradaY);
            ResuelveLaberinto::resolver(currY, currX, exito, lab, salidaX, salidaY, N, true);
            UtilLaberinto::printLab(currY, currX, N, lab);
            break;

        default:
            cout << "Dicha opción no se encuentra en el menu";
            break;
            
    }
}

int labOriginal[NORIGINAL][NORIGINAL] = {{PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED},
    {PARED, 0, 0, 0, 0, 0, PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, PARED},
    {PARED, 0, PARED, PARED, PARED, PARED, PARED, 0, PARED, 0, PARED, PARED, PARED, 0, PARED, 0, PARED},
    {PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, PARED, 0, PARED},
    {PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 0, PARED, 0, PARED, PARED, PARED, 0, PARED},
    {PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, 0, 0, PARED},
    {PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 0, PARED, PARED, PARED, PARED, PARED, 0, PARED},
    {PARED, 0, PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, 0, 0, 0, 0, PARED},
    {PARED, 0, PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 0, PARED, PARED, PARED, PARED, PARED},
    {PARED, 0, PARED, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, PARED, 0, 0, 0, PARED},
    {PARED, PARED, PARED, PARED, PARED, 0, PARED, 0, PARED, 0, PARED, PARED, PARED, 0, PARED, 0, PARED},
    {PARED, 0, 0, 0, 0, 0, PARED, 0, 0, 0, PARED, 0, 0, 0, PARED, 0, 0},
    {PARED, 0, PARED, PARED, PARED, PARED, PARED, 0, PARED, PARED, PARED, 0, PARED, 0, PARED, PARED, PARED},
    {PARED, 0, PARED, 0, 0, 0, PARED, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, PARED},
    {PARED, 0, PARED, 0, PARED, 0, PARED, PARED, PARED, 0, PARED, PARED, PARED, PARED, PARED, 0, PARED},
    {PARED, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, 0, 0, 0, 0, 0, 0, PARED},
    {PARED, PARED, PARED, PARED, PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED}};

void generarCoordenadasEntradaYSalida( int &entradaY, int &entradaX, int &salidaY, int &salidaX, int N);
int **generarLabDinamico();

void UtilInteraccion::resuelveLabOriginal(){

    int currX = _ENTRADA_X;
    int currY = _ENTRADA_Y-1;
    bool exito = false;

    int **labOriDinamico = generarLabDinamico();
    
    ResuelveLaberinto::resolver(currY, currX, exito, labOriDinamico, _SALIDA_X, _SALIDA_Y, NORIGINAL, false);
    
    cout << " N: " << NORIGINAL << " - Entrada: (" << _ENTRADA_Y << "," << _ENTRADA_X << ") - Salida: (" << _SALIDA_Y << "," << _SALIDA_X << ")" << endl;
    UtilLaberinto::printLab(currY, currX, NORIGINAL, labOriDinamico);
    
}

int **generarLabDinamico(){
    int **retor;
    UtilLaberinto::inicializarLaberinto(retor, NORIGINAL);
    for(int i=0; i<NORIGINAL;i++){
        for(int j=0; j<NORIGINAL;j++){
            if(labOriginal[i][j]==PARED)
                retor[i][j] = PARED;
            else
                retor[i][j] = 0;
        }
    }
    return retor;
        
}

void UtilInteraccion::resuelveLabAleatorio(int **lab){
    
    bool krusk = rand() % (int)(1);
    int nAleatorio = UtilLaberinto::getRandomImparRango(15,29);
    
    UtilLaberinto::inicializarLaberinto(lab, nAleatorio);
    
    if(krusk){
        
        int kruskExito = 0;
        int nCeldas = UtilLaberinto::rellenarLaberintoConPesos(lab, nAleatorio);
        Kruskal::generarKruskal(lab, kruskExito, nCeldas, nAleatorio, false);
    } else {
        
        int y = 0, x = 0;
        UtilLaberinto::rellenarLaberintoConCeros(lab, nAleatorio);
        Backtracking::generar(y, x, nAleatorio, lab, false);
    }
    
    
    int entradaX, entradaY, salidaX, salidaY;
    generarCoordenadasEntradaYSalida(entradaY,entradaX,salidaY,salidaX, nAleatorio);
    
    
    int currX = entradaX;
    int currY = entradaY;
    bool exito = false;
    
    UtilLaberinto::sustituirPesosPorCeros(lab, nAleatorio, salidaX, salidaY, entradaX, entradaY);
    
    cout << endl << " N: " << nAleatorio << " - Entrada: (" << entradaY << "," << entradaX << ") - Salida: (" << salidaY << "," << salidaX << ")" << endl;
    
    ResuelveLaberinto::resolver(currY, currX, exito, lab, salidaX, salidaY, NORIGINAL, false);
    UtilLaberinto::printLab(currY, currX, nAleatorio, lab);
    
}

void generarCoordenadasEntradaYSalida( int &entradaY, int &entradaX, int &salidaY, int &salidaX, int N){
    
    // En el modo aleatorio siempre ponemos la entrada a la izquierda y en la primera mitad, y la salida a la derecha y abajo
    // para que el recorrido sea algo más visible.
    entradaX = 0;
    entradaY = UtilLaberinto::getRandomImparRango(0,N/2);
    
    salidaX = N-1;
    salidaY = UtilLaberinto::getRandomImparRango(N/2,N);
    
}
