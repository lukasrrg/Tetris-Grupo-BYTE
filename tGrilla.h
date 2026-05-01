#ifndef TGRILLA_H_INCLUDED
#define TGRILLA_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "tMino.h"

//Resoluciones
#define ANCHO_VENTANA_CGA 320
#define ALTO_VENTANA_CGA 200
#define ANCHO_VENTANA_VGA 640
#define ALTO_VENTANA_VGA 480
#define ESCALA_VENTANA 3

//Tamaño de grilla de juego
#define ANCHO_GRILLA 10
#define ALTO_GRILLA 24

//Tamaño de mino
#define TAM_MINO 3


typedef struct              //Grilla in-game
{
    tMino *vecMinos;
} tGrilla;

bool grillaCrear(tGrilla *p);           //Pide memoria necesaria para la grilla
void grillaDestruir(tGrilla *p);        //Libera la memoria de la grilla
void grillaDibujar(const tGrilla *p);         //Dibujar grilla en pantalla

#endif // TGRILLA_H_INCLUDED
