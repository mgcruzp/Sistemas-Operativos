/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 29-08-24
 * Tema: Laboratorio compilacion modular
 *   - Fundacion del codigo
 *   - Modularizacio del codigo
 *   - Creacion de fichero de automatizacion de compilacion
 ***********************************************************************
      INTERFAZ DE LIBRERIA DE FUNCIONES: MENU DE FUNCIONES
 ***********************************************************************/

#ifndef _LIBRERIALAB_H
#define _LIBRERIALAB_H

#define CAPACIDAD_INICIAL 4

/*Creación Estructura de Datos para el Vector*/
typedef struct vectorDinamico{
        int capacidad;
        int totalElementos;
        void **elementos;
} vectorDinamico;

/*Incializacion de los valores del vector, casting y reserva de memoria*/
void vectorInicio(vectorDinamico *V);

/*Retorna el total de elementos*/
int totalVector(vectorDinamico *V);

/*Redimensiona el vector*/
static void resizeVector(vectorDinamico *V, int capacidad);

/*Agregar elementos al vector*/
void addVector(vectorDinamico *V, void *elemento);

/*Liberacion de memoria dinamica*/
void freeVector(vectorDinamico *V);

/*Obtencion del elemento segun indice*/
void *getVector(vectorDinamico *V, int indice);

/*Ubicar un elemeneto en un indice*/
void setVector(vectorDinamico *V, int indice, void *elemento);

/*Borrar elemento segun indice, redimension*/
void borrarVector(vectorDinamico *V, int indice);
   
#endif
