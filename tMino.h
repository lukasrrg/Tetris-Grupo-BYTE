#ifndef TMINO_H_INCLUDED
#define TMINO_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include <stdbool.h>

#define CANT_COLORES 16

//#define N 15 // Transparente
//#define A 14 // Amarillo
//#define C 3  // Celeste
//#define V 2  // Verde

//tGBT_ColorRGB paletaCGA[CANT_COLORES];    //Esta comentado porque tiene un error aun no resuelto

typedef struct      //Esta estructura define cada Mino, o sea, cada CUADRADRITO
{
//    bool activo; //Puede que no haga falta esta implementacion
//    int tam;  //Puede que no haga falta esta implementacion
    int posX;
    int posY;
    tGBT_ColorRGB color;
} tMino;

#endif // TMINO_H_INCLUDED
