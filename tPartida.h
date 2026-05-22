#ifndef TPARTIDA_H_INCLUDED
#define TPARTIDA_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include "tMino.h"
#include "tGrilla.h"
#include "tJugador.h"

#define PARTIDAS_BIN "partidas.bin"
#define MAX_PARTIDAS 100

// Celda serializable (sin posiciones de píxeles)
typedef struct {
    bool estado;
    int  color;
} tCeldaGuardada;

typedef struct {
    char   nombre[MAX_NOMBRE];
    int    puntaje;
    int    lineas;
    int    nivel;
    double velCaida;
    int    anchoGrilla;
    bool   modoDeluxe;
    tTetromino tetrominos[TAM_VEC_TETROMINOS];
    // ANCHO_GRILLA_MAX * ALTO_GRILLA_TOTAL celdas
    tCeldaGuardada celdas[ANCHO_GRILLA_MAX * ALTO_GRILLA_TOTAL];
} tPartida;

// Guarda o sobreescribe la partida del jugador
void partidaGuardar(const tPartida *p);

// Carga la partida del jugador. Devuelve true si existe.
bool partidaCargar(const char *nombre, tPartida *p);

// Serializa la grilla hacia tPartida
void partidaSerializarGrilla(tPartida *p, const tGrilla *grilla);

// Restaura la grilla desde tPartida (recalcula posiciones)
void partidaRestaurarGrilla(const tPartida *p, tGrilla *grilla, int resolAncho, int resolAlto);

#endif // TPARTIDA_H_INCLUDED
