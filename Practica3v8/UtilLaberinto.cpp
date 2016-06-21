#include "UtilLaberinto.hpp"
#include <iostream>
#include <random>

using namespace std;

bool esMiga(int currY, int currX, int **lab);

/*
 * Inicializa el array dinámico con todas las posiciones aleatoriamente.
 */
void UtilLaberinto::inicializarLaberinto(int **&lab, int N){
    lab = new int*[N];
    for(int i = 0; i < N; ++i) {
        lab[i] = new int[N];
    }
}

/*
 * Recibe un laberinto lab y un tamaño N.
 * Pone todas las paredes posibles a -1, y las celdas cada una con un peso distinto.
 *
 */
int UtilLaberinto::rellenarLaberintoConPesos(int **&lab, int N){

    int nCeldas = 0;
    for(int i=0; i<N;i++){
        for(int j=0; j<N; j++){
            if(i%2!=0&&j%2!=0){
                nCeldas++;
                lab[i][j] = nCeldas;
            } else {
                lab[i][j] = -1;
            }
        }
    }
    return nCeldas;
}

/*
 * Recibe un array dinámico de enteros de dos dimensiones y un entero N que corresponde con el numero de filas y columnas (siempre debe ser igual).
 *
 * Rellena con 0 lo que corresponde con las "celdas" del laberinto, y con -1 todas las posibles paredes.
 *
 * Las celdas con 0 son las impares, como se explica en la práctica, y todas las demás son paredes.
 *
 */
void UtilLaberinto::rellenarLaberintoConCeros(int **&lab, int N){
    for(int i=0; i<N;i++){
        for(int j=0; j<N; j++){
            if(i%2!=0&&j%2!=0){
                lab[i][j] = 0;
            } else {
                lab[i][j] = -1;
            }
        }
    }
}


/*
 * Recibe un array dinámico de enteros de dos dimensiones, un entero N (n de filas) y las coordenadas de entrada y de salida para el
 * laberinto.
 *
 * Sustituye con 0 todo lo que no sea -1 en el laberinto, además de la entrada y la salida.
 *
 */
void UtilLaberinto::sustituirPesosPorCeros(int **&lab, int N, int _SALIDA_X, int _SALIDA_Y, int _ENTRADA_X, int _ENTRADA_Y){
    for(int i=0; i<N;i++){
        for(int j=0; j<N; j++){
            if(lab[i][j]!=-1
               || (i==_ENTRADA_Y && j==_ENTRADA_X)
               || (i==_SALIDA_Y && j==_SALIDA_X))
                lab[i][j] = 0;
        }
    }
    
}

/*
 * Imprime el laberinto por pantalla, imprimiendo una P en la posición que se le indique mediante los enteros curry, currx.
 *
 */
void UtilLaberinto::printLab(int curry, int currx, int N, int **lab){
    for(int i=0; i<N;i++){
        cout << endl;
        for(int j=0; j<N; j++){
            if(curry!= 0 && currx!=0
               && (curry == i && currx == j))
                cout << " P";
            else if(lab[i][j]==-1)
                cout << " *";
            else if(i<N-1 && j<N-1 && esMiga(i, j, lab))
                cout << " ·";
            else
                cout << "  ";
        }
    }
    cout << endl;
}

/*
 * Método de ayuda para el método printLab que devuelve verdadero si la posición currY,currX corresponde con una miga de pan.
 *
 * El método para resolver si una posición corresponde con una miga de pan o no se explica en la memoria.
 *
 */
bool esMiga(int currY, int currX, int **lab){
    
    // Calculamos las coordenadas de las celdas colindantes.
    int xIzq = currX-1, xDer = currX+1;
    int yArr = currY-1, yAba = currY+1;
    
    // Obtenemos los pesos de dichas celdas. Si alguna celda no existe su peso será -1.
    int arriba = yArr >= 0 && currX >= 0 ? lab[yArr][currX] : -1;
    int abajo = yAba >= 0 && currX >= 0 ? lab[yAba][currX] : -1;
    int derecha = xDer >= 0 && currY >= 0 ? lab[currY][xDer] : -1;
    int izquierda = xIzq >= 0 && currY >= 0 ? lab[currY][xIzq] : -1;
    
    // Si la posicion actual "pasa por el camino" devolvemos verdadero para que se pinte una miga.
    if(lab[currY][currX]>1){
        if((arriba == 1 && derecha == 1)
           || (arriba == 1 && izquierda == 1)){
            return true;
        }
        if((abajo == 1 && derecha == 1)
           || (abajo == 1 && izquierda == 1)){
            return true;
        }
        if((abajo == 1 && arriba == 1)){
            return true;
        }
        
        if(izquierda == 1 && derecha == 1)
            return true;
    }
    
    // Cuando pasamos por una calle sin salida no volvemos a pasar nunca, por lo que esta quedará con un peso de 1 y el
    // algoritmo pensaría que es parte del camino. Por eso, devolvemos false en cualquiera de estos casos, que validan la
    // existencia de una calle sin salida.
    if(lab[currY][currX]==1){
        
        if((arriba == -1 && abajo == -1 && derecha == -1)
           || (arriba == -1 && abajo == -1 && izquierda == -1)
           || (arriba == -1 && izquierda == -1 && derecha == -1)
           || (abajo == -1 && izquierda == -1 && derecha == -1))
            return false;
    }
    
    // Por último, devolvemos verdadero si la posición actual es 1 y ninguna de las anteriores condiciones se cumple.
    return lab[currY][currX] == 1;
}


/*
 * Recibe un entero "max" y devuelve otro entero aleatorio desde 0 hasta max.
 */
int UtilLaberinto::getRandom(int max){
    
    /*
     Estas tres líneas son de stack overflor, de la siguiente pregunta:
     http://stackoverflow.com/questions/7560114/random-number-c-in-some-range
     If you wonder "what the hack is mt19937 type?!" - A Mersenne Twister pseudo-random generator of 32-bit numbers 
     with a state size of 19937 bits. It is a "wrapper" for the "mersenne_twister_engine" template 
     (cplusplus.com/reference/random/mersenne_twister_engine) with pre-set params.
     */
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(0, max); // define the range
    
    return distr(eng);
}

/*
 * Recibe un entero "max" y devuelve otro entero aleatorio desde 0 hasta max.
 */
int UtilLaberinto::getRandomRango(int n, int max){
    
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(n, max); // define the range
    
    return distr(eng);
}

int UtilLaberinto::getRandomImparRango(int n, int N){
    
    int r = UtilLaberinto::getRandomRango(n, N);
    while(r<=0
          || r >= N-1
          || r % 2 == 0)
        r = UtilLaberinto::getRandomRango(n, N);
    return r;
}

int UtilLaberinto::getRandomImpar(int N){
    
    int r = UtilLaberinto::getRandom(N);
    while(r<=0
          || r >= N-1
          || r % 2 == 0)
        r = UtilLaberinto::getRandom(N);
    return r;
}

int UtilLaberinto::getRandomPar(int N){
    
    int r = UtilLaberinto::getRandom(N);
    while(r<=0
          || r >= N-1
          || r % 2 != 0)
        r = UtilLaberinto::getRandom(N);
    return r;
}
