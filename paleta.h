#ifndef PALETA_H_INCLUDED
#define PALETA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#define CANT_COLORES 16


//Letras de identificacion para la paleta CLASICA
#define N 0  //Negro
#define AZ 1 //Azul
#define VE 2  //Verde
#define C 3  //Celeste
#define R 4  //Rojo
#define M 5  //Magenta
#define VI 6  //Violeta
#define AM 7 //Amarillo
#define GO 8 //Gris oscuro
#define AB 9 //Azul brillante
#define VB 10 //Verde brillante
#define NA 11 //Naranja
#define RB 12 //Rojo brillante
#define B 13 //Blanco
#define GC 14 // Gris claro
#define T 15 // Transparente

//Letras de identificacion para la paleta SHINY
#define N    0   // Negro
#define CN   1   // Cian Neon
#define MN   2   // Magenta Neon
#define AN   3   // Amarillo Neon
#define VL   4   // Verde Lima
#define RN   5   // Rojo Neon
#define AE   6   // Azul Electrico
#define G    7   // Gris Claro
#define NB   8   // Naranja Brillante
#define RF   9   // Rosa Fuerte
#define VN   10  // Violeta Neon
#define RCB  11  // Rojo Coral Brillante
#define VAN  12  // Verde Agua Neon
#define B    13  // Blanco Visible
#define AND  14  // Amarillo Naranja / Dorado Brillante
#define T    15  // Transparente

extern tGBT_ColorRGB paletaCLASICA[CANT_COLORES];
extern tGBT_ColorRGB paletaSHINY[CANT_COLORES];

#endif // PALETA_H_INCLUDED
