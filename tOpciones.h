#ifndef TOPCIONES_H_INCLUDED
#define TOPCIONES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include "tPantalla.h"

#define OPCIONES_BIN "opciones.bin"

typedef struct
{
    int resolAncho;
    int resolAlto;
    double velCaida;
    int anchoGrilla;
    int paleta;   // reservado para el futuro
} tOpciones;

void opcionesGuardar(const tOpciones *op);
void opcionesCargar(tOpciones *op);

#endif // TOPCIONES_H_INCLUDED
