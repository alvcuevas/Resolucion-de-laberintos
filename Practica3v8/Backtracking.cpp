#include <iostream>
#include <stdlib.h>
#include "Backtracking.hpp"
#include "UtilLaberinto.hpp"

void getNuevasCoord(int &y, int &x, int direccion);
void romperPared(int y, int x, int direccion, int **lab);
void getNext(int &dire);
bool direccionValida(int y, int x, int direccion, int N, int **lab);
int _getRandomForMaze(int N);


void Backtracking::generar(int y, int x, int N, int **lab, bool verMientrasGenera){
    
    if(verMientrasGenera){
        UtilLaberinto::printLab(0, 0, N, lab);
        usleep(175000);
    }
    
    if(x == 0 && y == 0){
        x = _getRandomForMaze(N);
        y = _getRandomForMaze(N);
    }
    
    
    // El numero para hacer el bucle. El bucle empezará en una dirección al azar y luego
    // va a la siguiente con el getNext(currDireccion)
    int numVecinos = 4;
    int currDireccion = UtilLaberinto::getRandom(4);
    
    
    // Por cada vecino, si no ha sido visitado, rompemos la pared y lo visitamos (llamada recursiva
    // con las coord del vecino).
    // Si ha sido visitado, hacemos getNext y comprobamos el siguiente vecino.
    // Si todos los vecinos de las coordenadas y,x han sido visitados se termina esta iteración y se
    // vuelve a un nivel anterior en la recursividad.
    for(int i=0;i<numVecinos;i++){
        
        // Esto comprueba que desde las coordenadas y,x se puede ir a la direccion currDireccion.
        // Devolverá false si la celda en dirección currDireccion ya ha sido visitada o no existe.
        if(direccionValida(y, x, currDireccion, N, lab)){
            
            // El vecino no ha sido visitado.
            // Este método pone un 1 en la celda actual, la pared y la celda adyacente a la que
            // nos vamos a 'mover'.
            romperPared(y, x, currDireccion, lab);
            
            
            // Obtenemos las coordenadas de la celda siguiente hacia la direccion currDireccion.
            int nextX = x, nextY = y;
            getNuevasCoord(nextY, nextX, currDireccion);
            
            
            // Llamada recursiva con la celda siguiente.
            generar(nextY, nextX, N, lab, verMientrasGenera);
        }
        
        // Esto devuelve la siguiente dirección. Si currDireccion == 3, la siguiente será 0.
        getNext(currDireccion);
    }
}

/*
 * Este método recibe unas coordenadas x e y (entrada y salida), y una dirección (de 0 a 3).
 *
 * Devuelve nuevas coordenadas en x e y, "desplazándolas" hacia la dirección que se haya indicado.
 *
 */
void getNuevasCoord(int &y, int &x, int direccion){
    switch (direccion) {
        case 0:
            x = x-2;
            break;
        case 1:
            y = y-2;
            break;
        case 2:
            x = x+2;
            break;
        case 3:
            y = y+2;
            break;
    }
}

/*
 * Este método altera el laberinto. Recibe unas coordenadas x e y, una dirección (de 0 a 3) y un array dinámico de enteros de dos dimentiones.
 * 
 * Tomando como referencia la celda en la posición (x, y), este método pone un 1 sobre la pared y la celda adyacentes en la dirección indicada.
 *
 * Este método da por sentado que la posición en la que va a colocar un 1 existe. Esto se tiene que comprobar antes de llamarlo.
 *
 */
void romperPared(int y, int x, int direccion, int **lab){
    
    lab[y][x] = 1;
    
    switch (direccion) {
        case 0:
            lab[y][x-1] = 1;
            lab[y][x-2] = 1;
            break;
        case 1:
            lab[y-1][x] = 1;
            lab[y-2][x] = 1;
            break;
        case 2:
            lab[y][x+1] = 1;
            lab[y][x+2] = 1;
            break;
        case 3:
            lab[y+1][x] = 1;
            lab[y+2][x] = 1;
            break;
    }
}


/*
 * Este método recibe unas coordenadas x e y, una dirección (de 0 a 3 donde 0 es izq), un entero N y un array dinámico de enteros
 * de dos dimensiones (lab).
 *
 * Es utilizado desde el método de creación de laberintos por backtracking. Se llama a este método para comprobar si una celda tiene
 * otra celda vecina sin visitar (su peso es 0) en la dirección indicada.
 *
 * Adicionalmente, devuelve falso si, desde la posición (x,y), moviendonos hacia la dirección (direccion), nos salimos del laberinto.
 *
 */
bool direccionValida(int y, int x, int direccion, int N, int **lab){
    
    // Comprobar que no se sale del laberinto
    if(x==1&&direccion==0)
        return false;
    if(x==N-2&&direccion==2)
        return false;
    if(y==1&&direccion==1)
        return false;
    if(y==N-2&&direccion==3)
        return false;
    
    // Devuelve verdadero si la celda [y][x] es 0 (no ha sido visitada)
    switch (direccion) {
        case 0:
            return (lab[y][x-2]==0);
        case 1:
            return (lab[y-2][x]==0);
        case 2:
            return (lab[y][x+2]==0);
        case 3:
            return (lab[y+2][x]==0);
    }
    
    return true;
}


/**
 * Este método recibe un entero N que es el numero de columnas y filas del laberinto
 * y devuelve un entero impar al azar desde el 1 menor que N.
 * 
 * Es un método privado que solo se llama desde esta clase.
 */
int _getRandomForMaze(int N){
    
    int r = UtilLaberinto::getRandom(N);
    while(r<=0
          || r >= N-1
          || r % 2 == 0)
        r = UtilLaberinto::getRandom(N);
    return r;
}


// Método de ayuda sencillo para conseguir que un entero nunca sea > 3.
void getNext(int &dire){
    if(dire==3) dire = 0;
    else dire++;
}
