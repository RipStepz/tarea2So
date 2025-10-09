#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include "definicion.hpp"
using namespace std;



int main(int argc, char const *argv[]){
    
    int fd[2]; // para agua
    int fd_2[2]; // para alimentos
    pipe(fd);
    int suerte;


    pid_t pid1 = fork();

    if (pid1 == 0){ // hijo
        
        suerte = rand() % 101;
        close(fd[0]);
        close(fd_2[0]);
        close(fd_2[1]);

        Agua(suerte, fd);

    }

    pid_t pid2 = fork();

    if (pid2 == 0){ // hijo
         
        suerte = rand() % 101;
        close(fd_2[0]);
        close(fd[0]);
        close(fd[1]);

        Alimentos(suerte, fd_2);

    }
    
    



    return 0;
}
