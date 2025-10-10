#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cmath>

#include "definicion.hpp"

int moral(int estado, int MoralActual){ 
    if (estado == 0){
        MoralActual = MoralActual - 10;
    }

    else if (estado == 1){
        MoralActual = MoralActual + 10;
    }
    
    else if (estado == 2){
        MoralActual = MoralActual + 20;
    }
    
    if (MoralActual > 100){
        MoralActual = 100;
    }
    else if (MoralActual < 0){
        MoralActual = 0;
    }
    
    return MoralActual;
    
}