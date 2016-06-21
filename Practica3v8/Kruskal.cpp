#include "Kruskal.hpp"
#include "UtilLaberinto.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

void changeLab(int anterior, int nuevo, int N, int **&lab);

int obtenerCoordenadaAleatoria(int N){
    int r = UtilLaberinto::getRandom(N-1);
    while(r<=0
          || r >= N-1)
        r = UtilLaberinto::getRandom(N-1);
    return r;
}

/*
 * Genera un laberinto de N*N aleatorio utilizando el algoritmo adaptado de Kruskal.
 */
void Kruskal::generarKruskal(int **&lab, int &exito, int nCeldas, int N, bool verGeneracion){
    
    if(verGeneracion){
        UtilLaberinto::printLab(0, 0, N, lab);
        usleep(17500);
    }
    
    // Enteros aleatorios que servirán como coordenadas.
    int y = 0, x = 0;
    
    if(exito>=nCeldas-1) return;
    
    // Mientras que los dos son pares o impares (tienen que ser distintos, como se explica en la memoria).
    while( (y%2==0 && x%2==0) || (y%2!=0 && x%2!=0) ){
        y = obtenerCoordenadaAleatoria(N);
        x = obtenerCoordenadaAleatoria(N);
    }
    
    // Enteros auxiliares. Servirán como coordenadas de las celdas colindantes a la parede actual.
    int prevX, nextX, prevY, nextY;
    
    // Guardarán los pesos de la celda anterior y posterior a la pared actual.
    int prev, next;
    
    // Calcula los pesos de las celdas correspondientes y los guarda en prev y next.
    if(y%2!=0){
        // La pared es vertical.
        prevX = x-1;
        nextX = x+1;
        prev = lab[y][prevX];
        next = lab[y][nextX];
    } else {
        // La pared es horizontal.
        prevY = y-1;
        nextY = y+1;
        prev = lab[prevY][x];
        next = lab[nextY][x];
    }
    
    // Si los pesos de las dos celdas son distintos, cambiamos los pesos convenientes.
    if(prev!=next){
        
        // Le ponemos el peso de una de las celdas a la pared.
        lab[y][x] = next;
        
        // Ponemos todas las celdas que tengan peso prev, peso next.
        changeLab(prev, next, N, lab);
        exito++;
    }
    
    // LLamada recursiva.
    Kruskal::generarKruskal(lab, exito, nCeldas, N, verGeneracion);
    
}

void changeLab(int anterior, int nuevo, int N, int **&lab){
    for(int i=0; i<N;i++){
        for(int j=0; j<N; j++){
            if(lab[i][j] == anterior)
                lab[i][j] = nuevo;
        }
    }
}

