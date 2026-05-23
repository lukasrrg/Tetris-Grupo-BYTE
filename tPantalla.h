#ifndef TPANTALLA_H_INCLUDED
#define TPANTALLA_H_INCLUDED

#include <stdio.h>
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
#define OPCIONES 7
#define INGRESO_NOMBRE 8
#define GUARDAR_PARTIDA  9
#define CARGAR_PARTIDA  10
#define INGRESO_NOMBRE_CARGA 11
#define SALIR_DEL_JUEGO 0

//Datos del juego

#define VEL_CAIDA_RAPIDO 0.5
#define VEL_CAIDA_DEFAULT 1.0   //Segundos hasta que el tetromino baja un cuadrado
#define VEL_FIJACION_DEFAULT 0.5
#define VEL_NORMAL 0
#define VEL_RAPIDA 1
#define FACTOR_VEL_RAPIDA 10
#define VEL_CAIDA_LENTO 2.0
#define SIN_INFORMACION -1      //Para cuadros de texto sin parametro numerico
#define IZQUIERDA -1
#define DERECHA 1
#define ANTIHORARIO -1
#define HORARIO 1

#define MODO_CLASSIC 0
#define MODO_DELUXE 1

//Defines de los subindices para el vectorInfoJuego
#define DATOS_DE_JUEGO 7

//#define TETRO_T 0
//#define TETRO_L 1
//#define TETRO_J 2
//#define TETRO_I 3
//#define TETRO_S 4
//#define TETRO_Z 5
//#define TETRO_O 6
//#define TETRO_X 7
//#define TETRO_C 8
//#define TETRO_P 9
//#define TETRO_V 10
#define LINEAS 11
#define SCORE 12
#define TOP_SCORE 13
#define NIVEL 14
#define MODO_DE_JUEGO 15
#define RESOL_ANCHO 16
#define RESOL_ALTO 17


int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO], tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempInactiv, double *velActual, int *modoVelocidad);
int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int gameOver(int resolAncho, int resolAlto);
int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE]);
int ingresarNombreCarga(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE], bool modoDeluxe);
int menuOpciones(int resolAncho, int resolAlto, int *nuevoAncho, int *nuevoAlto, double *velCaida, int *anchoGrilla, bool modoDeluxe);
void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto);
void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto);


#endif // TPANTALLA_H_INCLUDED
