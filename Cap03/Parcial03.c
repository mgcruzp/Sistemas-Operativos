/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 07-11-24
 * Tema: Parcial tercer corte
         - Posic Threads
 ***********************************************************************/

// LIbrerias usadas en el codigo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// variable global 
int turno = 0;  // este seria como el primer hijo a ejecutar pero sirve mas como turno para ir comparando mas abajito e ir mirando el hulo

// Mutex 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Funcion de contar que la va a ejectitar cada uno de los hilos
void *contar(void *arg) {
    int hilo_id = *(int*)arg;

    // Bucle para esperar su turno
    while (1) {
        pthread_mutex_lock(&mutex);  // mutex para acceder a turno

        if (turno == hilo_id - 1) { 
            printf("Hilo %d iniciado\n", hilo_id);

            // Bucle que cuenta hasta 300 como se pidio en el enunciado
            for (int i = 0; i < 300; i++) {
                usleep(5000); // 5 milisegundos de espera para simular trabajo
            }

            printf("Hilo %d finalizado\n", hilo_id);
            turno++;  // Actualizar el turno para el siguiente hilo
            pthread_mutex_unlock(&mutex);  // Liberar el mutex
            break;
        }

        pthread_mutex_unlock(&mutex);  // Liberar el mutex si no es su turno
        usleep(1000);
    }

    return NULL;
}


int main() {
    pthread_t hilos[5];  // aca se almacenan los hilos
    int ids[5] = {1, 2, 3, 4, 5};  /// aqui estan los ids de los mismos hilos de arribita

    // se crean los 5 hilos que se piden en el anuncaido
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&hilos[i], NULL, contar, &ids[i]) != 0) {
            printf("Error al crear el hilo\n");
            return 1;
        }
    }

    // Esperar que todos los hilos terminen
    for (int i = 0; i < 5; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}

