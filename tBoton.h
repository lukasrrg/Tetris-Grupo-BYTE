#ifndef TBOTON_H_INCLUDED
#define TBOTON_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "texto.h"

//Estados de los botones
#define INACTIVO 0
#define ACTIVO 1
#define APUNTADO 2

#define COLOR_BOTON_APUNTADO 5 //Color que se ilumina un boton cuando esta siendo apuntado

//Tamaños de botones
#define ANCHO_BOTON_GRANDE 90
#define ANCHO_BOTON_MEDIANO 50
#define ANCHO_BOTON_CHICO 35
#define ALTO_BOTON_DEFAULT 11
#define SEPARACION_ENTRE_BOTON 3


typedef struct
{
    int estado; //Puede estar INACTIVO (no hace nada), ACTIVO (desencadena la accion para la cual existe) o APUNTADO (se ilumina su borde mostrandole al usuario que tiene el cursor sobre el)
    int tamAncho;
    int tamAlto;
    int posX;
    int posY;
    int colorBorde;
    int colorCentro;
    int colorTexto;
    char texto[20];
} tBoton;

void botonCrear(tBoton *p, int estado, int ancho, int alto, int pX, int pY, int colBorde, int colCentro, char text[], int colTexto);
void botonDibujar(tBoton *p);
void botonActualizarTodosInactivo(tBoton *p, int ce);        //Actualiza el estado de todos los botones de un vector a INACTIVO

#endif // TBOTON_H_INCLUDED
