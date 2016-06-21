/* 
 * File:   UtilLaberinto.hpp
 * Author: Alvaro
 *
 * Created on 27 de enero de 2016, 14:29
 */

#ifndef UtilLaberinto_hpp
#define UtilLaberinto_hpp

#include <stdio.h>

class UtilLaberinto {
    
public:
    
    static void inicializarLaberinto(int **&lab, int N);
    
    static void rellenarLaberintoConCeros(int **&lab, int N);
    static int rellenarLaberintoConPesos(int **&lab, int N);
    
    static void sustituirPesosPorCeros(int **&lab, int N, int _SALIDA_X, int _SALIDA_Y, int _ENTRADA_X, int _ENTRADA_Y);

    static void printLab(int curry, int currx, int N, int **lab);
    
    /*
     * Recibe un entero "max" y devuelve otro entero aleatorio desde 0 hasta max.
     */
    static int getRandom(int max);
    static int getRandomImpar(int N);
    static int getRandomPar(int N);
    static int getRandomRango(int n, int max);
    static int getRandomImparRango(int n, int max);
};

#endif /* UtilLaberinto_hpp */

