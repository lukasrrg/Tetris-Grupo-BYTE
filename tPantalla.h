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

//Datos del juego
#define VEL_INI_CAIDA 1  //Cantidad de segundos (tipo de dato double) hasta que se desencade que el tetromin baje un cuadrado
#define SIN_INFORMACION -1  //Se pone en los cuadros de texto cuando dicho cuadro no necesita mostrar ningun parametro

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador *tempCaida, tGBT_Temporizador *tempInactiv);
int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int gameOver(int resolAncho, int resolAlto);
int menuConfiguracion(int resolAncho, int resolAlto);
void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto);
void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto);

#endif // TPANTALLA_H_INCLUDED
