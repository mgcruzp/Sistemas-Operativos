/****************************************************************
        Pontificia Universidad Javeriana
    Autor: Juan Diego Muñoz Angulo, David Roa Neisa,
            Jorge Humberto Sierra Laiton, Michelle Gabriela Cruz Pino,
            Sofia Carolina Mantilla Vega
    Fecha: 13 Noviembre 2024
    Materia: Sistemas Operativos
    Tema: Taller de Evaluación de Rendimiento
    Fichero:fuente de multiplicación de matrices NxN por hilos.
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

#define DATA_SIZE (1024*1024*64*3)  // Tamaño del arreglo de memoria compartida

pthread_mutex_t MM_mutex;  // Mutex para sincronización
static double MEM_CHUNK[DATA_SIZE];  // Bloque de memoria para almacenar las matrices
double *mA, *mB, *mC;  // Punteros a matrices A, B, y C

// Estructura para pasar parámetros a los hilos
struct parametros {
	int nH;   // Número total de hilos
	int idH;  // ID del hilo
	int N;    // Tamaño de la matriz (NxN)
};

struct timeval start, stop;  // Variables para medir el tiempo de ejecución

// Función para llenar las matrices A y B con valores iniciales y matriz C con ceros
void llenar_matriz(int SZ) { 
	srand48(time(NULL));  // Inicializar generador de números pseudoaleatorios
	for(int i = 0; i < SZ * SZ; i++) {
		mA[i] = 1.1 * i;  // Asignar valores a la matriz A
		mB[i] = 2.2 * i;  // Asignar valores a la matriz B
		mC[i] = 0;        // Inicializar la matriz C en cero
	}	
}

// Función para imprimir la matriz si el tamaño es menor a 12x12
void print_matrix(int sz, double *matriz) {
	if(sz < 12) {  // Limitar impresión para matrices pequeñas
    	for(int i = 0; i < sz * sz; i++) {
			if(i % sz == 0) printf("\n");
            printf(" %.3f ", matriz[i]);
		}	
    	printf("\n>-------------------->\n");
	}
}

// Funciones para medir el tiempo de ejecución
void inicial_tiempo() {
	gettimeofday(&start, NULL);  // Registrar el tiempo de inicio
}

void final_tiempo() {
	gettimeofday(&stop, NULL);  // Registrar el tiempo de fin
	stop.tv_sec -= start.tv_sec;  // Calcular la diferencia en microsegundos
	printf("\n:-> %9.0f µs\n", (double) (stop.tv_sec * 1000000 + stop.tv_usec));
}

// Función ejecutada por cada hilo para calcular una sección de la matriz resultante
void *mult_thread(void *variables) {
	struct parametros *data = (struct parametros *)variables;
	
	int idH = data->idH;
	int nH  = data->nH;
	int N   = data->N;
	int ini = (N / nH) * idH;        // Índice inicial de la partición de filas
	int fin = (N / nH) * (idH + 1);  // Índice final de la partición de filas

    for (int i = ini; i < fin; i++) {  // Recorrer filas de la matriz A
        for (int j = 0; j < N; j++) {  // Recorrer columnas de la matriz B
			double *pA, *pB, sumaTemp = 0.0;
			pA = mA + (i * N); 
			pB = mB + j;
            for (int k = 0; k < N; k++, pA++, pB += N) {  // Producto escalar
				sumaTemp += (*pA * *pB);
			}
			mC[i * N + j] = sumaTemp;  // Asignar resultado en la matriz C
		}
	}

	pthread_mutex_lock(&MM_mutex);  // Sección crítica para sincronización
	pthread_mutex_unlock(&MM_mutex);  
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	// Validar argumentos de entrada
	if (argc < 2) {
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;	
	}
    int SZ = atoi(argv[1]);      // Tamaño de la matriz
    int n_threads = atoi(argv[2]);  // Número de hilos

    pthread_t p[n_threads];      // Arreglo de hilos
    pthread_attr_t atrMM;        // Atributos de los hilos

	mA = MEM_CHUNK;              // Asignar punteros a bloques de memoria
	mB = mA + SZ * SZ;
	mC = mB + SZ * SZ;

	llenar_matriz(SZ);           // Llenar las matrices con valores iniciales
	print_matrix(SZ, mA);        // Imprimir matriz A
	print_matrix(SZ, mB);        // Imprimir matriz B

	inicial_tiempo();            // Iniciar medición de tiempo
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Crear los hilos para la multiplicación de matrices
    for (int j = 0; j < n_threads; j++) {
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = SZ;
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
	}

    // Esperar que todos los hilos terminen su ejecución
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);
	final_tiempo();  // Finalizar la medición de tiempo
	
	print_matrix(SZ, mC);  // Imprimir matriz resultante

	pthread_attr_destroy(&atrMM);  // Liberar recursos
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit(NULL);
}
