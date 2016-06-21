//
//  main.cpp
//  BackTrack2
//
//  Created by Pablo Dubikin on 21/01/16.
//  Copyright © 2016 Pablo Dubikin. All rights reserved.
//

#include <iostream>
#include "Backtracking.hpp"
#include "Kruskal.hpp"
#include "ResuelveLaberinto.hpp"
#include "UtilInteraccion.hpp"
#include "UtilLaberinto.hpp"
#include <stdlib.h>
#include <random>

using namespace std;

//#define N 11 // Tamano del laberinto
#define PARED -1 // Valor para la pared
#define _SLEEP 155

int** lab;
void sistema();
void despedida();

int main(int argc, const char * argv[]) {
    
    cout << "¡¡BIENVENIDO AL SISTEMA DE GENERAR Y RESOLVER LABERINTOS!!" << endl << endl;
    
    sistema();

}

void sistema(){
    
    char op;
    
    cout << " - Para resolver un laberinto al azar, introduce la letra 'a'." << endl;
    cout << " - Para resolver el laberinto original, introduce la letra 'o'." << endl;
    cout << " - Para crear un laberinto personalizado, introduce la letra 'p'." << endl;
    cin >> op;
    cout << endl;
    
    switch (op) {
        case 'a':
            UtilInteraccion::resuelveLabAleatorio(lab);
            break;
            
        case 'o':
            UtilInteraccion::resuelveLabOriginal();
            break;
        case 'p':
            UtilInteraccion::creacionLaberinto(lab);
            break;
        default:
            break;
    }
    
    despedida();
    
}
void despedida(){
    
    char opc = 0;
    cout << endl << "El sistema ha finalizado" << endl << endl << "¿Desea reiniciar el sistema? \n" << endl;
    cout << "s / n" << endl;
    cin >> opc;
    cout << "\n";
    
    switch(opc){
        case 'S':
        case 's':
            sistema();
            break;
        case 'N':
        case 'n':
            cout << "Hasta otra!!!!!!" << endl;
            break;
        default:
            cout << "Dicha opción no se encuentra en el menu";
            break;
        
    }
}


