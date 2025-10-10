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
        int Anti_Warning = scanf("%d", &n);//amigadelarturo

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

    pd->Moral = 20;

    int suerte;


    pid_t pid1 = fork();

    if (pid1 < 0){

        cout<< "error al crear el proceso Agua"; 
        return 1;
    }
    
    if (pid1 == 0){
        
        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

        for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Agua(suerte, pd , i);             
                  
            }

        shmdt(pd);
        _exit(0);    

        }

    pid_t pid2 = fork();

     if (pid2 < 0){

        cout<< "error al crear el proceso Alimentos"; 
        return 1;
    }

    if (pid2 == 0){
   
        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

        for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Alimentos(suerte, pd , i);             
                  
            }

        shmdt(pd);
        _exit(0);    

    }
    
    
    pid_t pid3 = fork();

    if (pid3 < 0){

        cout<< "error al crear el proceso Refugio"; 
        return 1;
    }
    
    if (pid3 == 0){

        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

        for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Refugio(suerte, pd , i);             
                  
            }

        shmdt(pd);
        _exit(0);    

        }
    


    pid_t pid4 = fork();

    if (pid4 < 0){

        cout<< "error al crear el proceso Señales"; 
        return 1;
    }

    if (pid4 ==0){   
    
        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

         for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Senales(suerte, pd , i);             
                  
            }

        shmdt(pd);
        _exit(0); 
    }

    int status; //necesario para esperar
    waitpid(pid1, &status , 0);
    waitpid(pid2, &status , 0);
    waitpid(pid3, &status , 0);
    waitpid(pid4, &status , 0);

    for (int i = 0; i < n; i++){
       
        cout << "Dia: " << i+1 << endl;
        cout << "La moral es: " <<pd[i].Moral << endl; // actualiza la moral << endl<< endl;

        cout<< "Se recolecto: " << pd[i].Recoleccion[0][1] << " de agua"<< endl;
        cout<< "estado: " << pd[i].Recoleccion[0][0] << endl<< endl;

        cout<< "\nSe recolecto: " << pd[i].Recoleccion[1][1] << " de alimento"<< endl;
        cout<< "estado: " << pd[i].Recoleccion[1][0] << endl<< endl;

        cout<< "Se recolecto: " << pd[i].Recoleccion[2][1] << " de refugio"<< endl;
        cout<< "estado: " << pd[i].Recoleccion[2][0] << endl ;

        cout<< "\nSe recolecto: " << pd[i].Recoleccion[3][1] << " de señales"<< endl;
        cout<< "estado: " << pd[i].Recoleccion[3][0] << endl;

        cout <<"--------------------------------------------------------" << endl << endl;
    }

    shmdt(pd);
    shmctl(shmid, IPC_RMID, NULL); // termina todo, sino no te elegir una cantidad de iteraciones mayor a la que elejiste la primera vez (ya me paso)

    return 0;
}
