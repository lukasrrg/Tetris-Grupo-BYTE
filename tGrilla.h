#ifndef TGRILLA_H_INCLUDED
#define TGRILLA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "tMino.h"

//Tamaño de grilla de juego
#define ANCHO_GRILLA 10
#define ALTO_GRILLA_TOTAL 24
#define ALTO_GRILLA_VISIBLE 20


typedef struct              //Grilla in-game
{
    tMino *vecMinos;
} tGrilla;

bool grillaCrear(tGrilla *p, int resolAncho, int resolAlto);           //Pide memoria necesaria para la grilla
void grillaDestruir(tGrilla *p);        //Libera la memoria de la grilla
void grillaDeFondoDibujar(int resolAncho, int resolAlto);
void grillaDibujar(const tGrilla *p);         //Dibujar grilla en pantalla
void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto);        //Dibuja en la grilla un tetromino en (tetro->posX, tetro->posY)

#endif // TGRILLA_H_INCLUDED
