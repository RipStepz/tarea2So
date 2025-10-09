#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>   
#include <sys/wait.h> 
#include <sys/shm.h>

#include "definicion.hpp"
using namespace std;


int main(){

    int key = 67; // porque es un numero chistoso
    int n;
    Inventario estados;

    cout << "Ingrese limite de tiempo [10,30]: ";

    if (scanf("%d", &n) == 0){
        cout << "se ingreso un dato incorrecto, error scanf";
        return 0; 
    }

    else{
        while (n < 10 || 30 < n){
            cout << "Ingrese limite de tiempo [10,30]: ";
            if (scanf("%d", &n) == 0){
                cout << "se ingreso un dato incorrecto, error scanf" << endl; 
                return 0;
            }
        }

        cout << "Valor ingresado correctamente" << endl;
    }
    
    int shmid = shmget(key,sizeof(estados) * n, IPC_CREAT | 0600); // ocupe 0600 para que solo estos procesos puedan acceder, es mas seguro que 0666, aunque pa este caso da lo mismo la verdad :3 PD: si no funciona prueba cambiar 0666xd
    
    if (shmid == -1){
        cout<< "Error al crear la region de memoria compartida y su identificador del bloque de memoria " << endl;
        return 0;

    }
    

    Inventario* pd = (Inventario*) shmat(shmid, NULL , 0 );

    if (pd == (void*) -1){
        cout << "No se pudo adjuntar el segmento de memoria al inventario";
        return 0;
    }
    

    return 0;
}
