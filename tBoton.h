#ifndef TBOTON_H_INCLUDED
#define TBOTON_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#define INACTIVO 0
#define ACTIVO 1
#define APUNTADO 2

//Letras para los colores
#define N 1  //Negro
#define V 2  // Verde
#define C 3  // Celeste
#define R 4  //Rojo
#define M 5  //Magenta
#define B 13 //Blanco
#define A 14 // Amarillo
#define T 15 // Transparente

#define COLOR_BOTON_APUNTADO 5 //Color que se ilumina un boton cuando esta siendo apuntado

typedef struct
{
    int estado; //Puede estar INACTIVO (no hace nada), ACTIVO (desencadena la accion para la cual existe) o APUNTADO (se ilumina su borde mostrandole al usuario que tiene el cursor sobre el)
    int tamAncho;
    int tamAlto;
    int posX;
    int posY;
    int colorBorde;
    int colorCentro;
//    char *texto;
} tBoton;

void botonCrear(tBoton *p, int estado, int ancho, int alto, int pX, int pY, int colBorde, int colCentro);
void botonDibujar(tBoton *p);
void botonActualizarTodosInactivo(tBoton *p, int ce);        //Actualiza el estado de todos los botones de un vector a INACTIVO

#endif // TBOTON_H_INCLUDED
