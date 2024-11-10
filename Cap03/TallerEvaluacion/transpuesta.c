/****************************************************************
        Pontificia Universidad Javeriana
    Autor: Juan Diego Muñoz Angulo, David Roa Neisa,
            Jorge Humberto Sierra Laiton, Michelle Gabriela Cruz Pino,
            Sofia Carolina Mantilla Vega
    Fecha: 13 Noviembre 2024
    Materia: Sistemas Operativos
    Tema: Taller de Evaluación de Rendimiento
    Fichero:uente de multiplicación de matrices NxN por hilos.
    Objetivo: Evaluar el tiempo de ejecución del 
              algoritmo clásico de multiplicación de matrices.
              Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3) // Definición del tamaño de memoria compartida para matrices

// Variables globales para mutex y matrices en memoria compartida
pthread_mutex_t MM_mutex;
static double MEM_CHUNK[DATA_SIZE];
double *mA, *mB, *mC;

// Estructura para almacenar los parámetros de cada hilo
struct parametros {
    int nH;  // Número total de hilos
    int idH; // ID del hilo
    int N;   // Tamaño de la matriz
};

// Variables para medir el tiempo de ejecución
struct timeval start, stop;

// Función para llenar las matrices con valores iniciales
void llenar_matriz(int SZ) { 
    srand48(time(NULL));
    for (int i = 0; i < SZ*SZ; i++) {
        mA[i] = 1.1 * i; // Valor para la matriz A
        mB[i] = 2.2 * i; // Valor para la matriz B
        mC[i] = 0;       // Inicialización de la matriz resultado
    }   
}

// Función para imprimir matrices (para tamaños pequeños)
void print_matrix(int sz, double *matriz) {
    if (sz < 12) { // Se imprime solo si el tamaño es pequeño
        for (int i = 0; i < sz * sz; i++) {
            if (i % sz == 0) printf("\n");
            printf(" %.3f ", matriz[i]);
        }   
        printf("\n>-------------------->\n");
    }
}

// Función para inicializar el temporizador
void inicial_tiempo() {
    gettimeofday(&start, NULL);
}

// Función para calcular y mostrar el tiempo de ejecución
void final_tiempo() {
    gettimeofday(&stop, NULL);
    stop.tv_sec -= start.tv_sec;
    printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec));
}

// Función ejecutada por cada hilo para multiplicar una sección de la matriz
void *mult_thread(void *variables) {
    struct parametros *data = (struct parametros *)variables;
    
    int idH = data->idH;
    int nH  = data->nH;
    int N   = data->N;
    int ini = (N / nH) * idH;
    int fin = (N / nH) * (idH + 1);

    for (int i = ini; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            double *pA, *pB, sumaTemp = 0.0;
            pA = mA + (i * N); 
            pB = mB + (j * N);
            for (int k = 0; k < N; k++, pA++, pB++) {
                sumaTemp += (*pA * *pB);
            }
            mC[i * N + j] = sumaTemp;
        }
    }

    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);
    pthread_exit(NULL);
}

// Función principal
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        return -1;  
    }
    int SZ = atoi(argv[1]);        // Tamaño de la matriz
    int n_threads = atoi(argv[2]); // Número de hilos

    pthread_t p[n_threads];
    pthread_attr_t atrMM;

    // Inicialización de matrices en memoria compartida
    mA = MEM_CHUNK;
    mB = mA + SZ * SZ;
    mC = mB + SZ * SZ;

    // Llenado de matrices y cálculo de tiempo de ejecución
    llenar_matriz(SZ);
    print_matrix(SZ, mA);
    print_matrix(SZ, mB);

    inicial_tiempo();
    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Creación de hilos para multiplicación de matrices
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *)malloc(sizeof(struct parametros)); 
        datos->idH = j;
        datos->nH  = n_threads;
        datos->N   = SZ;
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
    }

    // Espera a que finalicen todos los hilos
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);
    final_tiempo();
    
    // Impresión de la matriz resultado y destrucción de recursos
    print_matrix(SZ, mC);

    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    pthread_exit(NULL);
}
