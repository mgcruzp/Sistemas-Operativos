/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 29-08-24
 * Tema: Laboratorio compilacion modular
 *   - Fundacion del codigo
 *   - Modularizacio del codigo
 *   - Creacion de fichero de automatizacion de compilacion
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 4

/*Creación Estructura de Datos para el Vector*/
typedef struct vectorDinamico{
        int capacidad;
        int totalElementos;
        void **elementos;
} vectorDinamico;

/*Incializacion de los valores del vector, casting y reserva de memoria*/
void vectorInicio(vectorDinamico *V){
        V->capacidad = CAPACIDAD_INICIAL;
        V->totalElementos = 0;
        V->elementos = malloc(sizeof(void *) * V->capacidad); 
}

/*Retorna el total de elementos*/
int totalVector(vectorDinamico *V){
        return V->totalElementos;
}

/*Redimensiona el vector*/
static void resizeVector(vectorDinamico *V, int capacidad){
        printf("Redimensión: %d a %d \n", V->capacidad, capacidad);

        void **elementos = realloc(V->elementos, sizeof(void *) * capacidad);
        if(elementos){
                V->elementos = elementos;
                V->capacidad = capacidad;
        }
}

/*Agregar elementos al vector*/
void addVector(vectorDinamico *V, void *elemento){
        if(V->capacidad == V->totalElementos)
                resizeVector(V, V->capacidad*2);
        V->elementos[V->totalElementos++] = elemento;
}

/*Liberacion de memoria dinamica*/
void freeVector(vectorDinamico *V){
        free(V->elementos);
}

/*Obtencion del elemento segun indice*/
void *getVector(vectorDinamico *V, int indice){
        if(indice >= 0 && indice < V->totalElementos)
                return V->elementos[indice];
        return NULL;
}

/*Ubicar un elemeneto en un indice*/
void setVector(vectorDinamico *V, int indice, void *elemento){
        if(indice >= 0 && indice < V->totalElementos)
                V->elementos[indice]=elemento;
}

/*Borrar elemento segun indice, redimension*/
void borrarVector(vectorDinamico *V, int indice){
        if(indice < 0 || indice >= V->totalElementos)
                return; 

        V->elementos[indice] = NULL;

        for(int i=indice; i<V->totalElementos-1; i++){
                V->elementos[i] = V->elementos[i+1];
                V->elementos[i+1] = NULL; 
        }
        V->totalElementos--;
        if(V->totalElementos>0 && V->totalElementos == V->capacidad/4)
                resizeVector(V, V->capacidad/2);
}

/*Programa principal*/
int main(){
  
        int i;
  
        vectorDinamico editor;
        vectorInicio(&editor);

        addVector(&editor, "Hola ");
        addVector(&editor, "Profesional ");
        addVector(&editor, "en ");
        addVector(&editor, "Formacion ");
        addVector(&editor, "de ");
        addVector(&editor, "Ingenieria");
  
        printf("\n");

        for (i = 0; i < totalVector(&editor); i++)
        printf("%s", (char *) getVector(&editor, i));
        
        printf("\n");
  
        /*Se borra los 5 elementos del 1 al 5*/
        int a=5;
        while (a>1){
          borrarVector(&editor, a);
          a--;
        }
        
        
        setVector(&editor, 1, "Buenos");
        addVector(&editor, "dias ");
      
        
        
        printf("\n");

        for (i = 0; i < totalVector(&editor); i++)
        printf("%s ", (char *) getVector(&editor, i));
        
        printf("\n");
        freeVector(&editor);
  
        return 0;
}
