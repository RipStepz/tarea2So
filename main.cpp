#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include "definicion.hpp"
using namespace std;



int main(){

    int fd[2]; // para agua
    int fd_2[2]; // para alimentos

    if (pipe(fd) < 0){
        cout << "Hubo un error al crear el pipe del agua" << endl;
        return 0;
    }

    if (pipe(fd_2) < 0){
        cout << "Hubo un error al crear el pipe del alimento" << endl;
        return 0;
    }
    
    
    int suerte;


    pid_t pid1 = fork();

    if (pid1 == 0){ // hijo
        
        srand(time(nullptr));
        suerte = rand() % 101;
        close(fd[0]);
        close(fd_2[0]);
        close(fd_2[1]);

        Agua(suerte, fd);
        _exit(0);  

    }

    pid_t pid2 = fork();

    if (pid2 == 0){ // hijo
        
        srand(time(nullptr));
        suerte = rand() % 101;
        close(fd_2[0]);
        close(fd[0]);
        close(fd[1]);

        Alimentos(suerte, fd_2);
        _exit(0);  

    }
    
    close(fd[1]);
    close(fd_2[1]);

    int resultado_agua[2]; 
    
    if (read(fd[0], resultado_agua, sizeof(resultado_agua)) < 0){
        cout << "Hubo un error desde el main al leer el pipe del agua" << endl;
        return 0;
    }

    int resultado_alimentos[2];
    
    if (read(fd_2[0], resultado_alimentos, sizeof(resultado_alimentos)) < 0){
        cout << "Hubo un error desde el main al leer el pipe del alimento" << endl;
        return 0;
    }
    

    close(fd[0]);
    close(fd_2[0]);

    cout << "Se obtuvo :" << resultado_agua[0] << " de agua" << endl; 
    cout << "caso : " << resultado_agua[1] <<endl << endl;

    
     
    cout << "Se obtuvo :" << resultado_alimentos[0] << " de alimentos" << endl; 
    cout << "caso : " << resultado_alimentos[1] <<endl;



    return 0;
}
