#ifndef TPANTALLA_H_INCLUDED
#define TPANTALLA_H_INCLUDED

#include "tBoton.h"

//Estado de juego
#define PANTALLA_INICIAL 1
#define MENU_PRINCIPAL 2
#define JUGANDO 3
#define PAUSA 4
#define GAME_OVER 5
#define CONFIGURACION 6
#define SALIR_DEL_JUEGO 0

#define CURSOR_NO_APUNTA -1

//Tamaños de botones
#define ANCHO_BOTON_GRANDE 50
#define ANCHO_BOTON_MEDIANO 40
#define ANCHO_BOTON_CHICO 30
#define ALTO_BOTON_DEFAULT 10

int pantallaInicial(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipal(int resolAncho, int resolAlto);
int interfazJuego(int resolAncho, int resolAlto);
int menuPausa(int resolAncho, int resolAlto);
int gameOver(int resolAncho, int resolAlto);
int menuConfiguracion(int resolAncho, int resolAlto);

#endif // TPANTALLA_H_INCLUDED
