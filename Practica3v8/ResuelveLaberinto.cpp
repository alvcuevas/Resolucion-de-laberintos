#include "ResuelveLaberinto.hpp"
#include "UtilLaberinto.hpp"
#include <iostream>

int _menorArista(int izquierda,int arriba,int derecha,int abajo, int **lab);

bool esMiga(int currY, int currX);
void getNuevasCoord(int &y, int &x, int direccion);

bool sinSalida(int arriba,int abajo,int izquierda,int derecha);

/* Resuelve un laberinto mediante el método de la vuelta a atrás.
 *
 * curr Y y currX son la "posicion actual" del sistema.
 * exito es verdadero solo si se ha llegado a la celda correspondiente con la salida.
 * lab es el array dinámico de dos dimensiones correspondiente al laberinto.
 * salida x e y son las coordenadas de salida.
 * N es el tamaño del laberinto.
 * verMientrasResuelve se sobreentiende por el nombre.
 *
 */
void ResuelveLaberinto::resolver(int &currY, int &currX, bool &exito, int **&lab, int _SALIDA_X, int _SALIDA_Y, int N, bool verMientrasResuelve){
    
    if(verMientrasResuelve){
        UtilLaberinto::printLab(currY, currX, N, lab);
        usleep(175000);
    }
    if(exito) return;
    
    // Coordenadas x e y de las celdas izquierda, arriba, derecha y abajo.
    int xIzq = currX-1, xDer = currX+1;
    int yArr = currY-1, yAba = currY+1;

    // Valores actuales de las celdas izquierda, arriba, derecha y abajo.
    int arriba = yArr >= 0 && currX >= 0 ? lab[yArr][currX] : -1;
    int abajo = yAba >= 0 && currX >= 0 ? lab[yAba][currX] : -1;
    int derecha = xDer >= 0 && currY >= 0 ? lab[currY][xDer] : -1;
    int izquierda = xIzq >= 0 && currY >= 0 ? lab[currY][xIzq] : -1;
    
    // Seleccionamos la celda que tenga el menor peso.
    int menor = _menorArista(izquierda,arriba,derecha,abajo, lab);
    
    // Sumamos uno a la celda actual para "registrar" un nuevo paso por ella.
    lab[currY][currX] += 1;

    // Si es un sin salida le ponemos un peso extra para que no vuelva a visitarlo
    if(sinSalida(arriba,abajo,izquierda,derecha)) lab[currY][currX] += 1;
    
    
    // Actualizamos las coordenadas de currX y currY
    if(izquierda!=-1
       && lab[currY][xIzq] == menor){ // izq libre
        currX -= 1;
    } else if(arriba!=-1
              && lab[yArr][currX]==menor){ // arriba libre
        currY -= 1;
    } else if(derecha!=-1
              && lab[currY][xDer]==menor){ // derecha libre
        currX += 1;
    } else if(abajo!=-1
              && lab[yAba][currX]==menor){ // abajo libre
        currY += 1;
    }
    
    // Si esta en la celda correspondiente a la salida, se ha terminado.
    if(currX==_SALIDA_X && currY==_SALIDA_Y){
        exito = true;
    }
    
    // LLamada recursiva
    resolver(currY,currX,exito, lab, _SALIDA_X, _SALIDA_Y, N, verMientrasResuelve);

    
}


// Devuelve verdadero si tres de las celdas de alrededor son paredes (es una "calle sin salida").
bool sinSalida(int arriba,int abajo,int izquierda,int derecha){
    if((arriba==-1 && abajo == -1 && (izquierda == -1 || derecha == -1))
       || (izquierda==-1 && derecha == -1 && (arriba == -1 || abajo == -1)))
        return true;
    return false;
}

// Calcula y devuelve la menor arista (el menor de los 4 numeros que se le dan).
int _menorArista(int izquierda,int arriba,int derecha,int abajo, int **lab){
    int menor = 99999999;
    if(izquierda != -1)
        menor = izquierda;
    if(arriba != -1
       && arriba < menor)
        menor = arriba;
    if(derecha != -1
       && derecha < menor)
        menor = derecha;
    if(abajo != -1
       && abajo < menor)
        menor = abajo;
    return menor;
}
