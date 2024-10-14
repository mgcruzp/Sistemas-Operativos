/**************************************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 14-10-24
 * Tema: Solucion taller
 
         - Grand hijo: calcula la suma A total del arreglo del fichero 00
         - Segundo hijo: calcula la summa B total del arreglo del fichero 01
         - Primer hijo: calcula la suma total desde los dos arreglos
         - Padre: recibe los calculos desde los 3 procesos
         
 **************************************************************************************/

/*Librerias usadas en el porgrama*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Funciones*/


/*Funcion: Lectura de arreglos de enteros*/
int* leerArreglo(const char* nombreArchivo, int n) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo\n");
        perror("-------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }

    int* arreglo = (int*)malloc(n * sizeof(int));
    if (arreglo == NULL) {
        perror("Error al asignar memoria");
        perror("-------------------------------------------------------\n");
        fclose(archivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(archivo, "%d", &arreglo[i]) != 1) {
            perror("Error al leer del archivo");
            perror("-------------------------------------------------------\n");
            free(arreglo);
            fclose(archivo);
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
    return arreglo;
}

/*Funcion: Sumar arreglos*/
int sumarArreglo(int* arreglo, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i];
    }
    return suma;
}


int main(int argc, char* argv[]) {
    printf("\n"); 
    printf("-------------------------------------------------------\n"); 
    printf("Bienvenido al programa de consultoria\n");
    printf("-------------------------------------------------------\n");
    printf("\n"); 
    
    /*Este error sale si se envia un num diferente de 5 parametros porque el programa recibe exactemente 5:
      El ejecutable, la cantidad de elementos del fichero, el fichero que contiene el arreglo de enteros, 
      cantidad de elementos del fichero y el ultimo fchero que contiene el arreflo de enteros */
    if (argc != 5) {
        perror("Error, mas de 5 parametros enviados. \n");
        perror("-------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }

    int N1 = atoi(argv[1]);
    const char* archivo1 = argv[2];
    int N2 = atoi(argv[3]);
    const char* archivo2 = argv[4];

    int* arreglo1 = leerArreglo(archivo1, N1);
    int* arreglo2 = leerArreglo(archivo2, N2);

    int pipe1[2], pipe2[2], pipe3[2];
    
    /*Sale este error para verificar si el pipe pudo haber sido creado correctamente*/
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("Error al crear pipesn+\n");
        perror("-------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
    

    pid_t pid1 = fork();
    /*Sale este error al no poder crear el fork hacia el hijo correctamente*/
    if (pid1 == -1) {
        perror("Error al hacer fork para gran hijo\n");
        perror("-------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        /*Gran hijo: no se porque primero imprime el segundo hijo antes del grand hijo pero funciona bien */
        int sumaA = sumarArreglo(arreglo1, N1);
        close(pipe1[0]); 
        write(pipe1[1], &sumaA, sizeof(sumaA));
        printf("Gran Hijo: [%d] Suma archivo 1 = %d\n", getpid(), sumaA);
        printf("-------------------------------------------------------\n");
        printf("\n"); 
        close(pipe1[1]); 
        exit(EXIT_SUCCESS);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Error al hacer fork para segundo hijo\n");
        perror("-------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        /*Segundo hijo*/
        int sumaB = sumarArreglo(arreglo2, N2);
        close(pipe2[0]);
        write(pipe2[1], &sumaB, sizeof(sumaB));
        printf("Segundo Hijo: [%d] Suma archivo 2 = %d\n", getpid(), sumaB);
        printf("-------------------------------------------------------\n");
        printf("\n"); 
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }

    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("Error al hacer fork para primer hijo\n");
        perror("-------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
    if (pid3 == 0) {
        /*Primer hijo*/
        int sumaA, sumaB;
        close(pipe1[1]);
        read(pipe1[0], &sumaA, sizeof(sumaA));
        close(pipe1[0]); 

        close(pipe2[1]);
        read(pipe2[0], &sumaB, sizeof(sumaB));
        close(pipe2[0]); 

        int total = sumaA + sumaB;
        close(pipe3[0]);
        write(pipe3[1], &total, sizeof(total));
        printf("Primer Hijo: [%d] Suma total = %d\n", getpid(), total);
        printf("-------------------------------------------------------\n");
        printf("\n"); 
        close(pipe3[1]); // Cerrar escritura
        exit(EXIT_SUCCESS);
    }

 
    close(pipe3[1]);
    int total;
    read(pipe3[0], &total, sizeof(total));
    printf("Padre: [%d] Suma total = %d\n", getpid(), total);
    printf("-------------------------------------------------------\n");
    printf("\n"); 
    close(pipe3[0]); 

    wait(NULL);
    wait(NULL);
    wait(NULL);

    /*Liberar memoria como aprendimos en clase que es importante y la vez pasada olvide ponerlo :)*/
    free(arreglo1);
    free(arreglo2);

    return 0;
}

