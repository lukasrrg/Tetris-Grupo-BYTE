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
    tCeldaGuardada celdas[ANCHO_GRILLA_MAX * ALTO_GRILLA_TOTAL];
} tPartida;


void partidaGuardar(const tPartida *p); // Guarda o sobreescribe la partida del jugador
bool partidaCargar(const char *nombre, bool modoDeluxe, tPartida *p); // Carga la partida del jugador. Devuelve true si existe.
void partidaSerializarGrilla(tPartida *p, const tGrilla *grilla); // Serializa la grilla hacia tPartida
void partidaRestaurarGrilla(const tPartida *p, tGrilla *grilla, int resolAncho, int resolAlto); // Restaura la grilla desde tPartida (recalcula posiciones)

#endif // TPARTIDA_H_INCLUDED
