#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cmath>

#include "definicion.hpp"

void Alimentos (int prob_exito, Inventario* pd, int indice_ronda){

    int recoleccion = 12;
    int Exito[2]; //pos 0 es la probabilidad, pos 1 es el caso
    exito(prob_exito, Exito);

    float ajuste = Exito[0] / 100.0f; // el f es para obligar a que sea flotante la division y no doble
    int Recurso = lround(ajuste * recoleccion);

    if (Recurso == 12 ){ // ya que todos los minimos son divisibles x2 decidimos que el extra del minimo sera la mitad del minimo, en este caso sera 6
        int yapa = rand() % 7;  
        Recurso = Recurso + yapa;
    }
    
    pd[indice_ronda].Recoleccion[0][0] =  Exito[1]; // guardo el estado 0,1,2
    pd[indice_ronda].Recoleccion[0][1] =  Recurso; // ctd de material recolectado
}