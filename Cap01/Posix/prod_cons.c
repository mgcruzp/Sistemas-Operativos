/***********************************************************************
 * Autor: Gabriela Cruz
 * Materia: Sistemas Operativos
 * Fecha: 24-10-2024
 * Tema: Posix
 * Descripcion: Este programa implementa el problema del productor-consumidor
 *              utilizando hilos de POSIX. El productor incrementa el contador
 *              y el consumidor lo decrementa, ambos coordinados mediante mutex
 *              y variables de condicion para evitar condiciones de carrera.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // Para usar sleep()

int counter = 0;  // Variable compartida que cuenta los elementos producidos
int max = 4;      // Numero maximo de hilos productores y consumidores

// Definicion de mutex y variables de condicion
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Protege el acceso al contador
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;   // Protege la condicion del productor
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;   // Protege la condicion del consumidor
pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER;     // Variable de condicion del productor
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER;     // Variable de condicion del consumidor

// Funcion del hilo productor
void *productor(void *arg) {
    while(1) {
        // Bloquea el acceso al productor hasta que haya espacio disponible para producir
        pthread_mutex_lock(&condp_mutex);
        while(counter >= 10) {
            pthread_cond_wait(&condVarProd, &condp_mutex);  // Espera si el contador esta lleno
        }
        pthread_mutex_unlock(&condp_mutex);

        // Bloquea el acceso al contador para incrementar su valor
        pthread_mutex_lock(&counter_mutex);
        counter++;  // Incrementa el contador
        pthread_cond_signal(&condVarCons);  // Notifica a los consumidores que hay un nuevo item
        printf("Soy productor %d valor contador = %d\n", (int)pthread_self(), counter);
        pthread_mutex_unlock(&condp_mutex);  // Libera el mutex del productor
        pthread_mutex_unlock(&counter_mutex);  // Libera el mutex del contador

        // Pausa si el contador alcanza el valor de 5
        if(counter == 5) {
            sleep(1);
        }
    }
    return NULL;
}

// Funcion del hilo consumidor
void *consumidor(void *arg) {
    while(1) {
        sleep(1);  // Simula tiempo de espera antes de consumir

        // Bloquea el acceso al consumidor hasta que haya items para consumir
        pthread_mutex_lock(&condc_mutex);
        while(counter <= 0) {
            pthread_cond_signal(&condVarProd);  // Notifica a los productores que pueden producir
            pthread_cond_wait(&condVarCons, &condc_mutex);  // Espera si el contador esta vacio
        }
        pthread_mutex_unlock(&condc_mutex);

        // Bloquea el acceso al contador para decrementarlo
        pthread_mutex_lock(&counter_mutex);
        if(counter > 0) {
            printf("Soy consumidor %d valor contador = %d\n", (int)pthread_self(), counter);
            counter--;  // Decrementa el contador
            pthread_cond_signal(&condVarProd);  // Notifica a los productores que hay espacio
        }
        pthread_mutex_unlock(&counter_mutex);  // Libera el mutex del contador
        pthread_mutex_unlock(&condc_mutex);  // Libera el mutex del consumidor
    }
    return NULL;
}

int main() {
    pthread_t proHilo[max], conHilo[max];  // Arrays para almacenar los identificadores de hilos
    int i;

    // Crea hilos productores y consumidores
    for(i = 0; i < 5; i++) {
        pthread_create(&proHilo[i], NULL, &productor, NULL);  // Crea un hilo productor
        pthread_create(&conHilo[i], NULL, &consumidor, NULL);  // Crea un hilo consumidor
    }

    // Espera a que los hilos finalicen
    for(i = 0; i < 5; i++) {
        pthread_join(proHilo[i], NULL);  // Espera a que termine el hilo productor
        pthread_join(conHilo[i], NULL);  // Espera a que termine el hilo consumidor
    }

    return 0;
}
