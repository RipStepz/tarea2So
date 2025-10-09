#ifndef DEFINICION_HPP
#define DEFINICION_HPP
#include <stdio.h>
using namespace std;


struct Inventario{
    int Recoleccion[4][2];
    /*
    Cada fila representa los recursos recolectados:
    pos 0: Agua
    pos 1: Alimentos 
    pos 2: Refugio
    pos 3: Señales 

    Cada columna:
    [x][0] = estado (0,1,2) codificados como 0 fracaso, 1 exito parcial, 2 exito
    [x][1] = ctd materiales recolectado
    */
};

void Agua(int prob_exito, Inventario* pd, int indice_ronda);
void Alimentos (int prob_exito, Inventario* pd, int indice_ronda);
void exito(int prob_exito, int array_retorno[]);




#endif