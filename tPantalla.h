#ifndef TPANTALLA_H_INCLUDED
#define TPANTALLA_H_INCLUDED

#include "tBoton.h"
#include "tGrilla.h"
#include "tJugador.h"

//Resoluciones
#define ANCHO_VENTANA_CGA 320
#define ALTO_VENTANA_CGA 200
#define ANCHO_VENTANA_VGA 640
#define ALTO_VENTANA_VGA 480
#define ESCALA_VENTANA 2

//Estado de juego
#define PANTALLA_INICIAL 1
#define MENU_PRINCIPAL_CLASSIC 2
#define MENU_PRINCIPAL_DELUXE 3
#define JUGANDO 4
#define PAUSA 5
#define GAME_OVER 6
#define CONFIGURACION 7
#define INGRESO_NOMBRE 8
#define CONFIG_DELUXE 9
#define SALIR_DEL_JUEGO 0

//Datos del juego
#define VEL_INI_CAIDA 1.5


int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grillaActiva, tGBT_Temporizador *temporizador);
int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int gameOver(int resolAncho, int resolAlto);
int menuConfiguracion(int resolAncho, int resolAlto);
int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE]);
int menuConfigDeluxe(int resolAncho, int resolAlto, int *anchoGrilla);

#endif // TPANTALLA_H_INCLUDED
