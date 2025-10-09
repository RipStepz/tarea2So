#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cmath>

#include "definicion.hpp"

using namespace std;

void Agua(int prob_exito, int fd[]){
    
    int recoleccion = 8;
    int Exito[2];
    exito(prob_exito, Exito);

    float ajuste = Exito[0] / 100.0f; // el f es para obligar a que sea flotante la division y no doble
    int retorno = lround(ajuste * recoleccion);

    if (retorno == 8 ){ // ya que todos los minimos son divisibles x2 decidimos que el extra del minimo sera la mitad del minimo, en este caso sera 4
        int yapa = rand() % 5;  
        retorno = retorno + yapa;
    }

    int array_retorno[2];
    array_retorno[0] = retorno;
    array_retorno[1] = Exito[1];

    int peso = sizeof(array_retorno);
    

    close(fd[0]);

    if (write(fd[1], array_retorno, peso) < 0){
        cout << "Hubo un error al leer desde la funcion agua" << endl;
        return;
    }

    close(fd[1]);

}