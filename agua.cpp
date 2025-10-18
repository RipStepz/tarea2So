#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cmath>

#include "definicion.hpp"

using namespace std;

void Agua(int prob_exito, Inventario* pd, int indice_ronda, int pid){
    
    int recoleccion = 8;
    int Exito[2]; //pos 0 es la probabilidad, pos 1 es el caso
    exito(prob_exito, Exito);

    float ajuste = Exito[0] / 100.0f; // el f es para obligar a que sea flotante la division y no doble
    int Recurso = lround(ajuste * recoleccion);

    if (Recurso == 8 ){ // ya que todos los minimos son divisibles x2 decidimos que el extra del minimo sera la mitad del minimo, en este caso sera 4
        int yapa = rand() % 5;  
        Recurso = Recurso + yapa;
    }

    int PonderadorMoral = moral(Exito[1], pd->Moral);
    
    pd[indice_ronda].Recoleccion[0][0] =  Exito[1]; // guardo el estado 0,1,2
    pd[indice_ronda].Recoleccion[0][1] =  Recurso; // ctd de material recolectado
    pd[indice_ronda].Moral = PonderadorMoral; // actualiza la moral
    pd[indice_ronda].pid[0][0] = pid;

}