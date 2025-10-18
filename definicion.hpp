#ifndef DEFINICION_HPP
#define DEFINICION_HPP
#include <stdio.h>
#include <sys/types.h>
using namespace std;


struct Inventario{
    int Recoleccion[4][2];
    int Moral;
    int pid[4][1];
    /*
    Cada fila representa los recursos recolectados:
    pos 0: Agua
    pos 1: Alimentos 
    pos 2: Refugio
    pos 3: Señales 

    Cada columna:
    [x][0] = estado (0,1,2) codificados como 0 fracaso, 1 exito parcial, 2 exito
    [x][1] = ctd materiales recolectado

    Moral, es solo una variable

    para obtener el pid
    pos 0: Agua
    pos 1: Alimentos 
    pos 2: Refugio
    pos 3: Señales 

    [x][0] = pid de la pos x

    */
};

//procesos
void Agua(int prob_exito, Inventario* pd, int indice_ronda , int pid);
void Alimentos (int prob_exito, Inventario* pd, int indice_ronda, int pid);
void Refugio (int prob_exito, Inventario* pd, int indice_ronda, int pid);
void Senales (int prob_exito, Inventario* pd, int indice_ronda, int pid);

//funciones auxiliares
void exito(int prob_exito, int array_retorno[]);
int moral(int estado, int MoralActual);

#endif