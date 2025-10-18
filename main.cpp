#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>   
#include <sys/wait.h> 
#include <sys/shm.h>
#include <cmath>


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

    pd->Moral = 100;

    int suerte;


    pid_t pid1 = fork();

    if (pid1 < 0){

        cout<< "error al crear el proceso Agua pid: "; 
        
        return 1;
    }
    
    if (pid1 == 0){
        
        pid_t pid1_hijo = getpid();

        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

        for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            
            Agua(suerte, pd , i , (int)pid1_hijo);             
                  
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

        pid_t pid2_hijo = getpid();

        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

        for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Alimentos(suerte, pd , i , (int)pid2_hijo);             
                  
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

        pid_t pid3_hijo = getpid();

        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

        for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Refugio(suerte, pd , i , (int)pid3_hijo);             
                  
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
    
        pid_t pid4_hijo = getpid();

        srand((unsigned)time(nullptr) ^ ((unsigned)getpid() << 16)); // para que no todos los randoms sean iguales

         for (int i = 0; i < n; i++){

            suerte = rand() % 101;
            Senales(suerte, pd , i, (int)pid4_hijo);             
                  
            }

        shmdt(pd);
        _exit(0); 
    }

    int status; //necesario para esperar
    waitpid(pid1, &status , 0);
    waitpid(pid2, &status , 0);
    waitpid(pid3, &status , 0);
    waitpid(pid4, &status , 0);

    int ContadorSeñales = 0;

    for (int i = 0; i < n; i++){
       
        
        if (pd[i].Moral == 0){
            cout << "La moral del equipo llego a 0, perdiste"<<endl;
            return 0;
        }

        if (pd[i].Recoleccion[3][0] == 2){
            ContadorSeñales += 1 ;
        }
        else{
            ContadorSeñales = 0;
        }
        getchar();
        cout << "=== DÍA " << i+1 << " DE SUPERVIVENCIA ==="<< endl;
        cout << "Iniciando equipos de recolección... " << endl;
        
        cout<< "[EQUIPO AGUA - PID: "<< pd[i].pid[0][0] << "] Explorando fuentes de agua..." << endl;
        cout<< "[EQUIPO ALIMENTOS - PID: "<< pd[i].pid[1][0] << "] Explorando territorios para cazar..." << endl;
        cout<< "[EQUIPO CONSTRUCCION - PID: "<< pd[i].pid[2][0] << "] Buscando materiales de construcción" << endl;
        cout<< "[EQUIPO SEÑALES - PID: "<< pd[i].pid[3][0] << "] Recolectando combustible seco..." << endl<<endl;

        cout<< "[EQUIPO AGUA - PID: "<< pd[i].pid[0][0] << "] Recolectando agua del arroyo encontrado..." << endl;
        cout<< "[EQUIPO ALIMENTOS - PID: "<< pd[i].pid[1][0] << "] Intentando pescar en la laguna..." << endl;
        cout<< "[EQUIPO CONSTRUCCION - PID: "<< pd[i].pid[2][0] << "] Cortando ramas útiles..." << endl;
        cout<< "[EQUIPO SEÑALES - PID: "<< pd[i].pid[3][0] << "] Manteniendo fogata de señales..." << endl<<endl;

        cout<< "[EQUIPO AGUA - PID: "<< pd[i].pid[0][0] << "] Purificando agua recolectada..." << endl;
        cout<< "[EQUIPO ALIMENTOS - PID: "<< pd[i].pid[1][0] << "] Capturado pez pequeño!!! Preparando..." << endl;
        cout<< "[EQUIPO CONSTRUCCION - PID: "<< pd[i].pid[2][0] << "] Construyendo refugio..." << endl;
        cout<< "[EQUIPO SEÑALES - PID: "<< pd[i].pid[3][0] << "] Creando señales de humo..." << endl<<endl;

        cout<< "REPORTES FINALES: " << endl;
        
        cout << "- Equipo Agua completó ciclo: " << pd[i].Recoleccion[0][1] << " unidades de agua obtenidas" << endl;
        cout << "- Equipo Alimentos completó ciclo: " << pd[i].Recoleccion[1][1] << " unidades de alimento obtenidas" << endl;
        cout << "- Equipo Construcción completó ciclo: " << pd[i].Recoleccion[2][1] << " unidades de material obtenidas" << endl;
        cout << "- Equipo Señales completó ciclo: " << pd[i].Recoleccion[3][1] << " unidades de señal obtenidas" << endl<<endl;

        cout<< "RESULTADOS DEL DIA: " << endl;

        if (pd[i].Recoleccion[0][0] == 0){
            cout << "Estado de recolección equipo agua: Fracaso " << endl;
        }
        else if(pd[i].Recoleccion[0][0] == 1){
            cout << "Estado de recolección equipo agua: Exito parcial " << endl;
        }
        else if(pd[i].Recoleccion[1][0] == 2){
            cout << "Estado de recolección equipo agua: Exito " << endl;
        }

        if (pd[i].Recoleccion[1][0] == 0){
            cout << "Estado de recolección equipo alimentos: Fracaso " << endl;
        }
        else if(pd[i].Recoleccion[1][0] == 1){
            cout << "Estado de recolección equipo alimentos: Exito parcial " << endl;
        }
        else if(pd[i].Recoleccion[1][0] == 2){
            cout << "Estado de recolección equipo alimentos: Exito " << endl;
        }

        if (pd[i].Recoleccion[2][0] == 0){
            cout << "Estado de recolección equipo materiales: Fracaso " << endl;
        }
        else if(pd[i].Recoleccion[2][0] == 1){
            cout << "Estado de recolección equipo materiales: Exito parcial " << endl;
        }
        else if(pd[i].Recoleccion[2][0] == 2){
            cout << "Estado de recolección equipo materiales: Exito " << endl;
        }

        if (pd[i].Recoleccion[3][0] == 0){
            cout << "Estado de recolección equipo señales: Fracaso " << endl;
        }
        else if(pd[i].Recoleccion[3][0] == 1){
            cout << "Estado de recolección equipo señales: Exito parcial " << endl;
        }
        else if(pd[i].Recoleccion[3][0] == 2){
            cout << "Estado de recolección equipo señales: Exito " << endl;
        }


        cout << "La moral del grupo es: " <<pd[i].Moral << endl<<endl; // actualiza la moral << endl<< endl;

        cout <<"--------------------------------------------------------" << endl << endl;
        

        if (ContadorSeñales == 10){
            cout << "Has logrado mantener las señales de humo 10 dias seguidos prendidas, has ganado"<<endl;
        }

        
        
    }

    cout << "Se acabaron los dias y no fuiste rescatado, perdiste"<<endl;
    shmdt(pd);
    shmctl(shmid, IPC_RMID, NULL); // termina todo, sino no te elegir una cantidad de iteraciones mayor a la que elejiste la primera vez (ya me paso)

    return 0;
}
