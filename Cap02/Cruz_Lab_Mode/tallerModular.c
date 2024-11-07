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

#include "libreriaLab.h"

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
