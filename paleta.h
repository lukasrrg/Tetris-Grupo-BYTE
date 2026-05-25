#ifndef PALETA_H_INCLUDED
#define PALETA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#define CANT_COLORES 16


//Letras para los colores
#define N 0  //Negro
#define AZ 1 //Azul
#define VE 2  //Verde
#define C 3  //Celeste
#define R 4  //Rojo
#define M 5  //Magenta
#define VI 6  //Violeta
#define GC 7 //Gris claro
#define GO 8 //Gris oscuro
#define AB 9 //Azul brillante
#define VB 10 //Verde brillante
#define NA 11 //Naranja
#define RB 12 //Rojo brillante
#define B 13 //Blanco
#define AM 14 // Amarillo
#define T 15 // Transparente

//Letras de identificacion para la segunda paleta
#define N   0   // Negro
#define AO  1   // Azul Oscuro
#define VO  2   // Verde Oscuro
#define AV  3   // Amarillo Verdoso
#define BO  4   // Bordo
#define MO  5   // Magenta Oscuro
#define VIO 6   // Violeta Oscuro
#define G   7   // Gris
#define GO  8   // Gris oscuro
#define AP  9   // Azul Petroleo
#define DA  10  // Dorado Apagado
#define IN  11  // Indigo Nocturno
#define BVO 12  // Borravino Oscuro
#define B   13  // Blanco
#define AM  14  // Amarillo
#define T   15  // Transparente

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];
extern tGBT_ColorRGB paletaVGA[CANT_COLORES];

#endif // PALETA_H_INCLUDED
