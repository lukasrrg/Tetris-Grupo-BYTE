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
#define VEL_CAIDA_LENTO 2.0
#define SIN_INFORMACION -1      //Para cuadros de texto sin parametro numerico
#define IZQUIERDA -1
#define DERECHA 1
#define ANTIHORARIO -1
#define HORARIO 1
#define VEL_NORMAL 0
#define VEL_RAPIDA 1
#define FACTOR_VEL_RAPIDA 10

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempInactiv, double *velActual, int *modoVelocidad, bool modo, int *puntaje, int *lineas, int *nivel);
int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int gameOver(int resolAncho, int resolAlto);
int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE]);
int ingresarNombreCarga(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE], bool modoDeluxe);
int menuOpciones(int resolAncho, int resolAlto, int *nuevoAncho, int *nuevoAlto, double *velCaida, int *anchoGrilla, bool modoDeluxe);
void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto);
void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto);


#endif // TPANTALLA_H_INCLUDED
