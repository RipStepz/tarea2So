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
    srand(time(nullptr));

    cout << "Ingrese limite de tiempo [10,30]: ";

    bool flag = true;

    while (flag){
        int Anti_Warning = scanf("%d", &n);

        if (Anti_Warning == 0){
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} // limpio el Anti_warning osino quedo pegado pa siempre printenado
            cout << "se ingreso un dato incorrecto, intente nuevamente con un numero entero en el rango [10,30]: ";
        }
        else{
            if (n < 10 || 30 < n){
                cout << "Ingrese limite de tiempo [10,30]: ";
            }
            else{
                flag = 0;
            }
            
        }
    }

    cout << endl;

    
    int shmid = shmget(key,sizeof(estados) * n, IPC_CREAT | 0600); // ocupe 0600 para que solo estos procesos puedan acceder, es mas seguro que 0666, aunque pa este caso da lo mismo la verdad :3 PD: si no funciona prueba cambiar 0666xd
    
    if (shmid == -1){
        cout<< "Error al crear la region de memoria compartida y su identificador del bloque de memoria " << endl;
        return 1;

    }
    

    Inventario* pd = (Inventario*) shmat(shmid, NULL , 0 );

    if (pd == (void*) -1){
        cout << "No se pudo adjuntar el segmento de memoria al inventario";
        return 1;
    }

    int suerte;


    pid_t pid1 = fork();

    if (pid1 == 0){ // agua
        int desvinculacion = shmctl(shmid, IPC_RMID, nullptr); // desvinculo

        suerte = rand() % 101;
        Agua(suerte, pd , 0);

        desvinculacion = shmdt(pd);

        if (desvinculacion == -1){
            cout << "Error al desvincular el proceso del agua de la zona de memoria compartida" << endl;
            return 1;
        }
        else{
            _exit(0);
        }
        
    }

    pid_t pid2 = fork();

    if (pid2 == 0){ // alimento
        int desvinculacion = shmctl(shmid, IPC_RMID, nullptr); // desvinculo

        suerte = rand() % 101;
        Alimentos(suerte, pd , 0);
        
        if (desvinculacion == -1){
            cout << "Error al desvincular el proceso del alimento de la zona de memoria compartida" << endl;
            return 1;
        }
        else{
            _exit(0);
        }

    }

    int status; //necesario para esperar
    waitpid(pid1, &status , 0);
    waitpid(pid2, &status , 0);

    cout<< "Se recolecto: " << pd[0].Recoleccion[0][1] << " de agua"<< endl;
    cout<< "estado: " << pd[0].Recoleccion[0][0] << endl;

    cout<< "\nSe recolecto: " << pd[0].Recoleccion[1][1] << " de alimento"<< endl;
    cout<< "estado: " << pd[0].Recoleccion[1][0] << endl;

    shmctl(shmid, IPC_RMID, NULL); // termina todo, sino no te elegir una cantidad de iteraciones mayor a la que elejiste la primera vez (ya me paso)

    return 0;
}
