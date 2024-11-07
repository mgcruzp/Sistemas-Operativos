/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 15-08-24
 * Tema: Gestión de memoria
 * Tópico: Multiplicación de matrices 
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*Funcion para imprimir la matriz*/
void imprimirMatriz(int *matriz, int n) {
  /*menor a 6 como se indico en clase*/
    if (n < 6) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", *(matriz + i * n + j));
            }
            printf("\n");
        }
        printf("-------------------------\n");
    }
}

int main(int argc, char* argv[]) {
  
  /*Verfica que se haya pasado el tam de la matriz*/
    if (argc < 2) {
        printf("\nArgumentos válidos: $ejecutable tamañoMatriz\n");
        exit(0);
    }
    
    /*atoi lo convierte a entero*/
    int n = atoi(argv[1]); 
    int size = n * n;
    
    /*Memoria dinamica asignada para las matrices como se aprendio en clase*/
    int *mA = (int *)malloc(size * sizeof(int));
    int *mB = (int *)malloc(size * sizeof(int));
    int *mC = (int *)malloc(size * sizeof(int));
    
    /*Verifica si fue asignada*/
    if (mA == NULL || mB == NULL || mC == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    /*Inicializaccion de la matriz
    con los valores usados en clase*/
    for (int i = 0; i < size; i++) {
        mA[i] = 1; 
        mB[i] = 2;
        mC[i] = 0;
    }
    
    /*imprime las matrices A y B*/
    imprimirMatriz(mA, n);
    imprimirMatriz(mB, n);

    /*Multiplicacion de matrices*/
    for (int i = 0; i < size; i++) {
        int fila = i / n;  
        int columna = i % n; 
        for (int k = 0; k < n; k++) {
            mC[i] += mA[fila * n + k] * mB[k * n + columna];
        }
    }
    
    /* imprime la matriz c (mA*mB=mC)*/
    imprimirMatriz(mC, n);

    /*Libera la memoria asignada*/
    free(mA);
    free(mB);
    free(mC);

    printf("... saliendo del programa\n");
    return 0;
}
