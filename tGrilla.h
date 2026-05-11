#ifndef TGRILLA_H_INCLUDED
#define TGRILLA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "tMino.h"
#include <stdlib.h>

//Tamaño de grilla de juego
#define ANCHO_GRILLA 10
#define ALTO_GRILLA_TOTAL 24
#define ALTO_GRILLA_VISIBLE 20
#define ALTO_GRILLA_INVISIBLE (ALTO_GRILLA_TOTAL - ALTO_GRILLA_VISIBLE)  // 4 filas ocultas sobre el techo
#define PRIMERA_FILA_VISIBLE 4


typedef struct              //Grilla in-game
{
    tMino *vecMinos;
} tGrilla;

bool grillaCrear(tGrilla *p, int resolAncho, int resolAlto);           //Pide memoria necesaria para la grilla
void grillaDestruir(tGrilla *p);        //Libera la memoria de la grilla
void grillaDeFondoDibujar(int resolAncho, int resolAlto);        //FUNCION INNECESARIA, SE PUEDE REEMPLAZAR POR dibujarRectangulo()
void grillaDibujar(const tGrilla *p);         //Dibujar grilla en pantalla
void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto);        //Dibuja en la grilla un tetromino en (tetro->posX, tetro->posY)
bool tetrominoColisionaSuelo(tTetromino *tetro);    //Chequea la colision con el suelo (hay que implementar la colision con otros minos)
void grillaActualizar(tGrilla *grilla, tTetromino *tetro);  //Actualiza los minos de la grilla (usado principalmente para que queden los tetrominos en el fondo guardados)

#endif // TGRILLA_H_INCLUDED
