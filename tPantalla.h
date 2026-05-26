#ifndef TPANTALLA_H_INCLUDED
#define TPANTALLA_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include "tBoton.h"
#include "tGrilla.h"
#include "tJugador.h"

//Resoluciones
#define ANCHO_VENTANA_CGA 320
#define ALTO_VENTANA_CGA 200
#define ANCHO_VENTANA_VGA 640
#define ALTO_VENTANA_VGA 480
#define ESCALA_VENTANA_DEFAULT 2

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
#define CONFIRMAR_SOBREESCRITURA 12
#define SALIR_DEL_JUEGO 0

//Error
#define ERROR_INTERNO_JUEGO -123

//Velocidades
#define VEL_CAIDA_RAPIDO 0.5        //Segundos hasta que el tetromino baja un cuadrado
#define VEL_CAIDA_DEFAULT 1.0       //Segundos hasta que el tetromino baja un cuadrado
#define VEL_CAIDA_LENTO 2.0         //Segundos hasta que el tetromino baja un cuadrado
#define VEL_FIJACION_DEFAULT 0.5    //Segundos hasta que el tetromino se fija en la grilla

//Modos de velocidad
#define MODO_VEL_NORMAL 0
#define MODO_VEL_RAPIDA 1
#define FACTOR_VEL_RAPIDA 10
#define FACTOR_AUMENTO_VEL 1.03

//Puntajes
#define SCORE_CAIDA_RAPIDA 2
#define SCORE_LINEA 250
#define PORCENT_EXTRA_LINEA 1.2

#define SIN_INFORMACION -1      //Para cuadros de texto sin parametro numerico
#define IZQUIERDA -1
#define DERECHA 1
#define ANTIHORARIO -1
#define HORARIO 1

#define MODO_CLASSIC 0
#define MODO_DELUXE 1

//Defines de los subindices para el vectorInfoJuego
#define DATOS_DE_JUEGO 11

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
#define TETROMINOS_COLOCADOS 11
#define LINEAS 12
#define SCORE 13
#define TOP_SCORE 14
#define NIVEL 15
#define MODO_DE_JUEGO 16
#define RESOL_ANCHO 17
#define RESOL_ALTO 18
#define MODO_VELOCIDAD 19   //Indica si el tetromino baja a velocidad normal, o en velocidad rapida (por que se mantiene la 'S' presionada)
#define TETROMINO_LIBRE 20  //Cuando un tetromino detecta una colision, deja de estar libre (1) para estar en estado de fijacion (0) y se mantiene asi hasta que se cumple un periodo seguido de tiempo estando quieto
#define CHEATS_ACTIVADOS 21

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO], tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempFijacion, double *velActual);
int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce, int *cheatsActivos);
int gameOver(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce, int score);
int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE]);
int ingresarNombreCarga(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE], bool modoDeluxe);
int menuOpciones(int resolAncho, int resolAlto, int *nuevoAncho, int *nuevoAlto, double *velCaida, int *anchoGrilla, bool modoDeluxe);
int confirmarSobreescritura(int resolAncho, int resolAlto);
void infoInterfazDeJuego(int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO], char sigTetromino, int velActual);
void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto);
void verificarArgumentos(int argc, char *argv[], int *resolAncho, int *resolAlto, int *escala);


#endif // TPANTALLA_H_INCLUDED
