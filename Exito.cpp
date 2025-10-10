#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include "definicion.hpp"

using namespace std;
/*
defino arbitrariamente;
0 Como Fracaso
1 Como Exito parcial
2 Como exito 

*/ 
void exito(int prob_exito, int ajuste[]){ // pos 0 es la probabilidad, pos 1 es el caso
    
    if (0 <= prob_exito && prob_exito <= 20){ // Fracaso
        ajuste[0] = rand() % 31;
        ajuste[1] = 0;

    }

    else if (20 < prob_exito && prob_exito <= 70){ // Exito parcial
        ajuste[0] = rand() % (80 - 50 + 1) + 50; // gracias a la formula rand() % (max - min + 1) + min hice un intervalor entre 80 y 50
        ajuste[1] = 1;
    }

    else{ // exito
        ajuste[0] = 100;
        ajuste[1] = 2;
    }
    
}