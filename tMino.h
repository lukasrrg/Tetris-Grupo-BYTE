#ifndef TMINO_H_INCLUDED
#define TMINO_H_INCLUDED

#include <stdbool.h>

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "paleta.h"

//Tamaño de mino
#define TAM_MINO 8

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];

typedef struct      //Esta estructura define cada Mino, o sea, cada CUADRADRITO
{
//    bool activo; //Puede que no haga falta esta implementacion
//    int tam;  //Puede que no haga falta esta implementacion
    int posX;
    int posY;
    int color;
} tMino;

void minoCrear(tMino *mino, int pX, int pY, int col);
void minoDibujar(tMino *mino);

#endif // TMINO_H_INCLUDED
