#ifndef TMINO_H_INCLUDED
#define TMINO_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include <stdbool.h>

#define CANT_COLORES 16

//Tamaño de mino
#define TAM_MINO 8

//Letras para los colores
#define N 0  //Negro
#define AZ 1 //Azul
#define V 2  // Verde
#define C 3  // Celeste
#define R 4  //Rojo
#define M 5  //Magenta
#define B 13 //Blanco
#define AM 14 // Amarillo
#define T 15 // Transparente

// Cantidad de tipos de tetraminos

#define CANT_TIPOS_TETRAMINOS 7

//Tipo de tetramino

#define TETRAMINO_O 0
#define TETRAMINO_J 1
#define TETRAMINO_L 2
#define TETRAMINO_T 3
#define TETRAMINO_I 4
#define TETRAMINO_S 5
#define TETRAMINO_Z 6


extern tGBT_ColorRGB paletaCGA[CANT_COLORES];

typedef struct      //Esta estructura define cada Mino
{
//    bool activo; //Puede que no haga falta esta implementacion
//    int tam;  //Puede que no haga falta esta implementacion
    int posX;
    int posY;
    int color;
} tMino;

typedef struct {
    tMino minos[4];   // siempre son exactamente 4 minos
    int tipo;
} tTetramino;

void crearMino(tMino *mino, int pX, int pY, int col);
void dibujarMino(tMino *mino);
void crearTetramino(tMino *tetramino, int pX, int pY);
void dibujarTetramino(tTetramino *tetramino);

#endif // TMINO_H_INCLUDED
