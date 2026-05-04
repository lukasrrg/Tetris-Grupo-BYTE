#ifndef PALETA_H_INCLUDED
#define PALETA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#define CANT_COLORES 16


//Letras para los colores
#define N 0  //Negro
#define AZ 1 //Azul
#define V 2  //Verde
#define C 3  //Celeste
#define R 4  //Rojo
#define M 5  //Magenta
#define B 13 //Blanco
#define AM 14 // Amarillo
#define T 15 // Transparente

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];

#endif // PALETA_H_INCLUDED
