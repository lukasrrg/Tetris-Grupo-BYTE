#ifndef TGRILLA_H_INCLUDED
#define TGRILLA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "tMino.h"
#include "vectores_matrices.h"
#include <stdlib.h>

//Tamaño de grilla de juego
#define ANCHO_GRILLA_DEFAULT 10
#define ANCHO_GRILLA_MIN 8
#define ANCHO_GRILLA_MAX 16
#define ALTO_GRILLA_TOTAL 24
#define ALTO_GRILLA_VISIBLE 20
#define PRIMERA_FILA_VISIBLE (ALTO_GRILLA_TOTAL - ALTO_GRILLA_VISIBLE)

typedef struct              //Grilla in-game
{
    tMino **matMinos;    //Matriz de minos
    int anchoGrilla;    //Cuantos minos de ancho tiene (variable segun modo)
    int alto;           //Cuantos minos de alto tiene
} tGrilla;

void grillaDecorativaSetear(tGrilla *grilla);
bool grillaCrear(tGrilla *p, int anchoGrilla, int altoGrilla);   //Pide memoria necesaria para la grilla
void grillaDestruir(tGrilla *p);                                                //Libera la memoria de la grilla
void grillaDeFondoDibujar(int resolAncho, int resolAlto, int anchoGrilla);      //Dibuja el borde de la grilla (equivalente a dibujarRectangulo)
void grillaDibujar(const tGrilla *p, int resolAncho, int resolAlto);            //Dibuja los minos anclados en pantalla
void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto, int anchoGrilla, int modoDeJuego);  //Dibuja el tetromino activo sobre la grilla
bool tetrominoColisionaSuelo(tTetromino *tetro);                                //Chequea colision con el suelo
bool tetrominoColisionaConOtro(tTetromino *tetro, tGrilla *grilla, int modoDeJuego);             //Chequea colision con minos ya anclados
bool tetrominoColisionaLateralmente(tTetromino *tetro, tGrilla *grilla, int lado, int modoDeJuego); //Chequea colision lateral con bordes y minos
void grillaActualizar(tGrilla *grilla, tTetromino *tetro, int modoDeJuego);                      //Ancla el tetromino en la grilla
void grillaSetearFilaInactiva(tGrilla *grilla);
int grillaChequearLinea(tGrilla *grilla, tTetromino *tetro);                                       //Chequea si se completo alguna linea, y devuelve dicha cantidad de lineas completas

#endif // TGRILLA_H_INCLUDED
