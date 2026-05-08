#ifndef TPANTALLA_H_INCLUDED
#define TPANTALLA_H_INCLUDED

#include "tBoton.h"
#include "tGrilla.h"

//Resoluciones
#define ANCHO_VENTANA_CGA 320
#define ALTO_VENTANA_CGA 200
#define ANCHO_VENTANA_VGA 640
#define ALTO_VENTANA_VGA 480
#define ESCALA_VENTANA 2

//Estado de juego
#define PANTALLA_INICIAL 1
#define MENU_PRINCIPAL_CLASSIC 2
#define MENU_PRINCIPAL_DELUXE 7
#define JUGANDO 3
#define PAUSA 4
#define GAME_OVER 5
#define CONFIGURACION 6
#define SALIR_DEL_JUEGO 0


int pantallaInicial(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int resolAncho, int resolAlto, tTetromino *tetroActivo, tGrilla *grillaActiva, eGBT_Tecla tecla);
int menuPausa(int resolAncho, int resolAlto);
int gameOver(int resolAncho, int resolAlto);
int menuConfiguracion(int resolAncho, int resolAlto);

#endif // TPANTALLA_H_INCLUDED
