#ifndef TJUGADOR_H_INCLUDED
#define TJUGADOR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 20
#define JUGADORES "jugadores.bin"

typedef struct
{
    char nombre[MAX_NOMBRE];
    int puntaje_max;
} tJugador;

bool jugadorExiste(const char* nombre); //Devuelve true si el nombre ya existe en el archivo.
void jugadorGuardar(const tJugador *jugador); //Guarda un jugador nuevo o sobreeescribe si ya existe.

#endif // TJUGADOR_H_INCLUDED
