/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 25-07-24
 * Tema: Entrada y salida en C
 ***********************************************************************/

#include <stdio.h>
#include <math.h>

 /* Sumar dos valores que entran por teclado */
void sumarEnteros(){
    int a, b;
    printf("-----------------------------------------------------------------------\n");
    printf("Suma de numeros\n");
    printf("Ingrese el primer valor:\n");
    scanf("%d", &a);
    printf("Ingrese el segundo valor:\n");
    scanf("%d", &b);
    int suma = a + b;
    printf("La suma de %d + %d = %d\n\n", a, b, suma);

}

  /* Calcular área de círculo ingresando por teclado el radio */
void areaCirculo(){
  printf("-----------------------------------------------------------------------\n");
    float radio;
  float pi = 3.14159;
    printf("Area de Circulo\n");
    printf("Ingrese el radio del circulo:\n");
    scanf("%f", &radio);
    float areaCirculo = pi * radio * radio; 
    printf("El area del circulo es %f\n\n", areaCirculo);
}

 /* Calcular volumen de esfera ingresando por teclado el radio */
void volumenEsfera(){
   printf("-----------------------------------------------------------------------\n");
    float radio;
    float pi = 3.14159;
    printf("Volumen de Esfera\n");
    printf("Ingrese el radio de la esfera:\n");
    scanf("%f", &radio);
    double volEsfera = (4/3) * pi * pow(radio, 3);
    printf("El volumen de la esfera es %lf\n\n", volEsfera);
}

  /* Calcular volumen de cono ingresando por teclado variables */
void volumenCono(){
  printf("-----------------------------------------------------------------------\n");
    float radio;
    float pi = 3.14159;
    printf("Volumen de Cono\n");
    float altura;
    printf("Ingrese el radio del cono:\n");
    scanf("%f", &radio);
    printf("Ingrese la altura del cono:\n");
    scanf("%f", &altura);
    double volCono = (pi * pow(radio, 2) * altura) / 3;  
    printf("El volumen del cono es %lf\n\n", volCono);
}

    /* Calcular hipotenusa ingresando por teclado variables */
void hipotenusa(){
  printf("-----------------------------------------------------------------------\n");
    printf("Calcular hipotenusa\n");
    float hipoA, hipoB;
    printf("Ingrese el valor del cateto opuesto:\n");
    scanf("%f", &hipoA);
    printf("Ingrese el valor del cateto adyacente:\n");
    scanf("%f", &hipoB);
    double hipotenusa = sqrt(pow(hipoA, 2) + pow(hipoB, 2)); 
    printf("La hipotenusa es %lf\n\n", hipotenusa);
}
